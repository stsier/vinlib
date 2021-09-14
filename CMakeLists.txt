cmake_minimum_required(VERSION 3.20)

#cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

#set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
#set(BUILD_SHARED_LIBS OFF)
#set(CMAKE_EXE_LINKER_FLAGS "-static")
#set(CMAKE_SHARE_LINKER_FLAGS "-static-libgcc -static-libstdc++  -pthread  -lrt -ldl -lm  ")
#set(CMAKE_BUILD_WITH_INSTALL_RPATH on)

#set(OpenCV_LIBS "../opencvlibs")
#set(OpenCV_DIR "opencv/lib/cmake/opencv4")

project( vinlib )
file(GLOB_RECURSE SOURCE_FILES 
        src/main.cpp 
        src/index.cpp 
        src/Reader.cpp 
        src/Extractor.cpp 
        src/Drawer.cpp 
        src/Matcher.cpp     
)

#find_library(opencv_imgproc NAMES libopencv_imgproc.so.4.5  PATHS  ${CMAKE_CURRENT_SOURCE_DIR}/opencvlibs NO_DEFAULT_PATH REQUIRED)
#find_library(opencv_core NAMES libopencv_core.so.4.5  PATHS  ${CMAKE_CURRENT_SOURCE_DIR}/opencvlibs NO_DEFAULT_PATH REQUIRED)

#find_library(opencv_core NAMES libopencv_core.a  REQUIRED)

#find_library(opencv_imgproc NAMES libopencv_imgproc.a  REQUIRED)

#SET_PROPERTY(TARGET ${PROJECT_NAME}  PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/opencvlib/")
#set(OpenCV_INCLUDE_DIRS /usr/local/include/opencv4)
 
#add_library( opencv_imgproc STATIC IMPORTED GLOBAL)
#set_target_properties( opencv_imgproc PROPERTIES IMPORTED_LOCATION  /usr/local/lib/libopencv_imgproc.a)
#add_library( opencv_imgproc STATIC /home/sergei/opencv-master/modules/imgproc/src/resize.cpp) #${OpenCV_INCLUDE_DIRS}/opencv2/imgproc.hpp) 

find_package(Eigen3 REQUIRED)
find_package(Iconv REQUIRED)
find_package(gflags REQUIRED)
find_package(OpenCV REQUIRED)


#find_library(libm.so.6 NAME libm-2.31.so  PATHS /lib/x86_64-linux-gnu/ REQUIRED)


include_directories( ${OpenCV_INCLUDE_DIRS} /home/sergei/.cmake-js/node-x64/v16.9.1/include/node src/include ${CMAKE_JS_INC}) # 


link_directories(/usr/local/lib/)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES}  ${CMAKE_JS_SRC}) 

#add_executable( ${PROJECT_NAME} ${SOURCE_FILES}  ${CMAKE_JS_SRC})

set_target_properties(${PROJECT_NAME}   PROPERTIES  POSITION_INDEPENDENT_CODE  TRUE  )

set_target_properties(${PROJECT_NAME}  PROPERTIES  PREFIX "" SUFFIX ".node" )
target_link_libraries(${PROJECT_NAME}  ${OpenCV_LIBS} ${CMAKE_JS_LIB} -static-libgcc -static-libstdc++)  #  INTERFACE ${OpenCV_LIBS} opencv_imgproc 

# Include node-addon-api wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )

        string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
        string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

#variable_watch(${OpenCV_LIBS})
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message (STATUS "opencv_imgproc:  ${opencv_imgproc}")

