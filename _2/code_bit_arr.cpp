#include <iostream>
#include <string>
#include <clocale>
#include "./headers/bitarray.h"

#include <chrono>

using namespace std;

int f(string s) {
    if (s[1]-'0'+160 == -15) return 32; // Ё
    return s[1]-'0'+160;
}

void input(BitArray& b) {
    string line;
    getline(cin, line, '\n');

    for (int i = 0; i < line.size(); i+=2) b[f(line.substr(i, 2))] = 1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    BitArray bA; 
    BitArray bB; 
    BitArray bC; 
    BitArray bD; 
    BitArray bE; 
    
    cout << "A: "; input(bA);
    cout << "B: "; input(bB);
    cout << "C: "; input(bC);
    cout << "D: "; input(bD);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto tt1 = clock();

    cout << endl;

    cout << "A: "; bA.print();
    cout << "B: "; bB.print();
    cout << "C: "; bC.print();
    cout << "D: "; bD.print();
    
    // Находим A ∩ B ∩ C - D
    for (int i = 0; i < 33; i++) bE[i] = bA[i] && bB[i] && bC[i]; 

    for (int i = 0; i < 33; i++) bE[i] = not (bE[i] <= bD[i]);
    
    // // Вывод результата
    cout << "Множество E = A ∩ B ∩ C - D: "; bE.print();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto tt2 = clock();

    cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::duration<double, micro>>(t2-t1).count() << " мкс" << endl;
    cout << "Счетчик тиков: " << tt2-tt1 << endl;


    return 0;
}