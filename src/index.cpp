#include <napi.h>
#include <string>
#include "include/common.h"
#include <iostream>
using namespace std;

Napi::String start(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    string path = static_cast<string>(info[0].ToString());
    string img1 = static_cast<string>(info[1].ToString());
    string img2 = static_cast<string>(info[2].ToString());
    
    path = "undefined" ? "" : path;
    img1 = "undefined" ? "" : img1;
    img2 = "undefined" ? "" : img2;
    std::cout << "info.Env(): "<< path << ": " << img1 <<" vs " << img2 << std::endl;

    std::string result = "vinlib terminated successfully";

   try {
       test(path,img1,img2);      
    } 
    catch(std::exception e) {
        result = "error";
    }

    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {

    exports.Set(
        Napi::String::New(env, "start"), // property name => "start"
        Napi::Function::New(env, start) // property value => `start` function
    );

    return exports;
}

NODE_API_MODULE(vinlib, Init)