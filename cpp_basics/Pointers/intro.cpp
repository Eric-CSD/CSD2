#include <iostream>
using namespace std;

int sumSquares(int *block)
{
int total= 0;
    for (int i=0; i<10; i++) total += block[i]*block[i];
    return total;
}

int main()
{
  // char letter = 'a';
  // char* letterPointer = &letter;
  //
  // cout << int(letter) << "\n";
  // cout << (unsigned long)letterPointer << "\n";
  //
  // *letterPointer = 'b';
  //
  // cout << *letterPointer << "\n";
  // cout << (unsigned long)letterPointer << "\n";

  int *lijst = new int[10];
  for (int i=0; i<10; i++) lijst[i] = i;
  cout << sumSquares(lijst) << endl;
  cout << *lijst << endl;
  return 0;
}
