#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/euclid.hpp>
#include <cpplib/math/number-theory/modular-arithmetic/operation.hpp>

int64_t mocked_moddiv(const int64_t a, const int64_t b, const int64_t m){
    return mod(a/b, m);
}

int32_t main(){
    random_device gen;
    uniform_int_distribution<int16_t> lhs_distribution(numeric_limits<int16_t>::min(), numeric_limits<int16_t>::max());
    uniform_int_distribution<int32_t> rhs_distribution(1, numeric_limits<int32_t>::max());
    for(int i=0; i<MAX; ++i){
        int32_t b = lhs_distribution(gen), a = lhs_distribution(gen)*b, m = rhs_distribution(gen);
        if(mod(b, m) == 0 or gcd(mod(b, m), m) != 1){
            i--;
            continue;
        }
        if(moddiv(a, b, m) != mocked_moddiv(a, b, m)){
            debug(a);
            debug(b);
            debug(m);
            debug(moddiv(a, b, m));
            debug(mocked_moddiv(a, b, m));
            assert(moddiv(a, b, m) == mocked_moddiv(a, b, m));
        }
    }
    return 0;
}
