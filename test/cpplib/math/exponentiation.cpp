#include <cpplib/math/exponentiation.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    auto res = exp(2, 31);
    assert(res == 1 << 31);
    return 0;
}
