#ifndef SIGNAL_PROCESSING_WINDOW_HPP
#define SIGNAL_PROCESSING_WINDOW_HPP

namespace cps {
    class Window {
    public:
        virtual ~Window() = default;

    public:
        virtual double value(int n) const = 0;
    };
}

#endif //SIGNAL_PROCESSING_WINDOW_HPP
