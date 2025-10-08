#ifndef set_H
#define set_H

#include <iostream>

template<typename T>
struct set;

template<typename T>
struct Node {
    T value;
    Node* left;
    Node* right;
    Node* parent;

    Node(const T& val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T>
struct Iterator {
    using iterator_category = std::forward_iterator_tag; // Имитация, без <iterator>
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Node<T>* node;
    Node<T>* end_node; // для сравнения с end()

    Iterator(Node<T>* n = nullptr, Node<T>* end = nullptr) : node(n), end_node(end) {}

    T& operator*() const { return node->value; }
    T* operator->() const { return &(node->value); }

    Iterator& operator++() {
        if (node == nullptr || node == end_node) return *this;
        if (node->right) {
            node = node->right;
            while (node->left) node = node->left;
        } else {
            Node<T>* parent = node->parent;
            while (parent && node == parent->right) {
                node = parent;
                parent = parent->parent;
            }
            node = parent;
        }
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const Iterator& other) const {
        return node == other.node;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};

template<typename T>
struct set {
private:
    Node<T>* root;
    Node<T>* end_node; // фиктивный узел для end()
    size_t _size;

    void destroy_tree(Node<T>* node) {
        if (!node) return;
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }

    Node<T>* find_node(const T& value) const {
        Node<T>* curr = root;
        while (curr) {
            if (value < curr->value) {
                curr = curr->left;
            } else if (value > curr->value) {
                curr = curr->right;
            } else {
                return curr;
            }
        }
        return nullptr;
    }

    std::pair<Node<T>*, bool> insert_node(const T& value) {
        if (!root) {
            root = new Node<T>(value);
            root->parent = end_node; // родитель корня — end_node
            _size++;
            return {root, true};
        }

        Node<T>* curr = root;
        Node<T>* parent = nullptr;

        while (curr) {
            parent = curr;
            if (value < curr->value) {
                curr = curr->left;
            } else if (value > curr->value) {
                curr = curr->right;
            } else {
                return {parent, false}; // уже существует
            }
        }

        Node<T>* new_node = new Node<T>(value);
        new_node->parent = parent;

        if (value < parent->value) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        _size++;
        return {new_node, true};
    }

    void transplant(Node<T>* u, Node<T>* v) {
        if (u->parent == end_node) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v) {
            v->parent = u->parent;
        }
    }

    Node<T>* tree_minimum(Node<T>* node) {
        while (node->left) node = node->left;
        return node;
    }

    bool erase_node(Node<T>* z) {
        if (!z) return false;

        Node<T>* y = z;
        Node<T>* x;

        if (!z->left) {
            x = z->right;
            transplant(z, z->right);
        } else if (!z->right) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = tree_minimum(z->right);
            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }

        delete z;
        _size--;
        return true;
    }

    Node<T>* get_first_node() const {
        if (!root) return end_node;
        Node<T>* curr = root;
        while (curr->left) curr = curr->left;
        return curr;
    }

public:
    using iterator = Iterator<T>;

    set() : root(nullptr), end_node(new Node<T>(T())), _size(0) {
        end_node->parent = end_node->left = end_node->right = nullptr;
    }

    set(const T* arr, int N) : set() {
        for (size_t i = 0; i < N; ++i) {
            insert(arr[i]);
        }
    }

    ~set() {
        destroy_tree(root);
        delete end_node;
    }

    set& operator=(const set& other) = delete; // можно реализовать, но сложно без <utility>

    iterator begin() const {
        return iterator(get_first_node(), end_node);
    }

    iterator end() const {
        return iterator(end_node, end_node);
    }

    std::pair<iterator, bool> insert(const T& value) {
        auto result = insert_node(value);
        return { iterator(result.first, end_node), result.second };
    }

    size_t erase(const T& value) {
        Node<T>* node = find_node(value);
        if (node) {
            erase_node(node);
            return 1;
        }
        return 0;
    }

    iterator find(const T& value) const {
        Node<T>* node = find_node(value);
        return iterator(node, end_node);
    }

    bool empty() const {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }

    void clear() {
        destroy_tree(root);
        root = nullptr;
        _size = 0;
    }
};

#endif // set_H