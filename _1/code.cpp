#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <clocale>

#include <bitset>

using namespace std;

string universe = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯЁ";

struct bit {
   unsigned int bit:1;
};

void init(bit* b) {
   for (int i = 0; i < 33; i++) b[i].bit = rand() % 2;
}

void init_default(bit* b) {
   for (int i = 0; i < 33; i++) b[i].bit = 0;
}

int f(string s) {
   if (s[1]-'0'+160 == -15) return 32; // Ё
   return s[1]-'0'+160;
}

string fb(int i) {
   return universe.substr(i*2, 2);
}

void input(bit *b) {
   string line;
   getline(cin, line, '\n');

   for (int i = 0; i < line.size(); i+=2) b[f(line.substr(i, 2))].bit = 1;
}

void print(bit *b) {
   for (int i = 0; i < 33; i++) {
       if (b[i].bit == 1) cout << fb(i) << " ";
   }
   cout << endl;
}

void printBits(bit *b) {
   for (int i = 0; i < 33; i++) cout << b[i].bit << " ";
   cout << endl;
}

int main() {
   srand(time(0));
   setlocale(LC_ALL, "Russian");
  
   bit bA[33]; init(bA);
   bit bB[33]; init(bB);
   bit bC[33]; init(bC);
   bit bD[33]; init(bD);
   bit bE[33]; init_default(bE);

   cout << endl;

   // cout << "A: "; printBits(bA);
   // cout << "B: "; printBits(bB);
   // cout << "C: "; printBits(bC);
   // cout << "D: "; printBits(bD);

   cout << "A: "; print(bA);
   cout << "B: "; print(bB);
   cout << "C: "; print(bC);
   cout << "D: "; print(bD);
  
   // Находим A ∩ B ∩ C - D
   for (int i = 0; i < 33; i++) bE[i].bit = bA[i].bit && bB[i].bit && bC[i].bit;

   for (int i = 0; i < 33; i++) bE[i].bit = not (bE[i].bit <= bD[i].bit);
  
   // Вывод результата
   cout << "Множество E = A ∩ B ∩ C - D: "; print(bE);

   return 0;
}

