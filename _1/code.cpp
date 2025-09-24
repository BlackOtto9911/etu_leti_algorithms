#include <iostream>
#include <string>
#include <clocale>

using namespace std;

string universe = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯЁ";

int f(string s) {
   if (s[1]-'0'+160 == -15) return 32; // Ё
   return s[1]-'0'+160;
}

string fb(int i) {
   return universe.substr(i*2, 2);
}

void input(unsigned long long& w) {
   string line;
   getline(cin, line, '\n');

   for (int i = 0; i < line.size(); i+=2) w |= (1LL << f(line.substr(i, 2)));
}

void show(unsigned long long w) {
   for (int i = 0; i < 33; i++) {
       std::cout << w%2;
       w /= 2;
   }
   cout << endl;
}

void print(unsigned long long w) {
   for (int i = 0; i < 33; i++) {
       if (w%2 == 1) cout << fb(i) << " ";
       w/=2;
   }
   cout << endl;
}

int main() {
   setlocale(LC_ALL, "Russian");
  
   unsigned long long wA = 0;
   unsigned long long wB = 0;
   unsigned long long wC = 0;
   unsigned long long wD = 0;
   unsigned long long wE = 0;
  
   cout << "A: "; input(wA);
   show(wA);
   cout << "B: "; input(wB);
   show(wB);
   cout << "C: "; input(wC);
   show(wC);
   cout << "D: "; input(wD);

   cout << endl;

   cout << "A: "; print(wA);
   cout << "B: "; print(wB);
   cout << "C: "; print(wC);
   cout << "D: "; print(wD);
  
   // Находим A ∩ B ∩ C - D
   wE = wA & wB & wC;
   show(wD); show(~wD);
   show(wE);

   wE = wE & (~wD);
  
   // Вывод результата
   cout << "Множество E = A ∩ B ∩ C - D: "; print(wE);

   return 0;
}
