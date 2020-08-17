#pragma once
#ifndef int
#    define INT_LL
#else
#    undef int
#endif
#ifndef double
#    define DOUBLE_LD
#else
#    undef double
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#ifdef INT_LL
#    define int int64_t
#    define uint uint64_t
#else
#    define uint unsigned int
#endif
#ifdef DOUBLE_LD
#    define double long double
#endif
using namespace std;
using namespace __gnu_pbds;

using ii = pair<int, int>;
using tt = tuple<int, int, int>;

using vi = vector<int>;
using vd = vector<double>;
using vb = vector<bool>;
using vii = vector<ii>;
using vtt = vector<tt>;

using vvi = vector<vi>;
using vvd = vector<vd>;
using vvb = vector<vb>;
using vvii = vector<vii>;
using vvtt = vector<vtt>;

#define ff first
#define ss second
#define ep emplace
#define eb emplace_back

#define all(x)  x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define PI   acos(-1)
#define EPS  1e-9
#define INF  ((int)2e9 + 1)
#define LINF ((int)2e18 + 1)
#define MAXN ((int)2e6 + 1)
#define MOD  ((int)1e9 + 7)

#define desync() (ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL))
#define endl     "\n"
#define debug(x) (cerr << #x << " = " << (x) << endl)

template<typename T>
ostream &operator<<(ostream &lhs, const vector<T> &rhs)
{
    if(is_floating_point<T>::value)
        lhs << fixed << setprecision(10);
    for(size_t i = 0; i < rhs.size(); ++i) {
        if(i)
            lhs << ' ';
        lhs << rhs[i];
    }
    return lhs;
}

template<typename T, size_t N>
ostream &operator<<(ostream &lhs, const array<T, N> &rhs)
{
    if(is_floating_point<T>::value)
        lhs << fixed << setprecision(10);
    for(size_t i = 0; i < rhs.size(); ++i) {
        if(i)
            lhs << ' ';
        lhs << rhs[i];
    }
    return lhs;
}
