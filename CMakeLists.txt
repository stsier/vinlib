cmake_minimum_required(VERSION 2.8)
project( vinlib )
file(GLOB_RECURSE sources 
        src/main.cpp 
        src/Reader.cpp 
        src/include/Reader.h 
        src/Extractor.cpp 
        src/include/Extractor.h 
        src/Drawer.cpp 
        src/include/Drawer.h
        src/Matcher.cpp 
        src/include/Matcher.h
)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS}, src, src/include )
add_executable( vinlib ${sources} )
target_link_libraries( vinlib ${OpenCV_LIBS} )