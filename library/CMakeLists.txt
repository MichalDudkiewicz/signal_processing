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
        src/symmetrical_rectangular_signal.cpp
        src/triangular_signal.cpp
        src/unit_step_signal.cpp
        src/discreet_signal.cpp
        src/impulse_noise.cpp
        src/periodic_signal.cpp
        src/custom_signal.cpp
        src/utils.cpp
        include/quantizer.hpp
        include/extrapolator.hpp
        )

target_include_directories(library PUBLIC include)