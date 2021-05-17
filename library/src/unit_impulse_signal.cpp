#include "unit_impulse_signal.hpp"

namespace cps {

    double UnitImpulseSignal::value(double x) {
        if(x == mImpulseSampleX)
        {
            return mAmplitude;
        }
        else
        {
            return 0;
        }
    }

    UnitImpulseSignal::UnitImpulseSignal(double initialTimeSec, double durationSec,
                                         int impulseSampleNumber, int samplingFrequency)
                                         : DiscreetSignal(1, initialTimeSec, durationSec, samplingFrequency) {
        const int samplesNumber = mDurationSec * mSamplingFrequency;
        const double sampleDeltaTime = (double)mDurationSec / (double)samplesNumber;
        mImpulseSampleX = (impulseSampleNumber - 1) * sampleDeltaTime;
    }
}