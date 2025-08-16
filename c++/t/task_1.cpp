#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;
  int cN = 0, cS = 0, cE = 0, cW = 0;
  for (char c : s)
  {
    if (c == 'N')
      cN++;
    else if (c == 'S')
      cS++;
    else if (c == 'E')
      cE++;
    else if (c == 'W')
      cW++;
  }
  bool bX = (cE > 0) == (cW > 0);
  bool bY = (cN > 0) == (cS > 0);
  if (bX && bY)
  {
    cout << "Yes" << endl;
  }
  else
  {
    cout << "No" << endl;
  }
  return 0;
}