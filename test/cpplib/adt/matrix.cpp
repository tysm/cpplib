#include <cpplib/adt/matrix.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    auto m = matrix<int, 2>::identity();
    m = exp(m, 1000);
    return 0;
}
