#include <iostream>
#include <string>
#include <clocale>
#include "./headers/new_list.h"

#include <chrono>

using namespace std;

void print(LinkedList<string> &l) {
    for (auto ch : l) cout << ch << " ";
    cout << endl;
}

void input(LinkedList<string> &l) {
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

        l.push_back(line.substr(i, len));
        i += len;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    LinkedList<string>* listA = new LinkedList<string>;
    LinkedList<string>* listB = new LinkedList<string>;
    LinkedList<string>* listC = new LinkedList<string>;
    LinkedList<string>* listD = new LinkedList<string>;
    LinkedList<string>* listE = new LinkedList<string>;

    cout << "A: "; input(*listA);
    cout << "B: "; input(*listB);
    cout << "C: "; input(*listC);
    cout << "D: "; input(*listD);


   auto t1 = std::chrono::high_resolution_clock::now();
   auto tt1 = clock();

    cout << endl;

    cout << "A: "; print(*listA);
    cout << "B: "; print(*listB);
    cout << "C: "; print(*listC);
    cout << "D: "; print(*listD);
    
    // Находим A ∩ B ∩ C - D
    bool found = 0;
    for (auto chA : *listA) {
        for (auto chB : *listB) {
            for (auto chC : *listC) {
                if (chA == chB && chA == chC) {
                    (*listE).push_back(chA); found = 1; break;
                }
            }
            if (found) {found = 0; break;}
        }
    }

    for (auto itE = (*listE).begin(); itE != (*listE).end(); ++itE) {
        for (auto itD = (*listD).begin(); itD != (*listD).end(); ++itD) {
            if (*itE == *itD) {(*listE).remove(*itE); break;}
        }
    }
    

    // Вывод результата
    cout << "Множество E = A ∩ B ∩ C - D: "; print((*listE));

    auto t2 = std::chrono::high_resolution_clock::now();
    auto tt2 = clock();

    delete listA;
    delete listB;
    delete listC;
    delete listD;
    delete listE;

    cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::duration<double, micro>>(t2-t1).count() << " мкс" << endl;
    cout << "Счетчик тиков: " << tt2-tt1 << endl;


    return 0;
}