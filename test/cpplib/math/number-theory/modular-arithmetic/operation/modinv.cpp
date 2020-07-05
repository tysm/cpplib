#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/euclid.hpp>
#include <cpplib/math/number-theory/modular-arithmetic/operation.hpp>

int32_t main(){
    random_device gen;
    uniform_int_distribution<int32_t> lhs_distribution(numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    uniform_int_distribution<int32_t> rhs_distribution(1, numeric_limits<int32_t>::max());
    for(int i=0; i<MAX; ++i){
        int32_t a = lhs_distribution(gen), m = rhs_distribution(gen);
        if(mod(a, m) == 0 or gcd(mod(a, m), m) != 1){
            i--;
            continue;
        }
        if(modmul(mod(a, m), modinv(a, m), m) != 1){
            debug(a);
            debug(m);
            debug(modinv(a, m));
            debug(modmul(mod(a, m), modinv(a, m)));
            assert(modmul(mod(a, m), modinv(a, m)) == 1);
        }
    }
    return 0;
}
