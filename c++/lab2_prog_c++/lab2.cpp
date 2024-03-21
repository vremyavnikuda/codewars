// Функция для поиска максимального элемента в списке
#include <climits>
#include <iostream>
int findMaxElementAddress(int list[], int size) {
    int maxElement = INT_MIN;
    int address = -1;    
    for (int i = 0; i < size; i++) {
        if (list[i] > maxElement) {
            maxElement = list[i];
            address = i;
        }
    }
    return address;
}

// Функция для добавления элементов списка L2 в список L1 за первым вхождением элемента E
int addElementsAfterFirstOccurrence(int L1[], int& L1Size, int E, int L2[], int L2Size) {
    int insertIndex = -1;
    for (int i = 0; i < L1Size; i++) {
        if (L1[i] == E) {
            insertIndex = i + 1;
            break;
        }
    }
    if (insertIndex != -1) {
        for (int i = 0; i < L2Size; i++) {
            for (int j = L1Size; j > insertIndex; j--) {
                L1[j] = L1[j - 1];
            }
            L1[insertIndex++] = L2[i];
            L1Size++;
        }
    }
    return L1Size;
}

int main(){
  const int SIZE1 = 5;
  const int SIZE2 = 3;
  
  int L1[SIZE1] = {1, 2, 3, 4, 5};
  int L2[SIZE2] = {6, 7, 8};
  
  int L1Size = SIZE1;
  int L2Size = SIZE2;
  
  int maxElementAddress = findMaxElementAddress(L1, L1Size);
  
  std::cout<<"Max element address: "<<maxElementAddress<<std::endl;
  int elementToFind = 1;
  int newSize=addElementsAfterFirstOccurrence(L1, L1Size, elementToFind, L2, L2Size);
  std::cout<<"New list size: "<<newSize<<std::endl;
  return 0;
}