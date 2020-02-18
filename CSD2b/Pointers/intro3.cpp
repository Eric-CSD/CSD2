#include <iostream>
using namespace std;
#define BLOCKSIZE 1000

class Block
{
public:
  double data[BLOCKSIZE];
};

double sumsquares_copy(Block block)
{
  double total = 0;
  for (unsigned long i=0; i<BLOCKSIZE; i++)
  {
      total = total + (block.data[i] * block.data[i]);
  }
  return total;
}

int main()
{
  Block myBlock;
  cout << sumsquares_copy(myBlock);
  return 0;
}
