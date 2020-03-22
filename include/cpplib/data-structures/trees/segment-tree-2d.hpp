#pragma once
#include <cpplib/header.hpp>
#include <cpplib/data-structures/trees/segment-tree.hpp>

/**
 * Segment Tree 2D.
 *
 * Arranges data in a binary tree so that it
 * is possible to perform range queries and
 * point updates over a matrix effectively.
 *
 * Common kinds of use:
 * - Range Max Query;
 * - Range Min Query;
 * - Range Sum Query;
 * - Range Xor Query.
 *
 * Note: when the tree is constructed by
 * inserting each value one by one using
 * update, the time complexity is actually
 * O(n*m*log(n)*log(m)).
 *
 * Note: it's recommended to remove the
 * pair<T, bool> set from SegTree<K, T>::Node
 * when it's not being used since it costs
 * a bunch of time and memory mainly when
 * many Segment Trees are constructed.
 *
 * Time Complexity: O(n*m).
 * Space Complexity: O(n*m).
 * Where n is the height and m is the width of the matrix.
 */
template<SegTreeKind K, typename T>
class SegTree2D
{
public:
    SegTree2D(const size_t mat_height, const size_t mat_width) :
        tree(4*mat_height, SegTree<K, T>(mat_width)),
        mat_height(mat_height), mat_width(mat_width) {}

    SegTree2D(const vector<vector<T> > &mat) :
        SegTree2D(mat.size(), mat[0].size(), mat) {}

    SegTree2D(const size_t mat_height, const size_t mat_width, const vector<vector<T> > &mat) :
        tree(4*mat_height, SegTree<K, T>(mat_width)),
        mat_height(mat_height), mat_width(mat_width)
    {
        for(const vector<T> &arr : mat)
            assert(mat_width == arr.size());
        build(0, mat_height-1, 0, mat);
    }

    /**
     * Computes the matrix value in the ith row
     * and jth column.
     *
     * Time Complexity: O(log(n) + log(m)).
     * Where n is the height and m is the width of the matrix.
     */
    T query(const size_t i, const size_t j)
    {
        assert(i < mat_height);
        assert(j < mat_width);
        return query(i, i, j, j);
    }

    /**
     * Computes the value corresponding to the
     * row range [l1, r1] and column range
     * [l2, r2] of the matrix.
     *
     * Time Complexity: O(log(n) + log(m)).
     * Where n is the height and m is the width of the matrix.
     */
    T query(const size_t l1, const size_t r1, const size_t l2, const size_t r2)
    {
        assert(l1 <= r1 and r1 < mat_height);
        assert(l2 <= r2 and r2 < mat_width);
        return query(0, mat_height-1, l1, r1, 0, l2, r2).value;
    }

    /**
     * Updates the the matrix value in the ith
     * row and jth column according to the
     * SegmentTreeKind.
     *
     * Time Complexity: O(log(n)*log(m)).
     * Where n is the height and m is the width of the matrix.
     */
    void update(const size_t i, const size_t j, const T value)
    {
        assert(i < mat_height);
        assert(j < mat_width);
        update(0, mat_height-1, i, 0, j, value);
    }

private:
    SegTree<K, T> build(const size_t l, const size_t r, const size_t pos, const vector<vector<T> > &mat)
    {
        if(l == r)
            return tree[pos] = SegTree<K, T>(mat[l]);

        size_t mid = (l + r)/2;
        return tree[pos] = SegTree<K, T>(build(l, mid, 2*pos+1, mat), build(mid+1, r, 2*pos+2, mat));
    }

    typename SegTree<K, T>::Node query(const size_t l, const size_t r, const size_t i1, const size_t i2, const size_t pos, const size_t j1, const size_t j2)
    {
        if(l > i2 or r < i1)
            return typename SegTree<K, T>::Node();

        if(l >= i1 and r <= i2)
            return typename SegTree<K, T>::Node(tree[pos].query(j1, j2));

        size_t mid = (l + r)/2;
        return typename SegTree<K, T>::Node(query(l, mid, i1, i2, 2*pos+1, j1, j2), query(mid+1, r, i1, i2, 2*pos+2, j1, j2));
    }

    void update(const size_t l, const size_t r, const size_t i, const size_t pos, const size_t j, const T delta)
    {
        if(l > i or r < i)
            return;

        tree[pos].update(j, delta);

        if(l == i and r == i)
            return;

        size_t mid = (l + r)/2;
        update(l, mid, i, 2*pos+1, j, delta);
        update(mid+1, r, i, 2*pos+2, j, delta);
    }

    vector<SegTree<K, T> > tree;
    size_t mat_height, mat_width;
};
