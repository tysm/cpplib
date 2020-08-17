#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    point<int> i, j = {0, 1, 3};
    i += j;
    j -= i;
    return 0;
}
