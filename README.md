# README

This small daemon program makes use of the Poco library to create a http server and client.

It consists of two parts. 

The client part asks for the url of a m3u8 file. 
Then it fetches the contents at the provided url making a GET request. 

It loops through the response text and populates a video sequences vector, taking into account relative and absolute links.

Then in the second part, a http server daemon is launched listening at the port 9999. 

Once  the VLC application hits the server, it starts feeding it video parts. 

At the end it appends the #EXT-X-ENDLIST line to tell VLC that the sequence is over. After that it shuts down and the daemon exits. 

Please see the screenshots. 



