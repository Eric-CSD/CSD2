#include <iostream>
using namespace std;

int sumSquares(int *x)
{
  *x=*x+10;
  cout << *x<<endl;
}

int main()
{
  int getal = 52;
  cout << getal <<endl;
  sumSquares(&getal);
  cout << getal <<endl;
}
