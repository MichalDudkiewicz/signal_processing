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
#include <custom_signal.hpp>
#include <sstream>
#include <fstream>
#include <ostream>
#include <istream>

using namespace cps;

int main() {
//    UniformDistributionNoise signal(1, 0, 4);
//    GaussianNoise signal(1, 0, 5);
    SinusoidalSignal signal1(1, 0, 4, 1);
    HalfRectifiedSinusoidalSignal signal2(1, 0, 4, 1);
//    RectifiedSinusoidalSignal signal2(1, 0, 4, 1);
//    RectangularSignal signal(-1, 0, 4, 1, 0.25);
//    SymmetricalRectangularSignal signal(-1, 0, 4, 1, 0.25);
//    TriangularSignal signal(1, 0, 4, 1, 0.5);
//    UnitStepSignal signal(1, 0, 4, 1);
//    UnitImpulseSignal signal(0, 4, 10, 16);
//    ImpulseNoise signal(1, 0, 4, 16, 0.5);

    std::cout << signal1.mean() << "\n" << signal1.absMean() << "\n" << signal1.rms() << "\n" << signal1.variance() << "\n" << signal1.meanPower() << '\n';

    const auto custom = signal1 * signal2;

    std::ofstream out;
    out.open( "1.bin",
              std::ios::out | std::ios::trunc | std::ios::binary );

    custom.serialize(out);
    out.close();

    std::fstream in;
    in.open("1.bin", std::ios::in | std::ios::binary);
    CustomSignal customSignal;
    customSignal.unserialize(in);
    in.close();

    std::cout << customSignal;

    int a = 0;
}

