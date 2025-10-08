#include <iostream>
#include <string>
#include <clocale>
#include "./headers/bitword.h"

#include <chrono>

using namespace std;

int f(string s) {
   if (s[1]-'0'+160 == -15) return 32; // Ё
   return s[1]-'0'+160;
}

void input(BitWord& w) {
   string line;
   getline(cin, line, '\n');

   for (int i = 0; i < line.size(); i+=2) w |= (1LL << f(line.substr(i, 2)));
}

int main() {
   setlocale(LC_ALL, "Russian");
  
   BitWord wA;
   BitWord wB;
   BitWord wC;
   BitWord wD;
   BitWord wE;

   cout << "A: "; input(wA);
   cout << "B: "; input(wB);
   cout << "C: "; input(wC);
   cout << "D: "; input(wD);

   auto t1 = std::chrono::high_resolution_clock::now();
   auto tt1 = clock();


   cout << endl;

   cout << "A: "; wA.print();
   cout << "B: "; wB.print();
   cout << "C: "; wC.print();
   cout << "D: "; wD.print();
  
   // Находим A ∩ B ∩ C - D
   wE = wA & wB & wC;

   wE = wE & (~wD);
  
   // Вывод результата
   cout << "Множество E = A ∩ B ∩ C - D: "; wE.print();


    auto t2 = std::chrono::high_resolution_clock::now();
    auto tt2 = clock();

    cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::duration<double, micro>>(t2-t1).count() << " мкс" << endl;
    cout << "Счетчик тиков: " << tt2-tt1 << endl;


   return 0;
}
