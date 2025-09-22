#include <iostream>
#include <string>

using namespace std;

bool contains(string arr[], int size, string el) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == el) {
            return true;
        }
    }
    return false;
}

void print(string arr[], int size, string start) {
    cout << start;
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int sizeA = 8, sizeB = 5, sizeC = 5, sizeD = 3, sizeE = 0;

    string A[] = {"а", "б", "в", "г", "е", "ё", "ж", "з"};
    string B[] = {"а", "б", "в", "е", "ж"};
    string C[] = {"а", "б", "в", "е", "ё"};
    string D[] = {"а", "в", "з"};
    string E[100];

    print(A, sizeA, "A: ");
    print(B, sizeB, "B: ");
    print(C, sizeC, "C: ");
    print(D, sizeD, "D: ");

    // Находим A ∩ B ∩ C - D
    for (int i = 0; i < sizeA; i++) {
        string el = A[i];
        if (contains(B, sizeB, el) && contains(C, sizeC, el) && !contains(D, sizeD, el)) {
            E[sizeE] = el;
            sizeE++;
        }
    }

    // Вывод результата
    print(E, sizeE, "Множество E = A ∩ B ∩ C - D: ");

    return 0;
}