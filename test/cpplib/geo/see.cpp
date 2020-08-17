#include <cpplib/adt/point.hpp>
#include <cpplib/geo/see.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<point<int> > points;
    for(int i = 0; i < 100; ++i)
        points.eb(i, i);
    auto res = see(points);
    return 0;
}
