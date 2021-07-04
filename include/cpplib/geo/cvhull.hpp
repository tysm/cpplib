#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
static bool ccw(const point<T> &a, const point<T> &b, const point<T> &c)
{
    return ccw(b - a, c - b);
}

template<typename T>
static bool cw(const point<T> &a, const point<T> &b, const point<T> &c)
{
    return cw(b - a, c - b);
}

template<typename T>
tuple<vector<point<T> >, int> convex_hull(vector<point<T> > pts)
{
    int n = pts.size();
    if(n == 1)
        return {pts, 0};
    sort(all(pts));
    point<T> p1 = pts[0], p2 = pts[n - 1];
    vector<point<T> > up(1, p1), down(1, p1);
    for(int i = 1; i < n; ++i) {
        if(i == n - 1 or cw(p1, pts[i], p2)) {
            while(up.size() >= 2 and !cw(up[up.size() - 2], up[up.size() - 1], pts[i]))
                up.pop_back();
            up.emplace_back(pts[i]);
        }
        if(i == n - 1 or ccw(p1, pts[i], p2)) {
            while(down.size() >= 2 and !ccw(down[down.size() - 2], down[down.size() - 1], pts[i]))
                down.pop_back();
            down.emplace_back(pts[i]);
        }
    }
    vector<point<T> > res;
    for(auto &p: down)
        res.emplace_back(p);
    for(int i = up.size() - 2; i > 0; --i)
        res.emplace_back(up[i]);
    return {res, down.size() - 1};
}
