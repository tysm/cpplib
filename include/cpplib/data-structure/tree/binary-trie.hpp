#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structure/tree/trie.hpp>

/**
 * Binary Trie.
 *
 * Stores prefixes of binary
 * representations of non-negative integers
 * in a search tree so that common prefixes
 * share the same nodes/path.
 *
 * Time Complexity: O(n * B).
 * Space Complexity: O(n * B).
 * Where n is the amount of non-negative integers.
 */
template<size_t B = 8*sizeof(uint)>
class BTrie : protected Trie<2, '0'>
{
public:
    BTrie() {}

    BTrie(const vector<uint> &content)
    {
        for(uint x : content)
            insert(x);
    }

    /**
     * Inserts the binary representation of a
     * non-negative integer into the Trie.
     *
     * Time Complexity: O(B).
     * Space Complexity: O(B).
     */
    void insert(const uint x)
    {
        super_type::insert(bitset<B>(x).to_string());
    }

    /**
     * Erases occurrences of the binary
     * representation of a non-negative integer
     * from the Trie.
     *
     * Time Complexity: O(B).
     * Space Complexity: O(1).
     */
    void erase(const uint x, const size_t count = -1)
    {
        super_type::erase(bitset<B>(x).to_string(), count);
    }

    /**
     * Counts the occurrences of the binary
     * representation of a non-negative integer
     * in the Trie.
     *
     * Time Complexity: O(B).
     * Space Complexity: O(1).
     */
    size_t count(const uint x) const
    {
        return super_type::count(bitset<B>(x).to_string());
    }

    /**
     * Returns the amount of binary
     * representations of non-negative integers
     * in the Trie.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    size_t size() const
    {
        return super_type::size();
    }

    /**
     * Computes the maximum xor value of a
     * non-negative integer with the
     * non-negative integers represented in the
     * Trie.
     *
     * Time Complexity: O(B).
     * Space Complexity: O(1).
     */
    friend uint operator^(const uint x, const BTrie<B> &other)
    {
        if(other.size() == 0)
            return 0;

        uint ans = 0;
        Node* cur = other.root;
        for(char c : bitset<B>(x).to_string()){
            ans <<= 1;
            char inv = (c == '0'? '1' : '0');
            if(cur->exists(inv)){
                ans |= 1;
                cur = cur->next(inv);
            }
            else{
                assert(cur->exists(c));
                cur = cur->next(c);
            }
        }
        return ans;
    }

private:
    using super_type = Trie<2, '0'>;
};
