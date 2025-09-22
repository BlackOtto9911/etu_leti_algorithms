#include <iostream>
#include <string>
#include "../headers/set.h"

using namespace std;

void print(const set<string>& s) {
    for (auto ch : s) cout << ch << " ";
    cout << endl;
}

int main() {
    int sizeA = 8, sizeB = 5, sizeC = 5, sizeD = 0;

    string A[] = {"а", "б", "в", "г", "е", "ё", "ж", "з"};
    string B[] = {"а", "б", "в", "е", "ж"};
    string C[] = {"а", "б", "в", "е", "ё"};
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
    for (auto ch : setA) {
        if (setB.find(ch) != nullptr && setC.find(ch) != nullptr && setD.find(ch) == nullptr) setE.insert(ch);
    }

    // Вывод результата
    cout << "Множество E = A ∩ B ∩ C - D: "; print(setE);

    return 0;
}