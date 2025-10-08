#include <iostream>
#include <string>
#include <clocale>
#include "./headers/set.h"

using namespace std;

void print(const set<string>& s) {
    for (auto ch : s) cout << ch << " ";
    cout << endl;
}

void input(set<string>& s) {
    string line;
    getline(cin, line, '\n');

    for (int i = 0; i < line.size(); ) {
        unsigned char ch = line[i];
        size_t len;

        // Определяем длину UTF-8 символа по первому байту
        if ((ch & 0x80) == 0) len = 1;          // 0xxxxxxx
        else if ((ch & 0xE0) == 0xC0) len = 2;  // 110xxxxx
        else if ((ch & 0xF0) == 0xE0) len = 3;  // 1110xxxx
        else if ((ch & 0xF8) == 0xF0) len = 4;  // 11110xxx
        else len = 1; // fallback (некорректный UTF-8)

        // Ограничиваем длину размером строки
        if (i + len > line.size()) len = 1;

        s.insert(line.substr(i, len));
        i += len;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    set<string> setA;
    set<string> setB;
    set<string> setC;
    set<string> setD;
    set<string> setE;

    cout << "A: "; input(setA);
    cout << "B: "; input(setB);
    cout << "C: "; input(setC);
    cout << "D: "; input(setD);

    cout << endl;

    cout << "A: "; print(setA);
    cout << "B: "; print(setB);
    cout << "C: "; print(setC);
    cout << "D: "; print(setD);
    
    // Находим A ∩ B ∩ C - D
    for (auto chA : setA) {
        for (auto chB : setB) {
            for (auto chC : setC)
            if (chA == chB && chA == chC) setE.insert(chA);
        }
    }

    for (auto itE = setE.begin(); itE != setE.end(); itE++) {
        for (auto itD = setD.begin(); itD != setD.end(); itD++) {
            if (*itE == *itD) setE.erase(*itE);
        }
    }

    // Вывод результата
    cout << "Множество E = A ∩ B ∩ C - D: "; print(setE);

    return 0;
}