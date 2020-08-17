#pragma once
#include <cpplib/math/modop.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Rolling Hash.
 *
 * Computes the hash of a sequence of
 * integers and stores previous hashes so
 * that it is possible to perform queries
 * to find the hash of subsequences.
 *
 * Note: the base and the mod values should
 * be coprimes.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the sequence.
 */
class RollingHash
{
public:
    RollingHash() = delete;

    RollingHash(const int base, const int offset = 0, const pair<int, int> &mods = {1e9 + 7, 1e9 + 9}) :
        offset(offset), bases(mod(base, mods.first), mod(base, mods.second)), mods(mods)
    {
        assert(bases.first > 0 and bases.second > 0);
    }

    RollingHash(const vector<int> &seq, const int base, const int offset = 0, const pair<int, int> &mods = {1e9 + 7, 1e9 + 9}) :
        RollingHash(base, offset, mods)
    {
        for(int i: seq)
            emplace_back(i);
    }

    RollingHash(const string &s, const int base, const int offset = 0, const pair<int, int> &mods = {1e9 + 7, 1e9 + 9}) :
        RollingHash(vector<int>(all(s)), base, offset, mods) {}

    /**
     * Adds a sequence value to the hash.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    void emplace_back(int value)
    {
        assert(value >= offset);
        value = value - offset + 1;
        pair<int, int> values = {value % mods.first, value % mods.second};

        if(base_pows.size() == hash_table.size() - 1) {
            if(base_pows.empty())
                base_pows.emplace_back(1, 1);
            else {
                pair<int, int> aux = base_pows.back();
                aux.first = (aux.first * bases.first) % mods.first;
                aux.second = (aux.second * bases.second) % mods.second;
                base_pows.emplace_back(aux);
            }
        }
        assert(base_pows.size() >= hash_table.size());

        pair<int, int> hash = hash_table.back();
        hash.first = (((hash.first * bases.first) % mods.first) + values.first) % mods.first;
        hash.second = (((hash.second * bases.second) % mods.second) + values.second) % mods.second;
        hash_table.emplace_back(hash);
    }

    /**
     * Removes the last sequence value from the
     * hash.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    void pop_back()
    {
        assert(hash_table.size() > 1);
        hash_table.pop_back();
    }

    /**
     * Checks if it matches with another
     * RollingHash.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool match(const RollingHash &other) const
    {
        return hash_table.back() == other.hash_table.back();
    }

    /**
     * Returns the sequence hash.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    pair<int, int> hash() const
    {
        return hash_table.back();
    }

    /**
     * Computes the hash corresponding to the
     * range [l, r] of the sequence.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    pair<int, int> query(const size_t l, const size_t r) const
    {
        assert(l <= r);
        assert(r < hash_table.size() - 1);
        pair<int, int> ans = hash_table[r + 1];
        ans.first = mod(ans.first - (hash_table[l].first * base_pows[r - l + 1].first) % mods.first, mods.first);
        ans.second = mod(ans.second - (hash_table[l].second * base_pows[r - l + 1].second) % mods.second, mods.second);
        return ans;
    }

private:
    int offset;
    pair<int, int> bases, mods;
    vector<pair<int, int> > base_pows, hash_table = {{0, 0}};
};
