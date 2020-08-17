#include <cpplib/adt/modular.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    mint i = 10, j = 10.2, k = -10;
    i += j;
    j += k;
    k += i;
    return 0;
}
