#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Kadane.
 *
 * Computes the max contiguous subarray
 * sum and its bounds [l, r].
 *
 * Note: to find the min contiguous subarray
 * invert the signal of the elements in arr.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the array.
 */
pair<int, pair<int, int>> kadane(const vector<int> &arr, const int low = -LINF, const int high = LINF) {
    pair<int, int> bounds(-1, -1);
    int ans = 0, acc = 0, prevl = -1;
    for(int r = 0; r < arr.size(); ++r) {
        acc += arr[r];
        if(acc < 0 or arr[r] < low or arr[r] > high) {
            acc = 0;
            prevl = r;
        }
        else if(acc > ans) {
            ans = acc;
            bounds = {prevl + 1, r};
        }
    }
    return {ans, move(bounds)};
}
