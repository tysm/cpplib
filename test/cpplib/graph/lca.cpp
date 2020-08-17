#include <cpplib/graph/lca.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<vector<int> > adj(10);
    for(int i = 1; i < 10; ++i) {
        adj[0].emplace_back(i);
        adj[i].emplace_back(0);
    }
    LCA lca(adj, 0);
    return 0;
}
