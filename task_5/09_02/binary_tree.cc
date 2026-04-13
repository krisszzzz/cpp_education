#include "binary_tree.h"

namespace binary_tree {

void Tree::traverse_bfs() {
    if (!root) {
        return;
    }
    std::queue<std::shared_ptr<Node>> q;
    q.push(root);
    std::cout << "BFS: ";
    while (!q.empty()) {
        std::shared_ptr<Node> current = q.front();
        q.pop();
        std::cout << current->data << ' ';
        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
    std::cout << '\n';
}

void Tree::traverse_dfs() {
    if (!root) {
        return;
    }
    std::stack<std::shared_ptr<Node>> s;
    s.push(root);
    std::cout << "DFS: ";
    while (!s.empty()) {
        std::shared_ptr<Node> current = s.top();
        s.pop();
        std::cout << current->data << ' ';
        if (current->right) {
            s.push(current->right);
        }
        if (current->left) {
            s.push(current->left);
        }
    }
    std::cout << '\n';
}

}  // namespace binary_tree

int main() {
    using namespace binary_tree;

    Tree tree;

    tree.root = std::make_shared<Tree::Node>(1);

    tree.root->left = std::make_shared<Tree::Node>(2);
    tree.root->right = std::make_shared<Tree::Node>(3);
    tree.root->left->parent = tree.root;
    tree.root->right->parent = tree.root;

    tree.root->left->left = std::make_shared<Tree::Node>(4);
    tree.root->left->right = std::make_shared<Tree::Node>(5);
    tree.root->left->left->parent = tree.root->left;
    tree.root->left->right->parent = tree.root->left;

    tree.root->right->left = std::make_shared<Tree::Node>(6);
    tree.root->right->right = std::make_shared<Tree::Node>(7);
    tree.root->right->left->parent = tree.root->right;
    tree.root->right->right->parent = tree.root->right;

    tree.traverse_bfs();
    tree.traverse_dfs();

    return 0;
}