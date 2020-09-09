#ifndef CAR_HPP
#define CAR_HPP

#include "Part.hpp"

struct Car : Part {
    Wheels *wheels = nullptr;

    Car() {}
};

#endif