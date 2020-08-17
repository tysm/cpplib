#pragma once
#include <cpplib/stdinc.hpp>

struct Node
{
    Node *left = nullptr, *right = nullptr;
};

void morris(Node *root)
{
    Node *cur = root;
    while(cur != nullptr) {
        if(cur->left == nullptr) {
            // visit cur.
            cur = cur->right;
        }
        else {
            Node *pred = cur->left;
            while(pred->right != nullptr and pred->right != cur)
                pred = pred->right;
            if(pred->right == nullptr) {
                pred->right = cur;
                cur = cur->left;
            }
            else {
                pred->right = nullptr;
                // visit cur.
                cur = cur->right;
            }
        }
    }
}
