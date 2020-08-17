#include <cpplib/array/lis.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<int> arr = {0, 1, 2, 2, 3, 4, 5, 6, 1, 1, 2, 3, 4, 5};
    auto res = lis(arr);
    vector<int> rst = {0, 1, 2, 3, 4, 5, 6};
    assert(rst.size() == res.size());
    for(int i = 0; i < rst.size(); ++i)
        assert(rst[i] == res[i]);
    return 0;
}
