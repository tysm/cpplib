#include <cpplib/math/modop.hpp>
#include <cpplib/stdinc.hpp>

int64_t mocked_modmul(const int64_t a, const int64_t b, const int64_t m)
{
    return (mod(a, m) * mod(b, m)) % m;
}

int32_t main()
{
    random_device gen;
    uniform_int_distribution<int32_t> lhs_distribution(numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    uniform_int_distribution<int32_t> rhs_distribution(1, numeric_limits<int32_t>::max());
    for(int i = 0; i < MAXN; ++i) {
        int32_t a = lhs_distribution(gen), b = lhs_distribution(gen), m = rhs_distribution(gen);
        if(modmul(a, b, m) != mocked_modmul(a, b, m)) {
            debug(a);
            debug(b);
            debug(m);
            debug(modmul(a, b, m));
            debug(mocked_modmul(a, b, m));
            assert(modmul(a, b, m) == mocked_modmul(a, b, m));
        }
    }
    return 0;
}
