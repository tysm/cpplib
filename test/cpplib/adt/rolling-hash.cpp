#include <cpplib/adt/rolling-hash.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    RollingHash rh(3);
    rh.emplace_back(100);
    return 0;
}
