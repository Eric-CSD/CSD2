#include <iostream>

/*
  Assignment: complete this program by putting your code in all the locations
    that say -- your code here --

  Make sure that the program compiles and builds and check the output
    after every change.

  Tip: before you look at the output, always think ahead what you expect to
    see and then check if your assumption was correct.
 */

int main()
{
char letter = 97; // find this in the ASCII table (type 'man ascii')
char *letterpointer;

  std::cout << "Contents of the variable letter: ";
  std::cout << letter << std::endl;

  letterpointer = &letter;
  std::cout << "Contents of letterpointer: ";
  std::cout << (unsigned long)letterpointer << std::endl;

  std::cout << "Contents of what letterpointer points to: ";
  std::cout << *letterpointer << std::endl;

  *letterpointer = 'b';
  std::cout << "The variable letter has gotten a new value through letterpointer." << std::endl;
  std::cout << "Contents of what letterpointer points to: ";
  std::cout << *letterpointer << std::endl;

  std::cout << "Contents of the variable letter: ";
  std::cout << letter << std::endl;


  /*
   * Create the necessary pointer(s) and use them
   */

  unsigned short year = 2019;
  std::cout << "Contents of the variable year: ";
  std::cout << year << std::endl;

  // create a pointer to year
unsigned short* yearPointer = &year;

  std::cout << "Contents of yearpointer: ";
  std::cout << yearPointer << std::endl;

  std::cout << "Contents of what yearpointer points to: ";
  std::cout << *yearPointer << std::endl;
  // give year a new value via yearpointer
*yearPointer = 1266;

  std::cout << "Contents of the variable year: ";
  std::cout << year << std::endl;

  // create another pointer to year, named anotheryearpointer
unsigned short* anotherYearPointer = & year;

  std::cout << "Contents of anotheryearpointer: ";
  std::cout << anotherYearPointer << std::endl;

  std::cout << "Contents of what anotheryearpointer points to: ";
  std::cout << *anotherYearPointer << std::endl;

  // give year a new value via anotheryearpointer
*anotherYearPointer = 1996;

  std::cout << "Contents of year: ";
  std::cout << year << std::endl;

  std::cout << "Contents of what anotheryearpointer points to: ";
  std::cout << *anotherYearPointer << std::endl;

  anotherYearPointer++;

  std::cout << "Contents of anotheryearpointer after ++: ";
  std::cout << anotherYearPointer << std::endl;
  std::cout << "Contents of what anotheryearpointer points to after ++: ";
  std::cout << *anotherYearPointer << std::endl;


} // main()
