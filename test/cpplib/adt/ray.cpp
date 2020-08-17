#include <cpplib/adt/point.hpp>
#include <cpplib/adt/ray.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    point<int> p(1, 1), v(2, 2);
    ray<int> r(p, v);
    auto at = r.at(100);
    return 0;
}
