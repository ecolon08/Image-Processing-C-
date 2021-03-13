cmake_minimum_required(VERSION 3.17)
project(image_processing_lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(image_processing_lib main.cpp ImageProcessing.cpp ImageProcessing.h)