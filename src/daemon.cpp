#include <string.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <boost/algorithm/string.hpp>

#include "Poco/URI.h"
#include "Poco/Net/HTTPClientSession.h"

#include "Poco/Net/HTTPServer.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"


// global variable to count requests to the daemon
int requestIterator = 0;
// timer
std::chrono::steady_clock::time_point timelaps;
// video sequences
std::vector<std::string> sequences;

// concrete http request handler class that overrides Poco's HTTPRequestHandler abstract class
class RootHandler : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest &request,
                       Poco::Net::HTTPServerResponse &response)
    {

        // let's try to know who is the author of the request
        std::string caller;
        try
        {
            caller = request.get("User-Agent");
        }
        catch (Poco::NotFoundException exc)
        {
            caller = "Somebody";
        }

        std::cout << "[IN] " << caller << " asks server " << request.getHost() << request.getURI() << std::endl;

        // set Transfer-Encoding header of the response to chunked
        response.setChunkedTransferEncoding(true);
        // set the responce type to text
        response.setContentType("text/html");

        // open an output stream for the response 
        std::ostream &ostr = response.send();

        if (requestIterator <= sequences.size())
        {
            // print only the name of the video chunk, not the whole path 
            std::vector<std::string> pathChunks;
            boost::split(pathChunks, sequences[requestIterator], [](char c)
                         { return c == '/'; });
            std::cout << "[Out] " << pathChunks[pathChunks.size() - 1] << "("
                      << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timelaps).count()
                      << "ms)" << std::endl;
            timelaps = std::chrono::steady_clock::now();

            // add the video part to the responce
            ostr << sequences[requestIterator];
        }
        // tell the client that the sequence is over
        if (requestIterator == sequences.size())
        {
            ostr << "\n#EXT-X-ENDLIST";
            std::cout << "Sequence end" << std::endl;
            
        }

        requestIterator++;
        
    }
};

// concrete factory class for request handler objects that overrides HTTPRequestHandlerFactory
class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    RequestHandlerFactory(){};
    ~RequestHandlerFactory(){};

public:
    virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request)
    {
        return new RootHandler;
    };
};

int main(int argc, char **argv)
{
    // *************** Client part ***************

    // Argument must be test or link to m3u8 file
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " test or your <uri> to m3u8" << std::endl;
        return -1;
    }
    std::string uriStr = "";

    if (strcmp(argv[1], "test") == 0)
    {
        uriStr = "http://bitdash-a.akamaihd.net/content/MI201109210084_1/m3u8s/f08e80da-bf1d-4e3d-8899-f0f6155f6efa_video_1080_4800000.m3u8";
    }
    else
    {
        std::cout << "Unknown path " << argv[1] << std::endl;
        return -1;
    }

    Poco::URI uri(uriStr);

    std::cout << "Trying to fetch " << uri.toString() << std::endl;

    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    session.setKeepAlive(true);
    try
    {
        // build a request to the video source 
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPRequest::HTTP_1_1);
        // expect plain text
        request.setContentType("text/html");
        session.sendRequest(request);
    }
    // handle exception in case, for example, the video host is unavailable or link is incorrect
    catch (Poco::Exception &exc)
    {
        std::cerr << "ERR " << exc.displayText() << std::endl;
        return 1;
    }

    std::vector<std::string> pathChunks;
    boost::split(pathChunks, uri.toString(), [](char c)
                 { return c == '/'; });

    // obtain the path of the m3u8 file           
    std::string cdnPath;
    for (uint j = 0; j < pathChunks.size() - 1; j++)
    {
        cdnPath += pathChunks[j] + "/";
    }

    // response from the video host
    Poco::Net::HTTPResponse response;
    std::string recv_string;
    try
    {
        if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
        {
            std::istream &is = session.receiveResponse(response);
            Poco::StreamCopier::copyToString(is, recv_string);

            // the responce from the host is expected to be in the recv_string
            // let's break it into a vector of lines
            std::vector<std::string> lines;
            boost::split(lines, recv_string, [](char c)
                         { return c == '\n'; });
            // sequence is a payload string to be sent to VLC                         
            std::string sequence = "";
            for (const std::string &line : lines)
            {
                // don't modify the line that starts with #
                if (line[0] == '#')
                {
                    sequence += line + '\n';
                }
                // no need of empty lines
                else if (line.empty())
                {
                    continue;
                }
                else
                {
                    std::size_t found = line.find("http");
                    // if the path is relative then append the host path to the video part
                    if (found == std::string::npos)
                    {
                        sequence += cdnPath + line;
                    }
                    // otherwise keep the absolute host path
                    else
                    {
                        sequence += line;
                    }
                    // detect the end of the sequence
                    found = line.find(".ts");
                    if (found != std::string::npos)
                    {
                        sequences.push_back(sequence);
                        sequence = "";
                    }
                }
            }
        }
    }
    catch (Poco::Exception &exc)
    {
        std::cerr << "ERR " << exc.displayText() << std::endl;
        return 1;
    }

    if(sequences.size() == 0) {
        std::cerr << "ERR Empty response" << std::endl;
        return 1;
    }

    // *************** Server part ***************

    //Port to listen
    Poco::UInt16 port = 9999;

    Poco::Net::ServerSocket socket(port);

    Poco::Net::HTTPServerParams *pParams = new Poco::Net::HTTPServerParams();
    // we have one client so 
    // set the maximum number of queued connections.
    pParams->setMaxQueued(1);
    // set the maximum number of simultaneous threads available for this server
    pParams->setMaxThreads(1);

    Poco::Net::HTTPServer server(new RequestHandlerFactory(), socket, pParams);

    server.start();

    // start the timer
    timelaps = std::chrono::steady_clock::now();

    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // stop the server when done sending video sequences
        if (requestIterator == sequences.size() + 1)
        {
            server.stop();
            std::cout << "Server stopped " << std::endl;
            break;
        }
    }

    return 0;
}
