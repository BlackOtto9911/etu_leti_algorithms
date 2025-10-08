#include <iostream>
#include <string>
#include <clocale>
#include "./headers/new_set.h"
#include <chrono>

using namespace std;

void input(Set<string>& s) {
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
    
    Set<string> setA;
    Set<string> setB;
    Set<string> setC;
    Set<string> setD;
    Set<string> setE;

    cout << "A: "; input(setA);
    cout << "B: "; input(setB);
    cout << "C: "; input(setC);
    cout << "D: "; input(setD);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto tt1 = clock();

    cout << endl;

    cout << "A: "; setA.print();
    cout << "B: "; setB.print();
    cout << "C: "; setC.print();
    cout << "D: "; setD.print();
    
    // Находим A ∩ B ∩ C - D
    for (const auto& ch : setA) {
        if (setB.contains(ch) && setC.contains(ch) && !setD.contains(ch)) setE.insert(ch);
    }

    // Вывод результата
    cout << "Множество E = A ∩ B ∩ C - D: "; setE.print();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto tt2 = clock();

    cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::duration<double, micro>>(t2-t1).count() << " мкс" << endl;
    cout << "Счетчик тиков: " << tt2-tt1 << endl;


    return 0;
}