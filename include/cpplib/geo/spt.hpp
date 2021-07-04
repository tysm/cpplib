#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/adt/polygon.hpp>
#include <cpplib/geo/cvhull.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
struct StaticPolygon
{
    int bin = 0;
    vector<polygon<T> > pol;

    void add(const point<T> &p)
    {
        vector<point<T> > cst(1, p);   // cast.
        for(int k = 0; k < 20; ++k) {  // up to 1e6 insertions...
            if(!((bin >> k) & 1)) {
                auto pts = get<0>(convex_hull(cst));
                if(k >= pol.size())
                    pol.emplace_back(pts);
                else
                    pol[k] = polygon<T>(pts);
                break;
            }
            else {
                for(const auto &i: pol[k].pts)
                    cst.emplace_back(i);
            }
        }
        bin++;
    }

    T solve(point<T> &p)
    {
        assert(bin);

        T ans;
        bool ok = false;
        point<T> v(-p.y, p.x);  // rotate by 90º.
        for(int k = 0; k < pol.size(); ++k) {
            if(!((bin >> k) & 1))
                continue;

            auto e = extremes(v, pol[k]);
            if(!ok) {
                ans = p * pol[k][e.first];
                ok = true;
            }
            ans = max(ans, p * pol[k][e.first]);
            ans = max(ans, p * pol[k][e.second]);
        }
        return ans;
    }
};

template<typename T>
using solygon = StaticPolygon<T>;
