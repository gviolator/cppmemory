cmake_minimum_required(VERSION 3.17)
project (cppmemory)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /JMC /FC /Zc:__cplusplus /std:c++latest /permissive-")

add_subdirectory(commonlib)
add_subdirectory(cppoperators)
add_subdirectory(pageallocation)
add_subdirectory(stdallocator)
add_subdirectory(runtimestack)
add_subdirectory(runtimepool)
