#include <cpplib/math/modop.hpp>
#include <cpplib/stdinc.hpp>

int64_t mocked_modsub(const int64_t a, const int64_t b, const int64_t m)
{
    return mod((int64_t)mod(a, m) - (int64_t)mod(b, m), m);
}

int32_t main()
{
    random_device gen;
    uniform_int_distribution<int32_t> lhs_distribution(numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    uniform_int_distribution<int32_t> rhs_distribution(1, numeric_limits<int32_t>::max());
    for(int i = 0; i < MAXN; ++i) {
        int32_t a = lhs_distribution(gen), b = lhs_distribution(gen), m = rhs_distribution(gen);
        if(modsub(a, b, m) != mocked_modsub(a, b, m)) {
            debug(a);
            debug(b);
            debug(m);
            debug(modsub(a, b, m));
            debug(mocked_modsub(a, b, m));
            assert(modsub(a, b, m) == mocked_modsub(a, b, m));
        }
    }
    return 0;
}
