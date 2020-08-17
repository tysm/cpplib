#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Trie.
 *
 * Stores string prefixes in a search tree
 * so that common prefixes share the same
 * nodes/path.
 *
 * Time Complexity: O(m * n).
 * Space Complexity: O(m * n).
 * Where m is the amount of strings and n is the largest string size.
 */
template<size_t K = 26, char O = 'a'>
class Trie
{
public:
    /**
     * Trie Node.
     *
     * Stores transition information
     * dynamically.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    struct Node
    {
        int cnt = 0, words = 0;
        Node *trans[K] = {};

        /**
         * Creates the transition to the node that
         * represents c in the current path + c.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        void insert(const char c)
        {
            assert(!has(c));
            trans[c - O] = new Node();
        }

        /**
         * Returns the node that represents c in
         * the current path + c.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        Node *next(const char c) const
        {
            assert(has(c));
            return trans[c - O];
        }

        /**
         * Checks if the transition to the node
         * that represents c in the
         * current path + c already exists.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        bool has(const char c) const
        {
            return trans[c - O] != nullptr;
        }

        /**
         * Checks if the transition to the node
         * that represents c in the
         * current path + c already exists and is
         * valid.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        bool exists(const char c) const
        {
            return has(c) and trans[c - O]->cnt != 0;
        }
    };

    Trie() {}

    Trie(const vector<string> &content)
    {
        for(const string &s: content)
            insert(s);
    }

    /**
     * Inserts a string into the Trie.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     * Where n is the string size.
     */
    void insert(const string &s)
    {
        Node *cur = root;
        cur->cnt++;
        for(char c: s) {
            if(!cur->has(c))
                cur->insert(c);
            cur = cur->next(c);
            cur->cnt++;
        }
        cur->words++;
    }

    /**
     * Erases occurrences of a string from the
     * Trie.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(1).
     * Where n is the string size.
     */
    void erase(const string &s, const int count = -1)
    {
        int words = this->count(s);
        if(count != -1)
            words = min(words, count);

        if(words == 0)
            return;

        Node *cur = root;
        cur->cnt -= words;
        for(char c: s) {
            cur = cur->next(c);
            cur->cnt -= words;
        }
        cur->words -= words;
    }

    /**
     * Counts the occurrences of a string in
     * the Trie.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(1).
     * Where n is the string size.
     */
    int count(const string &s) const
    {
        Node *cur = node_at(s);
        return cur == nullptr ? 0 : cur->words;
    }

    /**
     * Returns the amount of strings in the
     * Trie with prefix s.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(1).
     * Where n is the string size.
     */
    int size(const string &s) const
    {
        Node *cur = node_at(s);
        return cur == nullptr ? 0 : cur->cnt;
    }

    /**
     * Returns the node that represents the
     * path taken in the Trie following a
     * string.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(1).
     * Where n is the string size.
     */
    Node *node_at(const string &s) const
    {
        Node *cur = root;
        for(char c: s) {
            if(!cur->exists(c))
                return nullptr;
            cur = cur->next(c);
        }
        return cur;
    }

    /**
     * Returns the amount of strings in the
     * Trie.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    int size() const
    {
        return root->cnt;
    }

protected:
    Node *root = new Node();
};
