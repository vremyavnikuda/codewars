#include <iostream>
#include <ostream>
using namespace std;
int offer(int a, int b)
{
  int result = a + b;
  return result;
}

bool trust(bool name)
{
  bool result;
  if (name == true)
  {
    cout << "Имя есть " << endl;
    result = true;
  }
  else
  {
    cout << "Имя отсутствует" << endl;
    result = false;
  }
  return result;
}

int main()
{
  int a{};
  int b(2);
  bool flag_1 = true;
  bool flag_2 = false;

  bool num_1(5 < 3);
  cout << "Summa: " << a + b << endl;
  // при выводе флага true and false => будет выводить 0 или 1
  //  true = 1
  //  false = 0
  cout << "Флаг равен true == " << flag_1 << endl;
  cout << "Флаг равен false == " << flag_2 << endl;
  cout << (num_1 ? "Yes" : "No") << endl;
  cout << offer(2, 2) << endl;
  cout << trust(true) << endl;
}

