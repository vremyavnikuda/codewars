#include <iostream>
using namespace std;
int main() {
  int temp;
  cin >> temp;

  if (temp <= 0) {
    cout << "Лёд";
  } else if (temp >= 100) {
    cout << "Водяной пар";
  } else if (0 > temp < 100) {
    cout << "Жидкая вода";
  }
}