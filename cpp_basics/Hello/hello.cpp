#include <iostream>
using namespace std;

class HelloWorld
{
public:
  HelloWorld(){}

  int setYear (int newYear)
  {
    year = newYear;
    return 0;
  }
  int hello()
  {
    cout << "It's the year: " << year << endl;
    return 0;
  }
  int year;
};

int main()
{
  HelloWorld hw;
  int year;
  cin >> year;
  hw.setYear(year);
  hw.hello();
  return 0;
}
