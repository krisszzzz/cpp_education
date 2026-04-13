#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <stack>

namespace binary_tree {

class Tree {
public:
    struct Node {
        int data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;

        explicit Node(int val) : data(val) {
            std::cout << "Node created: " << data << '\n';
        }

        ~Node() {
            std::cout << "Node deleted: " << data << '\n';
        }
    };

    std::shared_ptr<Node> root;

    void traverse_bfs();
    void traverse_dfs();
};

}  // namespace binary_tree