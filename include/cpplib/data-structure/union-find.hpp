#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Union Find.
 *
 * Tracks a set of elements partitioned
 * into a number of disjoint subsets.
 *
 * Time Complexity: O(n + m*log(n)).
 * Space Complexity: O(n).
 * Where n is the number of elements and m is the number of links between them.
 */
class UnionFind
{
public:
    UnionFind(const size_t set_size) :
        root(vector<size_t>(set_size)), sz(vector<size_t>(set_size, 1)), set_size(set_size)
    {
        iota(all(root), 0);
    }

    UnionFind(const size_t set_size, const vector<pair<size_t, size_t> > &links) :
        UnionFind(set_size)
    {
        for(const pair<size_t, size_t> &l : links)
            merge(l.ff, l.ss);
    }

    /**
     * Finds the element that represents
     * the set containing x.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(1).
     * Where n is the number of tracked elements.
     */
    size_t find(const size_t x)
    {
        assert(x < set_size);
        return root[x] == x? x : root[x] = find(root[x]);
    }

    /**
     * Merges the sets containing a and b.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(1).
     * Where n is the number of tracked elements.
     */
    bool merge(size_t a, size_t b)
    {
        assert(a < set_size and b < set_size);
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
    bool same(const size_t a, const size_t b)
    {
        assert(a < set_size and b < set_size);
        return find(a) == find(b);
    }

    /**
     * Returns the size of the set containing x.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(1).
     * Where n is the number of tracked elements.
     */
    size_t size(const size_t x)
    {
        assert(x < set_size);
        return sz[find(x)];
    }

private:
    vector<size_t> root, sz;
    size_t set_size;
};
