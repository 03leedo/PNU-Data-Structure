#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string word;
    Node* left, * right, * parent;
    Node(string w) : word(w), left(nullptr), right(nullptr), parent(nullptr) {}
};

class NodeTree {
public:
    Node* root;
    NodeTree() : root(nullptr) {}
    Node* findNode(string word) {
        Node* cur = root;
        while (cur) {
            if (cur->word == word) return cur;
            if (word < cur->word) cur = cur->left;
            else cur = cur->right;
        }
        return nullptr;
    }

    void insert(string word) {
        if (!root) {
            root = new Node(word);
            return;
        }
        Node* cur = root;
        Node* p = nullptr;
        while (cur) {
            p = cur;
            if (word == cur->word) return;
            if (word < cur->word) cur = cur->left;
            else cur = cur->right;
        }
        Node* newNode = new Node(word);
        newNode->parent = p;
        if (word < p->word) p->left = newNode;
        else p->right = newNode;
    }

    void remove(string word) {
        Node* target = findNode(word);
        if (!target) return;
        while (target->left || target->right) {
            Node* replacement = nullptr;
            if (target->left) {
                replacement = target->left;
                while (replacement->right)
                    replacement = replacement->right;
            }
            else {
                replacement = target->right;
                while (replacement->left)
                    replacement = replacement->left;
            }
            target->word = replacement->word;
            target = replacement;
        }
        if (target == root)
            root = nullptr;
        else {
            if (target->parent->left == target) target->parent->left = nullptr;
            else target->parent->right = nullptr;
        }
        delete target;
    }

    void printDepth(Node* node, int target_depth, int cur_depth, bool& found) {
        if (!node) return;
        if (cur_depth == target_depth) {
            cout << node->word << " ";
            found = true;
        }
        else if (cur_depth < target_depth) {
            printDepth(node->left, target_depth, cur_depth + 1, found);
            printDepth(node->right, target_depth, cur_depth + 1, found);
        }
    }
    void printLeaf(Node* node) {
        if (!node) return;
        if (!node->left && !node->right)
            cout << node->word << " ";
        else {
            printLeaf(node->left);
            printLeaf(node->right);
        }
    }
};

int main() {
    string cmd, word;
    int depth;
    NodeTree tree;
    while (cin >> cmd) {
        if (cmd == "quit") break;
        if (cmd == "+") {
            cin >> word;
            tree.insert(word);
        }
        else if (cmd == "-") {
            cin >> word;
            tree.remove(word);
        }
        else if (cmd == "depth") {
            cin >> depth;
            bool found = false;
            tree.printDepth(tree.root, depth, 1, found);
            if (!found) cout << "NO";
            cout << "\n";
        }
        else if (cmd == "leaf") {
            tree.printLeaf(tree.root);
            cout << "\n";
        }
    }
}