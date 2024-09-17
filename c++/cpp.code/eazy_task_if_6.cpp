#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;

  if (a > b) {
    cout << "Победил Деннис";
  } else if (a < b) {
    cout << "Победил Бьёрн";
  } else if (a == b) {
    cout << "Победила дружба";
  }
}