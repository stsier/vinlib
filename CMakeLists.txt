cmake_minimum_required(VERSION 3.10)

#cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project( vinlib )
file(GLOB_RECURSE SOURCE_FILES 
        src/main.cpp 
        src/index.cpp 
        src/Reader.cpp 
        src/Extractor.cpp 
        src/Drawer.cpp 
        src/Matcher.cpp     
)


find_package(OpenCV REQUIRED)


include_directories( ${OpenCV_INCLUDE_DIRS} src/include ${CMAKE_JS_INC}) 

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES}  ${CMAKE_JS_SRC}) 

set_target_properties(${PROJECT_NAME}   PROPERTIES  POSITION_INDEPENDENT_CODE  TRUE  )

set_target_properties(${PROJECT_NAME}  PROPERTIES  PREFIX "" SUFFIX ".node" )
target_link_libraries(${PROJECT_NAME}  ${OpenCV_LIBS} ${CMAKE_JS_LIB} -static-libgcc -static-libstdc++) 

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

