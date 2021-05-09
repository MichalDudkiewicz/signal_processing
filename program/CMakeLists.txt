cmake_minimum_required(VERSION 3.14)
project(program)

set(SOURCE_FILES
        main.cpp
        )

add_executable(program ${SOURCE_FILES})

target_link_libraries(program library)