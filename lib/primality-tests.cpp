#include <cpplib/math/primality-tests>

u64 ubexpm(u64 b, u64 e, u64 m){
    b %= m;
    u64 res = 1;
    while(e > 0){
        if(e & 1)
            res = ((u128)res*b)%m;
        b = ((u128)b*b)%m;
        e >>= 1;
    }
    return res;
}

/**
 * Miller-Rabin Deterministic Test.
 *
 * Returns true when n is prime,
 * false otherwise.
 *
 * Time Complexity: O(log(n)).
 */
bool isprimel(u64 n){
    if(n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while((d & 1) == 0){
        r++;
        d >>= 1;
    }

    for(int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == i)
            return true;

        u64 x = ubexpm(i, d, n);
        if(x == 1 or x == n - 1)
            continue;

        bool check = true;
        for(int j=1; j<r and check; ++j){
            x = ((u128)x*x)%n;
            if(x == n - 1)
                check = false;
        }
        if(check)
            return false;
    }
    return true;
}