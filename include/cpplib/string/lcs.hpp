#pragma once
#include <cpplib/array/lcs.hpp>
#include <cpplib/stdinc.hpp>

string lcs(const string &a, const string &b) {
    vector<int> arr_a, arr_b;
    for(char c: a)
        arr_a.emplace_back(c);
    for(char c: b)
        arr_b.emplace_back(c);
    string res;
    for(char c: lcs(arr_a, arr_b))
        res += c;
    return res;
}
