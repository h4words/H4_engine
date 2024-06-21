cmake_minimum_required(VERSION 3.10)
project(glad)

add_library(glad STATIC include/glad/glad.h src/glad.c include/KHR/khrplatform.h)

target_include_directories(glad PUBLIC include)
