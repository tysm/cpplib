#pragma once
#ifndef int
#    define INT_LL
#else
#    undef int
#endif
#ifdef double
#    define DOUBLE_LD
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

#define sqrt(x) sqrtl(x)

#define all(x)         x.begin(), x.end()
#define rall(x)        x.rbegin(), x.rend()
#define rep(x, st, nd) for(int x = st; (nd >= st ? x < nd : x > nd); (nd >= st ? ++x : --x))

#define PI   acosl(-1)
#define EPS  1e-9L
#define INF  ((int)2e9 + 1)
#define LINF ((int)2e18 + 1)
#define MAXN ((int)2e6 + 1)
#define MOD  ((int)1e9 + 7)

#define desync() (ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL))
#define endl     "\n"

void debug_it()
{
    cerr << endl;
}
template<typename Head, typename... Tail>
void debug_it(Head H, Tail... T)
{
    cerr << ' ' << H;
    debug_it(T...);
}

#ifdef TYSM_DEBUG
#    define debug(...) (cerr << #    __VA_ARGS__ << " =", debug_it(__VA_ARGS__))
#else
#    define debug(...)
#endif

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

template<typename T1, typename T2>
ostream &operator<<(ostream &lhs, const pair<T1, T2> &rhs)
{
    if(is_floating_point<T1>::value or is_floating_point<T2>::value)
        lhs << fixed << setprecision(10);
    lhs << rhs.first << ' ' << rhs.second;
    return lhs;
}
