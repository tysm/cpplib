#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Rolling Hash.
 *
 * Computes the hash of a sequence of
 * integers and stores previous hashes so
 * that it is possible to perform queries
 * to find the hash of subsequences.
 *
 * Note: the base and the mod values must
 * be primes.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the sequence.
 */
class RollingHash
{
public:
    RollingHash() = delete;

    RollingHash(const uint base, const pair<uint, uint> &mod_values = {1e9+7, 1e9+9}) :
        base(base), mod_values(mod_values) {}

    RollingHash(const vi &seq, const uint base, const pair<uint, uint> &mod_values = {1e9+7, 1e9+9}) :
        RollingHash(base, mod_values)
    {
        for(int i : seq)
            push_back(i);
    }

    /**
     * Adds a sequence value to the hash.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    void push_back(const uint value)
    {
        assert(value < base);
        if(base_pows.size() == hash_table.size()-1){
            if(base_pows.empty())
                base_pows.pb({1, 1});
            else{
                pair<uint, uint> aux = base_pows.back();
                aux.ff = (aux.ff*base)%mod_values.ff;
                aux.ss = (aux.ss*base)%mod_values.ss;
                base_pows.pb(aux);
            }
        }
        assert(base_pows.size() >= hash_table.size());

        pair<uint, uint> hash = hash_table.back();
        hash.ff = (hash.ff*base + value) % mod_values.ff;
        hash.ss = (hash.ss*base + value) % mod_values.ss;
        hash_table.pb(hash);
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
    pair<uint, uint> hash() const
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
    pair<uint, uint> query(const size_t l, const size_t r) const
    {
        assert(l <= r); assert(r < hash_table.size()-1);
        pair<uint, uint> ans = hash_table[r+1];
        ans.ff = mod(ans.ff - hash_table[l].ff*base_pows[r - l + 1].ff, mod_values.ff);
        ans.ss = mod(ans.ss - hash_table[l].ss*base_pows[r - l + 1].ss, mod_values.ss);
        return ans;
    }

private:
    uint base;
    pair<uint, uint> mod_values;
    vector<pair<uint, uint> > hash_table = {{0, 0}};
    vector<pair<uint, uint> > base_pows;
};
