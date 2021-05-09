#include "unit_impulse_signal.hpp"

namespace cps {

    double UnitImpulseSignal::value(double x) const {
        if(x == mImpulseSampleX)
        {
            return mAmplitude;
        }
        else
        {
            return 0;
        }
    }

    UnitImpulseSignal::UnitImpulseSignal(int initialTimeSec, int durationSec,
                                         int impulseSampleNumber, int samplingFrequency)
                                         : Signal(1, initialTimeSec, durationSec), mSamplingFrequency(samplingFrequency) {
        const int samplesNumber = mDurationSec * mSamplingFrequency;
        const double sampleDeltaTime = (double)mDurationSec / (double)samplesNumber;
        mImpulseSampleX = (impulseSampleNumber - 1) * sampleDeltaTime;
    }
}