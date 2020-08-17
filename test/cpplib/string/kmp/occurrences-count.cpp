#include <cpplib/stdinc.hpp>
#include <cpplib/string/kmp.hpp>

int32_t main()
{
    // https://cses.fi/problemset/task/1753
    desync();
    string t, p;
    cin >> t >> p;
    cout << kmp(p, t).size() << endl;
    return 0;
}
