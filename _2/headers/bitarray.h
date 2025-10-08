#ifndef BITARRAY_H
#define BITARRAY_H

#include <iostream>
#include <string>
#include <stdexcept>

struct Bit {
    unsigned int bit : 1; // 0 или 1

    Bit() : bit(0) {}
    Bit(unsigned int b) : bit(b & 1) {}
};

class BitArray {
private:
    static const size_t ALPHABET_SIZE = 33;
    std::string alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯЁ";
    Bit bits[ALPHABET_SIZE]; 

    // Прокси-класс для доступа к биту
    class BitProxy {
        Bit& bit_ref;
    public:
        BitProxy(Bit& b) : bit_ref(b) {}

        // Присваивание: proxy = 0 или proxy = 1
        BitProxy& operator=(unsigned int value) {
            bit_ref.bit = value & 1;
            return *this;
        }

        // Преобразование в bool (для чтения)
        operator bool() const {
            return bit_ref.bit != 0;
        }
    };

    // вспомогательная функция: позволяет получить индекс буквы в алфавите
    size_t getLetterIndex(char c) const {
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            if (c == alphabet[i]) {
                return i;
            }
        }
        throw std::invalid_argument("Символ не является буквой русского алфавита");
    }

public:

    // конструктор по умолчанию — все биты 0
    BitArray() {
        std::cout << "BitArray::BitArray() called\n";
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            bits[i].bit = 0;
        }
    }

    BitProxy operator[](size_t index) {
        std::cout << "BitArray::operator[] (non-const) called\n";
        return BitProxy(bits[index]);
    }

    bool operator[](size_t index) const {
        std::cout << "BitArray::operator[] (const) called\n";
        if (index >= ALPHABET_SIZE) return false;
        return bits[index].bit != 0;
    }

    void set(char letter) {
        std::cout << "BitArray::set() called\n";
        size_t idx = getLetterIndex(letter);
        bits[idx].bit = 1;
    }

    void reset(char letter) {
        std::cout << "BitArray::reset() called\n";
        size_t idx = getLetterIndex(letter);
        bits[idx].bit = 0;
    }

    int get(int idx) {
        std::cout << "BitArray::get() called\n";
        return bits[idx].bit;
    }

    bool test(char letter) const {
        std::cout << "BitArray::test() called\n";
        size_t idx = getLetterIndex(letter);
        return bits[idx].bit == 1;
    }

    void clear() {
        std::cout << "BitArray::clear() called\n";
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            bits[i].bit = 0;
        }
    }

    void print() const {
        std::cout << "BitArray::print() called\n";
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            if (bits[i].bit) {
                std::cout << alphabet.substr(i*2, 2) << " ";
            }
        }
        std::cout << std::endl;
    }

    bool empty() const {
        std::cout << "BitArray::empty() called\n";
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            if (bits[i].bit) return false;
        }
        return true;
    }

    size_t count() const {
        std::cout << "BitArray::count() called\n";
        size_t cnt = 0;
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            cnt += bits[i].bit;
        }
        return cnt;
    }
};


#endif 