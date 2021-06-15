#ifndef SIGNAL_PROCESSING_HAMMING_WINDOW_HPP
#define SIGNAL_PROCESSING_HAMMING_WINDOW_HPP

#include "window.hpp"

namespace cps {
    class HammingWindow : public Window {
    public:
        HammingWindow(int M);

    public:
        double value(int n) const override;

    private:
        int mM;
    };
}

#endif //SIGNAL_PROCESSING_HAMMING_WINDOW_HPP
