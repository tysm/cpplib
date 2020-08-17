#include <cpplib/graph/floyd-warshall.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<vector<int> > dis(10, vector<int>(10, LINF));
    for(int i = 0; i < 10; ++i) {
        dis[i][i] = 0;
        for(int j = i + 1; j < 10; ++j)
            dis[i][j] = 1;
    }
    dis = floyd(dis);
    return 0;
}
