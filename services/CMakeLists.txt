cmake_minimum_required(VERSION 2.8) 
project(services)
include_directories("/usr/local/include/hiredis")
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")
find_package(Threads)
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 
set(SRC
    main.cpp
    tcpserver.cpp
    simpletask.cpp
    redistask.cpp
    redisserver.cpp
    threadpool.hpp
    )
add_executable(service ${SRC})

target_link_libraries(service ${CMAKE_THREAD_LIBS_INIT} hiredis) 
