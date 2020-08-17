#include <cpplib/graph/kruskal.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<tuple<int, int, int> > edges;
    for(int i = 0; i < 10; ++i) {
        for(int j = i + 1; j < 10; ++j)
            edges.emplace_back(31, i, j);
    }
    auto res = kruskal(10, edges);
    return 0;
}
