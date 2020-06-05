#pragma once
#ifndef int
#   define INT_LL
#else
#   undef int
#endif
#ifndef double
#   define DOUBLE_LD
#else
#   undef double
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#ifdef INT_LL
#   define int long long
#   define uint unsigned long long
#endif
#ifdef DOUBLE_LD
#   define double long double
#endif
using namespace std;
using namespace __gnu_pbds;

using ii = pair<int, int>;
using vi = vector<int>;
using vd = vector<double>;
using vb = vector<bool>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvd = vector<vd>;
using vvb = vector<vb>;
using vvii = vector<vii>;

#define ff first
#define ss second
#define pb push_back

#define EPS 1e-9
#define INF ((int)1e9+1)
#define MAX ((int)1e6+1)
#define M ((int)1e9+7)

#define endl "\n"
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define debug(x) (cerr << #x << " = " << (x) << endl)
#define desync() (ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL))

inline int mod(const int n, const int m = M){
    return (n%m + m)%m;
}

/**
 * Euclidean GCD.
 *
 * Time Complexity: O(log(min(a, b))).
 */
int gcd(const int a, const int b){
    if(a < 0 or b < 0)
        return gcd(abs(a), abs(b));
    if(a == 0)
        return b;
    return gcd(b%a, a);
}

/**
 * Euclidean derivated LCM.
 *
 * Time Complexity: O(log(min(a, b))).
 */
int lcm(const int a, const int b){
    // same as a*b/gcd(a, b) but avoiding overflow.
    return a/gcd(a, b)*b;
}
