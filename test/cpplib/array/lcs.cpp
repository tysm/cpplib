#include <cpplib/array/lcs.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<int> a = {0, 1, 2, 3}, b = a;
    auto res = lcs(a, b);
    assert(a.size() == res.size() and a.size() == b.size());
    for(int i = 0; i < a.size(); ++i)
        assert(a[i] == b[i] and a[i] == res[i]);
    return 0;
}
