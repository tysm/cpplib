#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

#ifdef double
using ldouble = double;
#else
using ldouble = long double;
#endif

template<typename T>
pair<double, pair<int, int> > closest_pair(const vector<point<T> > &arr)
{
    // assuming arr is ordered by x.
    int n = arr.size();

    ldouble dis = 9e18;  // long int
    pair<int, int> res(-1, -1);

    set<pair<point<double>, int> > s;  // point<int>
    for(int i = 0, j = 0; i < n; ++i) {
        double d = ceil(sqrtl(dis));  // int
        while(arr[i].x - arr[j].x > dis - EPS) {
            s.erase({point<T>(arr[j].y, arr[j].x), j});
            j++;
        }

        auto it1 = s.lower_bound({point<double>(arr[i].y - d, arr[i].x), -1});  // point<int>
        auto it2 = s.lower_bound({point<double>(arr[i].y + d, arr[i].x), -1});  // point<int>

        for(auto it = it1; it != it2; ++it) {
            T dx = arr[i].x - it->first.y;
            T dy = arr[i].y - it->first.x;
            ldouble cur = 1.0L * dx * dx + 1.0L * dy * dy;  // 1LL 1LL
            if(cur <= dis - EPS) {
                dis = cur;
                res = {it->second, i};
            }
        }
        s.emplace(point<double>(arr[i].y, arr[i].x), i);  // point<int>
    }
    return {sqrtl(dis), res};
}
