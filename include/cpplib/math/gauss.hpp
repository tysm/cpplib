#pragma once
#include <cpplib/stdinc.hpp>

void fft(vector<complex<double> > &a, const bool invert = false)
{
    // n must me a power of 2.
    uint n = a.size();
    for(uint i = 1, j = 0; i < n; ++i) {
        uint bit = (n >> 1);
        for(; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if(i < j)
            swap(a[i], a[j]);
    }

    for(uint len = 2; len <= n; len <<= 1) {
        double ang = (2 * PI / len) * (invert ? -1 : 1);
        complex<double> wlen(cos(ang), sin(ang));
        for(uint i = 0; i < n; i += len) {
            complex<double> w(1);
            for(uint j = 0; j < len / 2; ++j) {
                complex<double> u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert) {
        for(complex<double> &i: a)
            i /= n;
    }
}
