cmake_minimum_required(VERSION 3.17)
project(library CXX)

add_library(library
        src/signal.cpp
        src/unit_impulse_signal.cpp
        src/signal_sampler.cpp
        include/signal_sampler.hpp
        src/uniform_distribution_noise.cpp
        src/gaussian_noise.cpp
        src/sinusoidal_signal.cpp
        src/half_rectified_sinusoidal_signal.cpp
        src/rectified_sinusoidal_signal.cpp
        src/rectangular_signal.cpp
        )

target_include_directories(library PUBLIC include)