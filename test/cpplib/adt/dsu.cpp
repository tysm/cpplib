#include <cpplib/adt/dsu.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    int sz = 10;
    DSU dsu(sz);
    for(int i = 0; i < sz; ++i) {
        for(int j = 0; j < sz; ++j)
            dsu.merge(i, j);
    }
    return 0;
}
