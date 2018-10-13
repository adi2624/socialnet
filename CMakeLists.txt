cmake_minimum_required(VERSION 3.12)
project(socialnet)

set(CMAKE_CXX_STANDARD 14)

include_directories(cpp/src)

add_executable(socialnet
        cpp/src/main.cpp
        cpp/src/Post.cpp
        cpp/src/Post.h
        cpp/src/Request.cpp
        cpp/src/Request.h
        cpp/src/Response.cpp
        cpp/src/Response.h
        cpp/src/User.cpp
        cpp/src/User.h
        cpp/src/users.tsn)
