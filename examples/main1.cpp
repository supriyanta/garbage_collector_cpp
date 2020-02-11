#include <iostream>
#include "../GCPtr.cpp"

int main(int argc, char const *argv[])
{
  try
  {
    GCPtr<int, 10> ap = new int[10];
    GCPtr<int>::GCiterator it = ap.begin();

    for (int i = 0; i < it.size(); ++i)
    {
      // std::cout << it[i] << " ";
      it[i] = i * 10 + 1;
    }
    // std::cout << std::endl;
    for (it = ap.begin(); it != ap.end(); ++it)
    {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }
  catch (std::bad_alloc &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
