#include <iostream>
#include <string>
#include "./headers/set.h"

using namespace std;

void print(const set<string>& s) {
    for (auto ch : s) cout << ch << " ";
    cout << endl;
}

int main() {
    int sizeA = 5, sizeB = 5, sizeC = 8, sizeD = 0;

    string A[] = {"а", "б", "в", "е", "ё"};
    string B[] = {"а", "б", "в", "е", "ж"};
    string C[] = {"а", "б", "в", "г", "е", "ё", "ж", "з"};
    string D[] = {};
    
    set<string> setA(A, sizeA);
    set<string> setB(B, sizeB);
    set<string> setC(C, sizeC);
    set<string> setD(D, sizeD);
    set<string> setE;

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