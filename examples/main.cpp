#include <iostream>
#include "../src/GCPtr.cpp"

int main(int argc, char const *argv[])
{
  GCPtr<int> p;
  p = new int(45);
  std::cout << *p << std::endl;
  return 0;
}
