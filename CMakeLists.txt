cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(UNIX AND NOT APPLE)
   set(LINUX TRUE)
endif()

project(CP)

set(CP_SRC
    header/atom.h
    header/multiset.h
    header/program.h
    header/simplesystem.h
    source/main.cxx
    source/multiset.cxx
    source/program.cxx
    )

add_executable(CP ${CP_SRC})  
target_include_directories(CP PRIVATE header test/header)

if(LINUX) 
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CP PRIVATE Threads::Threads)
endif()
