#include "signal.hpp"
#include "unit_impulse_signal.hpp"
#include "signal_sampler.hpp"
#include "uniform_distribution_noise.hpp"
#include "gaussian_noise.hpp"
#include "sinusoidal_signal.hpp"
#include "half_rectified_sinusoidal_signal.hpp"
#include "rectified_sinusoidal_signal.hpp"
#include "rectangular_signal.hpp"
#include "symmetrical_rectangular_signal.hpp"
#include "triangular_signal.hpp"
#include "unit_step_signal.hpp"
#include "impulse_noise.hpp"
#include <iostream>

using namespace cps;

int main() {
//    UniformDistributionNoise signal(1, 0, 4);
//    GaussianNoise signal(1, 0, 5);
//    SinusoidalSignal signal(1, 0, 4, 1);
//    HalfRectifiedSinusoidalSignal signal(1, 0, 4, 1);
//    RectifiedSinusoidalSignal signal(1, 0, 4, 1);
//    RectangularSignal signal(-1, 0, 4, 1, 0.25);
//    SymmetricalRectangularSignal signal(-1, 0, 4, 1, 0.25);
//    TriangularSignal signal(1, 0, 4, 1, 0.5);
//    UnitStepSignal signal(1, 0, 4, 1);
//    UnitImpulseSignal signal(0, 4, 10, 16);
    ImpulseNoise signal(1, 0, 4, 16, 0.5);

    std::cout << signal.mean() << "\n" << signal.absMean() << "\n" << signal.rms() << "\n" << signal.variance() << "\n" << signal.meanPower();

    int a = 0;
}

