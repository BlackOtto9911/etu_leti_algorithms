#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>

template<typename T>
class list {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val = T(), Node* nxt = nullptr) : data(val), next(nxt) {}
    };

    Node* head;
    size_t _size;

public:
    // Конструкторы и деструктор
    list() : head(nullptr), _size(0) {}
    list(std::initializer_list<T> init) : head(nullptr), _size(0) {
        for (auto it = init.end(); it != init.begin(); ) {
            --it;
            push_front(*it);
        }
    }
    ~list() { clear(); }

    // Копирование и перемещение
    list(const list& other) : head(nullptr), _size(0) {
        for (const auto& elem : other) {
            push_back(elem);
        }
    }

    list& operator=(const list& other) {
        if (this != &other) {
            clear();
            for (const auto& elem : other) {
                push_back(elem);
            }
        }
        return *this;
    }

    list(list&& other) noexcept : head(other.head), _size(other._size) {
        other.head = nullptr;
        other._size = 0;
    }

    list& operator=(list&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            _size = other._size;
            other.head = nullptr;
            other._size = 0;
        }
        return *this;
    }

    // Итератор
    struct iterator {
        Node* ptr;

        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* p = nullptr) : ptr(p) {}
        T& operator*() { return ptr->data; }
        const T& operator*() const { return ptr->data; }
        T* operator->() { return &(ptr->data); }
        iterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    // Основные методы
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    bool empty() const { return head == nullptr; }
    size_t size() const { return _size; }

    T& front() { return head->data; }
    const T& front() const { return head->data; }

    T& back() {
        if (!head) throw std::out_of_range("back() called on empty list");
        Node* curr = head;
        while (curr->next) curr = curr->next;
        return curr->data;
    }
    const T& back() const {
        if (!head) throw std::out_of_range("back() called on empty list");
        Node* curr = head;
        while (curr->next) curr = curr->next;
        return curr->data;
    }

    void push_front(const T& value) {
        head = new Node(value, head);
        ++_size;
    }

    void push_back(const T& value) {
        if (!head) {
            push_front(value);
            return;
        }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = new Node(value);
        ++_size;
    }

    void pop_front() {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        delete tmp;
        --_size;
    }

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        _size = 0;
    }

    iterator insert(iterator pos, const T& value) {
        if (pos.ptr == head) {
            push_front(value);
            return iterator(head);
        }
        // Ищем предыдущий узел
        Node* prev = head;
        while (prev && prev->next != pos.ptr) {
            prev = prev->next;
        }
        if (!prev) {
            // позиция не найдена — вставляем в конец
            push_back(value);
            return iterator(prev->next);
        }
        prev->next = new Node(value, prev->next);
        ++_size;
        return iterator(prev->next);
    }

    iterator erase(iterator pos) {
        if (pos.ptr == head) {
            pop_front();
            return iterator(head);
        }
        Node* prev = head;
        while (prev && prev->next != pos.ptr) {
            prev = prev->next;
        }
        if (!prev || !pos.ptr) return end(); // невалидный итератор

        Node* toDelete = pos.ptr;
        iterator nextIt = iterator(toDelete->next);
        prev->next = toDelete->next;
        delete toDelete;
        --_size;
        return nextIt;
    }

    void swap(list& other) {
        std::swap(head, other.head);
        std::swap(_size, other._size);
    }

    // Вывод (для отладки)
    void print() const {
        Node* curr = head;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
};

// swap свободная функция
template<typename T>
void swap(list<T>& a, list<T>& b) {
    a.swap(b);
}

#endif // list_H