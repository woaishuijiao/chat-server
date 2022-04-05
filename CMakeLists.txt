cmake_minimum_required(VERSION 3.15)
project(chat-server)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC base/log.cpp utils/util.cpp base/singleton.h)

add_library(jionglog SHARED ${LIB_SRC})

add_executable(test tests/test.cpp)
add_dependencies(test jionglog)
target_link_libraries(test jionglog)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

add_executable(chat-server chatserver/main.cpp chatserver/tcpserver.h chatserver/tcpserver.cpp) 
add_dependencies(chat-server jionglog)
target_link_libraries(chat-server jionglog)
