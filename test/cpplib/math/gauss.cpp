#include <cpplib/math/gauss.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<complex<double> > a;
    for(int i = 0; i < 100; ++i)
        a.emplace_back(1, 1);
    fft(a);
    return 0;
}
