#include <cpplib/math/modop.hpp>
#include <cpplib/stdinc.hpp>

int64_t mocked_mod(const int64_t a, const int64_t m)
{
    return (a % m + m) % m;
}

int32_t main()
{
    random_device gen;
    uniform_int_distribution<int32_t> lhs_distribution(numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    uniform_int_distribution<int32_t> rhs_distribution(1, numeric_limits<int32_t>::max());
    for(int i = 0; i < MAXN; ++i) {
        int64_t a = lhs_distribution(gen), m = rhs_distribution(gen);
        if(mod(a, m) != mocked_mod(a, m)) {
            debug(a);
            debug(m);
            debug(mod(a, m));
            debug(mocked_mod(a, m));
            assert(mod(a, m) == mocked_mod(a, m));
        }
    }
    return 0;
}
