#pragma once
#include <cpplib/array/lcs.hpp>
#include <cpplib/stdinc.hpp>

string lcs(const string &a, const string &b)
{
    vector<int> res = lcs(vector<int>(all(a)), vector<int>(all(b)));
    return string(all(res));
}
