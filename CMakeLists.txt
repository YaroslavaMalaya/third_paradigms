cmake_minimum_required(VERSION 3.26)
project(third_paradigms)

set(CMAKE_CXX_STANDARD 17)

add_executable(third_paradigms main.cpp
        library/CaesarCipherDLL.cpp
        FileReader.cpp
        FileReader.h
        FileWriter.cpp
        FileWriter.h)
