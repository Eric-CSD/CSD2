#include <iostream>
using namespace std;

int main()
{
  char letter = 'a';
  char* letterPointer = &letter;

  cout << int(letter) << "\n";
  cout << (unsigned long)letterPointer << "\n";

  *letterPointer = 'b';

  cout << *letterPointer << "\n";
  cout << (unsigned long)letterPointer << "\n";
  return 0;
}
