#include "filter.hpp"

#include <utility>
#include <stdexcept>

namespace cps {

    Filter::Filter(int M, double fo, std::shared_ptr<Window> window) : mM(M), mFo(fo), mWindow(std::move(window)){
        if (M % 2 != 0)
        {
            throw std::invalid_argument("M must be odd!");
        }
    }
}