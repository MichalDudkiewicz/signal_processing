cmake_minimum_required(VERSION 3.14)
project(test_program)

set(SOURCE_FILES
        main.cpp
        )

add_executable(test_program ${SOURCE_FILES})

target_link_libraries(test_program library)