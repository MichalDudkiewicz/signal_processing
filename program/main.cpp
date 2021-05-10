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

using namespace cps;

int main() {
//    UnitImpulseSignal signal(0, 4, 10, 16);
//    UniformDistributionNoise signal(1, 0, 4);
//    GaussianNoise signal(1, 0, 5);
//    SinusoidalSignal signal(1, 0, 4, 1);
//    HalfRectifiedSinusoidalSignal signal(1, 0, 4, 1);
//    RectifiedSinusoidalSignal signal(1, 0, 4, 1);
//    RectangularSignal signal(10, 0, 10, 2, 0.25);
    SymmetricalRectangularSignal signal(10, 0, 10, 2, 0.25);
    SignalSampler signalSampler(16);
    const auto sampledSignal = signalSampler.sample(signal);

    int a = 0;
}

