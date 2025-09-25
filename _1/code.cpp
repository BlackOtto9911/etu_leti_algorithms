#include <iostream>
#include <string>
#include <clocale>
#include <chrono>
#include "../headers/set.h"

using namespace std;

string universe = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯЁ";

void init(set<string>& s) {
    int size = 22; // -> <= 127 chars in set
    int ind;
    for (int i = 0; i < size; i++) {
        ind = rand()%32+rand()%2;
        s.insert(universe.substr(ind*2, 2));
    }
    
}

void print(set<string>& s) { 
    for (auto ch : s) cout << ch << " ";
    cout << endl;
}

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto tt1 = clock();

    srand(time(0));
    setlocale(LC_ALL, "Russian");
    
    set<string> setA; init(setA);
    set<string> setB; init(setB);
    set<string> setC; init(setC);
    set<string> setD; init(setD);
    set<string> setE; 

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

    for (auto itE = setE.begin(); itE != setE.end(); ) {
        for (auto itD = setD.begin(); itD != setD.end(); itD++) {
            if (*itE == *itD) {
                auto it = itE;
                setE.erase(*it);
                break;
            }
        }
        itE++;
    }

    // Вывод результата
    cout << "Множество E = A ∩ B ∩ C - D: "; print(setE);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto tt2 = clock();

    cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::duration<double, micro>>(t2-t1).count() << " мкс" << endl;
    cout << "Счетчик тиков: " << tt2-tt1 << endl;

    return 0;
}