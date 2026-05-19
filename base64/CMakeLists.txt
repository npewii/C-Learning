cmake_minimum_required(VERSION 3.10.0)
project(base64 VERSION 0.1.0 LANGUAGES C)

add_executable(base64
    src/main.c    
    src/base64.c
)

