#include "hamming_window.hpp"
#include <cmath>

namespace cps {

    HammingWindow::HammingWindow(int M) : mM(M) {
    }

    double HammingWindow::value(int n) const {
        return 0.53836 - 0.46164 * cos(2.0 * M_PI * n / mM);
    }

}