{
  "targets": [
    {
      "target_name": "vinlib",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      'cflags_cc': [ '-frtti','-fexceptions', '-std=gnu++0x' ],
      "sources": [
        "./src/index.cpp",
        "./src/main.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/usr/local/include/opencv4",
        "./src/include"
      ],
      
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    "libraries": [
        "-L/usr/local/lib",
        "-lopencv_core", 
        "-lopencv_highgui",
        "-lopencv_imgcodecs",
         "-lopencv_flann",
         "-lopencv_calib3d",
         "-lopencv_features2d",
         "-lopencv_imgproc",
         "-lopencv_objdetect"
      ]
      

    }
  ]
}