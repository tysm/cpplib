#pragma once
#include <cpplib/stdinc.hpp>

template<typename T>
int sign(const T n) {
    return n == 0 ? 0 : (n < 0 ? -1 : 1);
}
