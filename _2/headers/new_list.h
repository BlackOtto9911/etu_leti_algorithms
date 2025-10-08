#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <initializer_list>  // стандартный заголовок
#include <string>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t size_;

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() {
            return current->data;
        }

        const T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size_ = 0;
    }

public:
    // конструктор по умолчанию
    LinkedList() : head(nullptr), size_(0) {
        std::cout << "LinkedList::LinkedList() called\n";
    }

    // конструктор с начальной иницализацией
    LinkedList(std::initializer_list<T> init) : head(nullptr), size_(0) {
        std::cout << "LinkedList::LinkedList(initializer_list) called\n";
        for (const T& value : init) {
            push_back(value);
        }
    }

    // деструктор
    ~LinkedList() {
        std::cout << "LinkedList::~LinkedList() called\n";
        clear();
    }

    // копирование
    LinkedList(const LinkedList& other) : head(nullptr), size_(0) {
        std::cout << "LinkedList::LinkedList(const LinkedList&) called\n";
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        std::cout << "LinkedList::operator= called\n";
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // основные методы
    Iterator begin() {
        std::cout << "LinkedList::begin() called\n";
        return Iterator(head);
    }

    Iterator begin() const {
        std::cout << "LinkedList::begin() const called\n";
        return Iterator(head);
    }

    Iterator end() {
        std::cout << "LinkedList::end() called\n";
        return Iterator(nullptr);
    }

    Iterator end() const {
        std::cout << "LinkedList::end() const called\n";
        return Iterator(nullptr);
    }

    void push_front(const T& value) {
        std::cout << "LinkedList::push_front() called\n";
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        ++size_;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        std::cout << "LinkedList::push_back() called\n";
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size_;
    }

    bool remove(const T& value) {
        std::cout << "LinkedList::remove() called\n";
        if (!head) return false;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            --size_;
            return true;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            --size_;
            return true;
        }

        return false;
    }

    bool contains(const T& value) const {
        std::cout << "LinkedList::contains() called\n";
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    size_t size() const {
        std::cout << "LinkedList::size() called\n";
        return size_;
    }

    bool empty() const {
        std::cout << "LinkedList::empty() called\n";
        return head == nullptr;
    }

    void print() const {
        std::cout << "LinkedList::print() called\n";
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};


#endif 