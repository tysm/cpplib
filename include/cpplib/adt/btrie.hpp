#pragma once
#include <cpplib/adt/trie.hpp>
#include <cpplib/stdinc.hpp>

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
template<size_t B = 8 * sizeof(uint)>
class BTrie : protected Trie<2, '0'>
{
public:
    BTrie(const bool unique = true) :
        super_type(unique)
    {}

    BTrie(const vector<uint> &content, const bool unique = true) :
        super_type(unique)
    {
        for(uint x: content)
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
    void erase(const uint x, const int count = -1)
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
    int count(const uint x) const
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
    int size() const
    {
        return super_type::size();
    }

    /**
     * Returns true if the Trie is empty.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool empty() const
    {
        return super_type::empty();
    }

    /**
     * Returns true if the Trie is full.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool full() const
    {
        assert(unique);

        Node *root = this->root;
        if(!root->exists('1') or !root->exists('0'))
            return false;
        uint cnt = 1ULL<<(B-1);
        return root->next('0')->cnt == cnt and root->next('1')->cnt == cnt;
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
    friend uint operator^(const uint x, const BTrie &btrie)
    {
        if(btrie.empty())
            return 0;

        uint ans = 0;
        Node *cur = btrie.root;
        for(char c: bitset<B>(x).to_string()) {
            ans <<= 1;

            char inv = (c == '0' ? '1' : '0');
            if(cur->exists(inv)) {
                ans |= 1;
                cur = cur->next(inv);
            }
            else {
                assert(cur->exists(c));
                cur = cur->next(c);
            }
        }
        return ans;
    }

    /**
     * Computes the mex over all elements
     * of the Trie pretending that they are
     * xor x.
     *
     * Time Complexity: O(B).
     * Space Complexity: O(1).
     */
    friend uint mex(const BTrie &btrie, const uint x = 0)
    {
        assert(btrie.unique and !btrie.full());  // if full, then we can't get mex with B bits.
        if(btrie.empty())
            return 0;

        uint ans = 0, cnt = 1ULL<<(B-1);
        Node *cur = btrie.root;
        for(char c: bitset<B>(x).to_string()){
            ans <<= 1;

            if(cur == nullptr)
                continue;  // we can just fill the rest with zeroes.

            if(!cur->exists(c) or cur->next(c)->cnt < cnt)
                cur = (cur->exists(c)? cur->next(c) : nullptr);
            else{
                ans |= 1;

                char inv = (c == '0' ? '1' : '0');
                cur = (cur->exists(inv)? cur->next(inv) : nullptr);
            }
            cnt >>= 1;
        }
        return ans;
    }

private:
    using super_type = Trie<2, '0'>;
};
