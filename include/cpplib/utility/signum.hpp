#pragma once
#include <cpplib/stdinc.hpp>

template<typename T,
typename enable_if<is_arithmetic<T>::value, uint>::type = 0>
int sign(const T n){
    return n == 0? 0 : (n < 0? -1 : 1);
}
