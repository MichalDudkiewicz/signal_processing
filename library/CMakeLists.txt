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
        src/sin_card_reconstructed_signal.cpp
        src/signal_similarity_measures.cpp
        src/quantized_signal.cpp
        src/extrapolated_signal.cpp
        include/window.hpp
        src/rectangular_window.cpp
        src/hamming_window.cpp
        src/filter.cpp
        src/low_pass_filter.cpp
        src/high_pass_filter.cpp
        src/discreet_fourier_transform.cpp
        src/complex_signals_processor.cpp
        )

target_include_directories(library PUBLIC include)