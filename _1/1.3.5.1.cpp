#include <iostream>
#include <string>
#include <clocale>
#include "./headers/set.h"

using namespace std;

string universe = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯЁ";

void init(set<string>& s) {
    int size = rand() % 128; // -> <= 127 chars in set
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

    return 0;
}