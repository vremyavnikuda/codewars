#include <complex>
#include <iostream>
using namespace std;
int main() {
  double a;
  cin >> a;
  double result = std::sqrt(a);
  cout << "У этого монитора сторона " << result << " пикселей";
}