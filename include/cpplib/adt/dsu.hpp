#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Disjoint Set Union.
 *
 * Tracks a set of elements partitioned
 * into a number of disjoint subsets.
 *
 * Time Complexity: O(n + m*log(n)).
 * Space Complexity: O(n).
 * Where n is the number of elements and m is the number of links between them.
 */
class DSU
{
public:
    DSU(const int set_size) :
        root(set_size), sz(set_size, 1), set_size(set_size)
    {
        iota(all(root), 0);
    }

    DSU(const int set_size, const vector<pair<int, int> > &links) :
        DSU(set_size)
    {
        for(const auto &l: links)
            merge(l.first, l.second);
    }

    /**
     * Finds the element that represents
     * the set containing x.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(1).
     * Where n is the number of tracked elements.
     */
    int find(const int x)
    {
        assert(0 <= x and x < set_size);
        return root[x] == x ? x : root[x] = find(root[x]);
    }

    /**
     * Merges the sets containing a and b.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(1).
     * Where n is the number of tracked elements.
     */
    bool merge(int a, int b)
    {
        assert(0 <= a and a < set_size);
        assert(0 <= b and b < set_size);
        a = find(a);
        b = find(b);

        if(a == b)
            return false;

        if(sz[a] < sz[b])
            swap(a, b);

        root[b] = a;
        sz[a] += sz[b];
        return true;
    }

    /**
     * Checks if two elements are in the same set.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(1).
     * Where n is the number of tracked elements.
     */
    bool same(const int a, const int b)
    {
        assert(0 <= a and a < set_size);
        assert(0 <= b and b < set_size);
        return find(a) == find(b);
    }

    /**
     * Returns the size of the set containing x.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(1).
     * Where n is the number of tracked elements.
     */
    int size(const int x)
    {
        assert(0 <= x and x < set_size);
        return sz[find(x)];
    }

private:
    vector<int> root, sz;
    int set_size;
};
