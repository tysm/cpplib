#include <cpplib/array/kadane.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    vector<int> arr = {0, 1, 301, -31231, 31, 32, 4123, -31, 132};
    auto res = kadane(arr);
    return 0;
}
