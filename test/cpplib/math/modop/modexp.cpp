#include <cpplib/math/modop.hpp>
#include <cpplib/stdinc.hpp>

int64_t mocked_modexp(const int64_t b, const int64_t e, const int64_t m)
{
    int64_t res = 1;
    for(int64_t i = 0; i < e; ++i)
        res = modmul(res, b, m);
    return res;
}

int32_t main()
{
    random_device gen;
    uniform_int_distribution<uint8_t> lhs_distribution(0, numeric_limits<uint8_t>::max());
    uniform_int_distribution<int32_t> rhs_distribution(1, numeric_limits<int32_t>::max());
    for(int i = 0; i < MAXN; ++i) {
        int32_t b = lhs_distribution(gen), e = lhs_distribution(gen), m = rhs_distribution(gen);
        if(modexp(b, e, m) != mocked_modexp(b, e, m)) {
            debug(b);
            debug(e);
            debug(m);
            debug(modexp(b, e, m));
            debug(mocked_modexp(b, e, m));
            assert(modexp(b, e, m) == mocked_modexp(b, e, m));
        }
    }
    return 0;
}
