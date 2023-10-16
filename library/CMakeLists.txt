cmake_minimum_required(VERSION 3.26)
project(library)

set(CMAKE_CXX_STANDARD 17)

add_library(library SHARED CaesarCipherDLL.cpp)
