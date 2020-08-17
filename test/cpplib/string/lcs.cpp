#include <cpplib/stdinc.hpp>
#include <cpplib/string/lcs.hpp>

int32_t main()
{
    assert("abc" == lcs("abc", "abc"));
    return 0;
}
