#include <cpplib/adt/point.hpp>
#include <cpplib/adt/segment.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    point<int> p(1, 1), q(2, 2);
    segment<int> s(p, q);
    assert(count(s, p));
    return 0;
}
