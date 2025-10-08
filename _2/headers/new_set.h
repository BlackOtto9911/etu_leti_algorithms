#ifndef SET_H
#define SET_H

#include <iostream>
#include <initializer_list>

template <typename T>
class Set {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    class Iterator {
    private:
        static const int MAX_HEIGHT = 64;
        Node* stack[MAX_HEIGHT];
        int top;

        void pushLeft(Node* node) {
            while (node && top < MAX_HEIGHT) {
                stack[top++] = node;
                node = node->left;
            }
        }

    public:
        Iterator(Node* root = nullptr) : top(0) {
            pushLeft(root);
        }

        T& operator*() {
            return stack[top - 1]->data;
        }

        const T& operator*() const {
            return stack[top - 1]->data;
        }

        Iterator& operator++() {
            if (top <= 0) return *this;
            Node* current = stack[--top];
            pushLeft(current->right);
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            if (top == 0 && other.top == 0) return false;
            if (top == 0 || other.top == 0) return true;
            return stack[top - 1] != other.stack[other.top - 1];
        }
    };

    // вспомогательные функции 
    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    bool contains(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return contains(node->left, value);
        return contains(node->right, value);
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, const T& value) {
        if (!node) return node;
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    void inorder(Node* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    // конструктор 
    Set() : root(nullptr) {
        std::cout << "Set::Set() called\n";
    }

    // конструктор с начальной инициалиацией
    Set(std::initializer_list<T> init) : root(nullptr) {
        std::cout << "Set::Set(initializer_list) called\n";
        for (const T& value : init) {
            insert(value);
        }
    }

    // деструктор
    ~Set() {
        std::cout << "Set::~Set() called\n";
        destroy(root);
    }

    Iterator begin() const {
        std::cout << "Set::begin() called\n";
        return Iterator(root);
    }

    Iterator end() const {
        std::cout << "Set::end() called\n";
        return Iterator(nullptr);
    }

    // методы интерфейса
    void insert(const T& value) {
        std::cout << "Set::insert() called\n";
        root = insert(root, value);
    }

    void remove(const T& value) {
        std::cout << "Set::remove() called\n";
        root = remove(root, value);
    }

    bool contains(const T& value) const {
        std::cout << "Set::contains() called\n";
        return contains(root, value);
    }

    void print() const {
        std::cout << "Set::print() called\n";
        inorder(root);
        std::cout << std::endl;
    }

    bool empty() const {
        std::cout << "Set::empty() called\n";
        return root == nullptr;
    }
};


#endif 