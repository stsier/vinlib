{
  "targets": [
    {
      "target_name": "vinlib",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      'cflags_cc': [ '-frtti','-fexceptions', '-std=gnu++0x' ],
      "cflags+": [ "-std=c++11" ],
      "cflags_c+": [ "-std=c++11" ],
      "cflags_cc+": [ "-std=c++11" ],
      "cflags" : [ "-std=c++11", "-static-libstdc++" ],
      "sources": [
        "./src/index.cpp",
        "./src/Reader.cpp", 
        "./src/Extractor.cpp", 
        "./src/Drawer.cpp", 
        "./src/Matcher.cpp",
        "./src/main.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/usr/local/include/opencv4",
        "./src/include"
      ],
      
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    "libraries": [
        "-lopencv_core", 
        "-lopencv_imgcodecs",
         "-lopencv_flann",
         "-lopencv_calib3d",
         "-lopencv_features2d",
         "-lopencv_imgproc",
         "-lopencv_objdetect",
         "-L/usr/local/lib",
         "-L/usr/local/share/opencv4/",
         "-lrt",
        "-L/usr/lib"
      ]
      

    }
  ]
}