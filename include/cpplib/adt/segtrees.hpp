#pragma once
#include <cpplib/adt/segtree.hpp>
#include <cpplib/adt/segtreesb.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Segment Tree S Node.
 *
 * Note: this implementation only
 * adds set operations.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<STKind K, typename T>
struct STNodeS : STNodeSB<T>
{
    using super_type = STNodeSB<T>;

    STNodeS() :
        super_type(neutral_value<T>(K)) {}

    STNodeS(const T value) :
        super_type(value) {}

    STNodeS(const STNodeS &lhs, const STNodeS &rhs) :
        super_type(merge_values<T>(K, lhs.value, rhs.value))
    {
        assert(lhs.lazy == 0 and rhs.lazy == 0);
        assert(!lhs.set.second and !rhs.set.second);
    }

    /**
     * Checks if a value matches with
     * this->value according to the
     * SegmentTreeKind.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool match(const T value) const
    {
        switch(K) {
            case RMaxQ:
                return this->value >= value;
                // return this->value > value;
            case RMinQ:
                return this->value <= value;
                // return this->value < value;
            case RSumQ:
            case RXorQ:
            default:
                assert(false);
        }
    }

    /**
     * Updates the current node according to
     * the SegmentTreeKind.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    void update(const size_t range)
    {
        if(this->set.second) {
            switch(K) {
                case RMaxQ:
                case RMinQ:
                    this->value = this->set.first;
                    break;
                case RSumQ:
                    this->value = range * this->set.first;
                    break;
                case RXorQ:
                    this->value = (range % 2) * this->set.first;
                    break;
                default:
                    assert(false);
            }
        }

        switch(K) {
            case RMaxQ:
            case RMinQ:
                this->value += this->lazy;
                break;
            case RSumQ:
                this->value += range * this->lazy;
                break;
            case RXorQ:
                break;
            default:
                assert(false);
        }

        this->lazy = 0;
        this->set = {0, false};
    }
};

template<STKind K, typename T>
using SegTreeS = SegTreeSB<STNodeS<K, T>, T>;
