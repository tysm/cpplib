#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/modular-arithmetic/operation.hpp>

int64_t mocked_modadd(const int64_t a, const int64_t b, const int64_t m){
    return (mod(a, m) + mod(b, m))%m;
}

int32_t main(){
    random_device gen;
    uniform_int_distribution<int32_t> lhs_distribution(numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    uniform_int_distribution<int32_t> rhs_distribution(1, numeric_limits<int32_t>::max());
    for(int i=0; i<MAX; ++i){
        int64_t a = lhs_distribution(gen), b = lhs_distribution(gen), m = rhs_distribution(gen);
        if(modadd(a, b, m) != mocked_modadd(a, b, m)){
            debug(a);
            debug(b);
            debug(m);
            debug(modadd(a, b, m));
            debug(mocked_modadd(a, b, m));
            assert(modadd(a, b, m) == mocked_modadd(a, b, m));
        }
    }
    return 0;
}
