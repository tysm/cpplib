#include <cpplib/graph/morris.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    Node *root = new Node();
    root->left = new Node();
    root->left->left = new Node();
    root->left->right = new Node();
    root->right = new Node();
    root->right->left = new Node();
    root->right->right = new Node();
    morris(root);
    return 0;
}
