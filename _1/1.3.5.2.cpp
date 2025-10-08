#include <iostream>
#include <string>
#include <clocale>
#include "./headers/list.h"
#include "./headers/set.h"

using namespace std;

string universe = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯЁ";

void init(list<string>& l) {
    int size = rand() % 40; // -> <= 33 chars in set
    int ind;
    for (int i = 0; i < size; i++) {
        ind = rand()%32+rand()%2;
        l.push_back(universe.substr(ind*2, 2));
    }
}

void removeDuplicates(list<string>& l) {
    set<string> seen;
    auto it = l.begin();
    while (it != l.end()) {
        if (seen.find(*it) != nullptr) {
            auto itt = it;
            l.erase(itt);
        } else {
            seen.insert(*it);
        }
        it++;
    }
}


void print(list<string>& l) {
    for (auto ch : l) cout << ch << " ";
    cout << endl;
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    
    list<string> listA; init(listA);
    list<string> listB; init(listB);
    list<string> listC; init(listC);
    list<string> listD; init(listD);
    list<string> listE;

    cout << endl;

    cout << "A: "; print(listA);
    cout << endl;
    cout << "B: "; print(listB);
    cout << endl;
    cout << "C: "; print(listC);
    cout << endl;
    cout << "D: "; print(listD);
    cout << endl;
    
    // Находим A ∩ B ∩ C - D
    bool found = 0;
    removeDuplicates(listA);
    for (auto chA : listA) {
        for (auto chB : listB) {
            for (auto chC : listC) {
                if (chA == chB && chA == chC) {
                    listE.push_back(chA); found = 1; break;
                }
            }
            if (found) {found = 0; break;}
        }
    }

    for (auto itE = listE.begin(); itE != listE.end(); ++itE) {
        for (auto itD = listD.begin(); itD != listD.end(); ++itD) {
            if (*itE == *itD) {listE.erase(itE); break;}
        }
    }
    

    // Вывод результата
    cout << "Множество E = A ∩ B ∩ C - D: "; print(listE);

    return 0;
}