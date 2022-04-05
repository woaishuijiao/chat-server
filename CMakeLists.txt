cmake_minimum_required(VERSION 3.15)
project(chat-server)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC log.cpp util.cpp singleton.h)

add_library(jiong SHARED ${LIB_SRC})

add_executable(test tests/test.cpp)
add_dependencies(test jiong)
target_link_libraries(test jiong)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

add_executable(chat-server main.cpp tcpserver.h tcpserver.cpp log.h log.cpp util.h util.cpp singleton.h)
