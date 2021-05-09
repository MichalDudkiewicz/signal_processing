#include "signal.hpp"
#include "unit_impulse_signal.hpp"
#include "signal_sampler.hpp"
#include "uniform_distribution_noise.hpp"
#include "gaussian_noise.hpp"

using namespace cps;

int main() {
//    UnitImpulseSignal signal(0, 4, 10, 16);
//    UniformDistributionNoise signal(1, 0, 4);
    GaussianNoise signal(1, 0, 5);
    SignalSampler signalSampler(16);
    const auto sampledSignal = signalSampler.sample(signal);

    int a = 0;
}

