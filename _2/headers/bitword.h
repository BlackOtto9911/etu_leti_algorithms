#ifndef BITWORD_H
#define BITWORD_H

#include <iostream>
#include <string>
#include <stdexcept>

class BitWord {
private:
    static const size_t ALPHABET_SIZE = 33;
    std::string alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    unsigned long long data;

    // вспомогательная функция: позволяет получить индекс буквы в алфавите
    size_t getLetterIndex(char c) const {
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            if (c == alphabet[i]) {
                return i;
            }
        }
        throw std::invalid_argument("Символ не является заглавной буквой русского алфавита");
    }

public:
    // конструктор по умолчанию — пустое множество
    BitWord() : data(0) {}

    void set(char letter) {
        size_t idx = getLetterIndex(letter);
        if (idx >= 64) return;
        data |= (1ULL << idx);
    }

    void reset(char letter) {
        size_t idx = getLetterIndex(letter);
        if (idx >= 64) return;
        data &= ~(1ULL << idx);
    }

    bool test(char letter) const {
        size_t idx = getLetterIndex(letter);
        if (idx >= 64) return false;
        return (data & (1ULL << idx)) != 0;
    }

    void clear() {
        data = 0;
    }

    bool empty() const {
        return data == 0;
    }

    size_t count() const {
        size_t cnt = 0;
        unsigned long long n = data;
        while (n) {
            cnt += n & 1;
            n >>= 1;
        }
        return cnt;
    }

    void print() const {
        for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
            if (data & (1ULL << i)) {
                std::cout << alphabet.substr(i*2, 2) << " ";
            }
        }
        std::cout << std::endl;
    }

    unsigned long long getValue() const {
        return data;
    }

    BitWord operator|(const BitWord& other) const {
        BitWord result;
        result.data = this->data | other.data;
        return result;
    }
    BitWord& operator|=(unsigned long long mask) {
        data |= mask;
        return *this;
    }
    friend BitWord operator~(const BitWord& bw) {
        const unsigned long long MASK = (1ULL << 33) - 1;
        BitWord result;
        result.data = (~bw.data) & MASK;
        return result;
    }

    BitWord operator&(const BitWord& other) const {
        BitWord result;
        result.data = this->data & other.data;
        return result;
    }

    BitWord& operator|=(const BitWord& other) {
        data |= other.data;
        return *this;
    }

    BitWord& operator&=(const BitWord& other) {
        data &= other.data;
        return *this;
    }
};

#endif 