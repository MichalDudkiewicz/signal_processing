#ifndef SIGNAL_PROCESSING_RECTANGULAR_WINDOW_HPP
#define SIGNAL_PROCESSING_RECTANGULAR_WINDOW_HPP

#include "window.hpp"

namespace cps {
    class RectangularWindow : public Window {
    public:
        double value(int n) const override;
    };
}

#endif //SIGNAL_PROCESSING_RECTANGULAR_WINDOW_HPP
