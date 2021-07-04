#pragma once
#include <cpplib/adt/line.hpp>
#include <cpplib/adt/point.hpp>
#include <cpplib/adt/segment.hpp>
#include <cpplib/adt/triangle.hpp>
#include <cpplib/math/modop.hpp>
#include <cpplib/stdinc.hpp>
#include <cpplib/utility/signum.hpp>

// 2D convex polygon*
template<typename T>
struct polygon
{
    T _double_area = -1;
    vector<point<T> > pts;  // polygon points in ccw and pts[0] is the lowest lexi (y, x).

    template<typename T1>
    polygon(const vector<point<T1> > &hull) :
        pts(hull)
    {
        assert(!pts.empty());

        int n = pts.size();
        if(n <= 2)
            sort(all(pts), [](const point<T1> i, const point<T1> j) { return point<T1>(i.y, i.x) < point<T1>(j.y, j.x); });
        else {
            int res = 0;
            for(int i = 1; i < n; ++i) {
                if(point<T>(pts[i].y, pts[i].x) < point<T>(pts[res].y, pts[res].x))
                    res = i;
            }

            int o = zori(pts[(res + 1) % n] - pts[res], pts[mod(res - 1, n)] - pts[res]);
            if(o == 1)
                rotate(pts.begin(), pts.begin() + res, pts.end());
            else {
                rotate(pts.rbegin(), pts.rbegin() + res, pts.rend());
                reverse(all(pts));
            }
        }
    }

    // Degenerate check - O(1).
    bool is_degenerate() const
    {
        return size() <= 2;
    }

    // Area - O(n).
    double area()
    {
        if(_double_area == -1) {
            _double_area = 0;
            int n = pts.size();
            for(int i = 0, j = 1; i < n; ++i, j = (j + 1) % n)
                _double_area += (pts[i] ^ pts[j]).z;
            _double_area = abs(_double_area);
        }
        return _double_area * 0.5L;
    }

    // Size - O(1).
    size_t size() const
    {
        return pts.size();
    }

    point<T> &operator[](int pos)
    {
        if(pos < 0 or pos >= size())
            pos = mod(pos, size());
        return pts[pos];
    }

    const point<T> &operator[](int pos) const
    {
        if(pos < 0 or pos >= size())
            pos = mod(pos, size());
        return pts[pos];
    }

    // Point inside check - O(log(n)).
    template<typename T1>
    friend bool count(const polygon &pl, const point<T1> &p)
    {
        if(pl.size() == 1)
            return pl[0] == p;
        else if(pl.size() == 2)
            return count(segment<T>(pl[0], pl[1]), p);

        int l = 1, r = pl.size() - 1;
        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(ccw(pl[mid] - pl[0], p - pl[0]))  // p0->mid -> p0->p is ccw.
                l = mid;
            else
                r = mid;
        }
        return count(triangle<T>(pl[0], pl[l], pl[l + 1]), p);
    }

    // Minkowski Sum of two convex polygons - O(n+m).
    template<typename T1>
    friend auto minkowski_sum(const polygon &a, const polygon<T1> &b) -> polygon<typename common_type<T, T1>::type>
    {
        int n = a.size(), m = b.size();
        vector<point<typename common_type<T, T1>::type> > res;
        for(int i = 0, j = 0; i < n or j < m;) {
            res.emplace_back(a[i] + b[j]);

            int o = zori(a[i + 1] - a[i], b[j + 1] - b[j]);
            if(o >= 0)
                i++;
            if(o <= 0)
                j++;
        }
        return polygon<typename common_type<T, T1>::type>(res);
    }

    // Index of the extreme point to a vector 2D - O(log(n)).
    template<typename T1>
    friend int extreme(const point<T1> &v, const polygon &pl)
    {
        // it maximizes the cross product.
        int n = pl.size();
        auto vertex_cmp = [&](int i, int j) {
            return zori(pl[j] - pl[i], v);
        };
        auto is_extreme = [&](const int idx, int &isig) {
            return (isig = vertex_cmp(idx, idx + 1)) <= 0 and vertex_cmp(idx - 1, idx) > 0;
        };
        int lo = 0, losig, hi = (is_extreme(lo, losig) ? 1 : n);
        while(hi - lo > 1) {
            int mid = (lo + hi) / 2, midsig;
            if(is_extreme(mid, midsig))
                return mid;
            if(losig != midsig ? losig > midsig : losig != vertex_cmp(lo, mid))
                hi = mid;
            else {
                lo = mid;
                losig = midsig;
            }
        }
        return lo;  // lo won't ever be n, because the bsearch does not increment lo by mid.*/
    }

    // Index of the extreme points to a vector 2D - O(log(n)).
    template<typename T1>
    friend pair<int, int> extremes(const point<T1> &v, const polygon &pl)
    {
        return {extreme(v, pl), extreme(-v, pl)};
    }

    // Line intersection check - O(log(n)).
    template<typename T1>
    friend bool intersect(const line<T1> &l, const polygon &pl)
    {
        if(l.is_degenerate())
            return count(pl, l.p);

        auto vertex_cmp = [&](int idx) {
            return zori(pl[idx] - l.p, l.v);
        };

        if(pl.is_degenerate()) {  // size 1 or 2.
            int s = vertex_cmp(0);
            return !s or s != vertex_cmp(pl.size() - 1);
        }
        auto exts = extremes(l.v, pl);
        int s = vertex_cmp(exts.first);
        return !s or s != vertex_cmp(exts.second);
    }

    // Polygon intersection check - O(n).
    template<typename T1>
    friend bool intersect(const polygon<T1> &a, const polygon &b)
    {
        auto pts = b.pts;
        for(auto &p: pts) {
            p.x = -p.x;
            p.y = -p.y;
        }
        auto mksum = minkowski_sum(a, polygon<T>(pts));  // a + (-b).
        return count(mksum, point<T>(0, 0));
    }

    // Polygon distance - O(n+m).
    template<typename T1>
    friend double distance(const polygon<T1> &a, const polygon &b)
    {
        auto pts = b.pts;
        for(auto &p: pts) {
            p.x = -p.x;
            p.y = -p.y;
        }

        auto mksum = minkowski_sum(a, polygon<T>(pts));  // a + (-b).

        point<T> origin(0, 0);
        if(count(mksum, origin))
            return 0;

        int n = mksum.size();
        auto res = distance(origin, mksum[0]);
        for(int i = 0; i < n; ++i)
            res = min(res, distance(origin, segment<typename common_type<T, T1>::type>(mksum[i], mksum[i + 1])));
        return res;
    }
};
