#pragma once
#include <cpplib/header.hpp>

enum class SegTreeKind
{
    RMaxQ,
    RMinQ,
    RSumQ,
    RXorQ,
};

class SegTree
{
public:
    struct Node {
        SegTreeKind kind;
        int val, lazy;

        Node(const SegTreeKind kind) :
            kind(kind), lazy(0)
        {
            switch(kind){
                case SegTreeKind::RMaxQ:
                    val = -INF;
                    break;
                case SegTreeKind::RMinQ:
                    val = INF;
                    break;
                case SegTreeKind::RSumQ:
                case SegTreeKind::RXorQ:
                default:
                    val = 0;
                    break;
            }
        }

        Node(const SegTreeKind kind, const int val, const int lazy = 0) :
            kind(kind), val(val), lazy(lazy) {}

        bool match(const int val) const
        {
            switch(kind){
                case SegTreeKind::RMaxQ:
                    return this->val >= val;
                    // return this->val > val;
                case SegTreeKind::RMinQ:
                    return this->val <= val;
                    // return this->val < val;
                case SegTreeKind::RSumQ:
                case SegTreeKind::RXorQ:
                default:
                    assert(false);
            }
        }

        static Node merge(const SegTreeKind kind, const Node lhs, const Node rhs)
        {
            assert(lhs.lazy == 0 and rhs.lazy == 0);
            switch(kind){
                case SegTreeKind::RMaxQ:
                    return Node(kind, max(lhs.val, rhs.val));
                case SegTreeKind::RMinQ:
                    return Node(kind, min(lhs.val, rhs.val));
                case SegTreeKind::RSumQ:
                    return Node(kind, lhs.val + rhs.val);
                case SegTreeKind::RXorQ:
                    return Node(kind, lhs.val ^ rhs.val);
                default:
                    assert(false);
            }
        }
    };

    SegTree(const SegTreeKind kind, const int arr_size) :
        kind(kind), tree(4*arr_size, Node(kind)), arr_size(arr_size) {}

    SegTree(const SegTreeKind kind, const vi &arr) :
        kind(kind), tree(4*arr.size(), Node(kind)), arr_size(arr.size())
    {
        build(0, arr_size-1, 0, arr);
    }

    int find(const int val)
    {
        return find(0, arr_size-1, 0, val);
    }

    int query(const int i)
    {
        assert(0 <= i and i < arr_size);
        return query(i, i);
    }

    int query(const int l, const int r)
    {
        assert(0 <= l and l <= r and r < arr_size);
        return query(0, arr_size-1, l, r, 0).val;
    }

    void update(const int i, const int delta)
    {
        assert(0 <= i and i < arr_size);
        update(i, i, delta);
    }

    void update(const int l, const int r, const int delta)
    {
        assert(0 <= l and l <= r and r < arr_size);
        update(0, arr_size-1, l, r, 0, delta);
    }

private:
    Node build(const int l, const int r, const int pos, const vi &arr)
    {
        if(l == r)
            return tree[pos] = Node(kind, arr[l]);

        int mid = (l + r)/2;
        return tree[pos] = Node::merge(kind, build(l, mid, 2*pos+1, arr), build(mid+1, r, 2*pos+2, arr));
    }

    int find(const int l, const int r, const int pos, const int val)
    {
        propagate(l, r, pos);

        if(!tree[pos].match(val))
            return arr_size;
        else if(l == r)
            return l;

        int mid = (l + r)/2;
        int ans = find(l, mid, 2*pos+1, val);
        return ans != arr_size? ans : find(mid+1, r, 2*pos+2, val);
    }

    Node query(const int l, const int r, const int i, const int j, const int pos)
    {
        propagate(l, r, pos);

        if(l > r or l > j or r < i)
            return Node(kind);

        if(l >= i and r <= j)
            return tree[pos];

        int mid = (l + r)/2;
        return Node::merge(kind, query(l, mid, i, j, 2*pos+1), query(mid+1, r, i, j, 2*pos+2));
    }

    Node update(const int l, const int r, const int i, const int j, const int pos, const int delta)
    {
        propagate(l, r, pos);

        if(l > r or l > j or r < i)
            return tree[pos];

        if(l >= i and r <= j){
            tree[pos].lazy = delta;
            // it's important to propagate before returning and Node::merge.
            propagate(l, r, pos);
            return tree[pos];
        }

        int mid = (l + r)/2;
        return tree[pos] = Node::merge(kind, update(l, mid, i, j, 2*pos+1, delta), update(mid+1, r, i, j, 2*pos+2, delta));
    }

    void propagate(int l, int r, int pos)
    {
        int lazy = tree[pos].lazy;

        if(lazy == 0)
            return;

        switch (kind){
            case SegTreeKind::RMaxQ:
            case SegTreeKind::RMinQ:
                tree[pos].val += lazy;
                break;
            case SegTreeKind::RSumQ:
                tree[pos].val += (r - l + 1)*lazy;
                break;
            case SegTreeKind::RXorQ:
            default:
                break;
        }
        if(l != r){
            tree[2*pos+1].lazy += lazy;
            tree[2*pos+2].lazy += lazy;
        }
        tree[pos].lazy = 0;
    }

    SegTreeKind kind;
    vector<Node> tree;
    int arr_size;
};