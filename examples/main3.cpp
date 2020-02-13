#include <iostream>
#include <new>
#include "../src/GCPtr.cpp"

using namespace std;

class MyClass
{
  int a, b;

public:
  double val;
  MyClass() { a = b = 0; }
  MyClass(int x, int y)
  {
    a = x;
    b = y;
    val = 0.0;
  }
  ~MyClass()
  {
    cout << "Destructing MyClass(" << a << ", " << b << ")\n";
  }
  int sum()
  {
    return a + b;
  }
  friend ostream &operator<<(ostream &strm, MyClass &obj);
};
// Create an inserter for MyClass.
ostream &operator<<(ostream &strm, MyClass &obj)
{
  strm << "(" << obj.a << " " << obj.b << ")";
  return strm;
}
// Pass a normal pointer to a function.
void passPtr(int *p)
{
  cout << "Inside passPtr(): "
       << *p << endl;
}

// Pass a GCPtr to a function.
void passGCPtr(GCPtr<int, 0> p)
{
  cout << "Inside passGCPtr(): "
       << *p << endl;
}

int main()
{
  try
  {
    // Declare an int GCPtr.
    GCPtr<int> ip;
    // Allocate an int and assign its address to ip.
    ip = new int(22);
    // Display its value.
    cout << "Value at *ip: " << *ip << "\n\n";
    // Pass ip to a function
    passGCPtr(ip);
    // ip2 is created and then goes out of scope
    {
      GCPtr<int> ip2 = ip;
    }
    int *p = ip; // convert to int * pointer'
    passPtr(p);  // pass int * to passPtr()
    *ip = 100;   // Assign new value to ip
    // Now, use implicit conversion to int *

    passPtr(ip);
    cout << endl;
    // Create a GCPtr to an array of ints
    GCPtr<int, 5> iap = new int[5];
    // Initialize dynamic array.
    for (int i = 0; i < 5; i++)
      iap[i] = i;

    // Display contents of array.
    cout << "Contents of iap via array indexing.\n";
    for (int i = 0; i < 5; i++)
      cout << iap[i] << " ";
    cout << "\n\n";
    // Create an int GCiterator.
    GCPtr<int>::GCiterator itr;

    // Now, use iterator to access dynamic array.
    cout << "Contents of iap via iterator.\n";
    for (itr = iap.begin(); itr != iap.end(); itr++)
      cout << *itr << " ";
    cout << "\n\n";
    // Generate and discard many objects
    for (int i = 0; i < 10; i++)
      ip = new int(i + 10);
    // Now, manually garbage collect GCPtr<int> list.
    // Keep in mind that GCPtr<int, 5> pointers
    // will not be collected by this call.
    cout << "Requesting collection on GCPtr<int> list.\n";
    GCPtr<int>::collect();
    // Now, use GCPtr with class type.
    GCPtr<MyClass> ob = new MyClass(10, 20);
    // Show value via overloaded insertor.
    cout << "ob points to " << *ob << endl;
    // Change object pointed to by ob.
    ob = new MyClass(11, 21);
    cout << "ob now points to " << *ob << endl;

    // Call a member function through a GCPtr.
    cout << "Sum is : " << ob->sum() << endl;
    // Assign a value to a class member through a GCPtr.
    ob->val = 19.21;
    cout << "ob->val: " << ob->val << "\n\n";
    cout << "Now work with pointers to class objects.\n";
    // Declare a GCPtr to a 5-element array
    // of MyClass objects.
    GCPtr<MyClass, 5> v;
    // Allocate the array.
    v = new MyClass[5];
    // Get a MyClass GCiterator.
    GCPtr<MyClass>::GCiterator mcItr;

    // Initialize the MyClass array.
    for (int i = 0; i < 5; i++)
    {
      v[i] = MyClass(i, 2 * i);
    }
    // Display contents of MyClass array using indexing.
    cout << "Cycle through array via array indexing.\n";
    for (int i = 0; i < 5; i++)
    {
      cout << v[i] << " ";
    }
    cout << "\n\n";
    // Display contents of MyClass array using iterator.
    cout << "Cycle through array through an iterator.\n";
    for (mcItr = v.begin(); mcItr != v.end(); mcItr++)
    {
      cout << *mcItr << " ";
    }
    cout << "\n\n";
    // Here is another way to write the preceding loop.
    cout << "Cycle through array using a while loop.\n";
    mcItr = v.begin();
    while (mcItr != v.end())
    {
      cout << *mcItr << " ";
      mcItr++;
    }
    cout << "\n\n";

    cout << "mcItr points to an array that is "
         << mcItr.size() << " objects long.\n";
    // Find number of elements between two iterators.
    GCPtr<MyClass>::GCiterator mcItr2 = v.end() - 2;
    mcItr = v.begin();
    cout << "The difference between mcItr2 and mcItr is "
         << mcItr2 - mcItr;
    cout << "\n\n";
    // Can also cycle through loop like this.
    cout << "Dynamically compute length of array.\n";
    mcItr = v.begin();
    mcItr2 = v.end();
    for (int i = 0; i < mcItr2 - mcItr; i++)
    {
      cout << v[i] << " ";
    }

    cout << "\n\n";
    // Now, display the array backwards.
    cout << "Cycle through array backwards.\n";
    for (mcItr = v.end() - 1; mcItr >= v.begin(); mcItr--)
      cout << *mcItr << " ";
    cout << "\n\n";
    // Of course, can use "normal" pointer to
    // cycle through array.
    cout << "Cycle through array using 'normal' pointer\n";
    MyClass *ptr = v;
    for (int i = 0; i < 5; i++)
      cout << *ptr++ << " ";
    cout << "\n\n";
    // Can access members through a GCiterator.
    cout << "Access class members through an iterator.\n";
    for (mcItr = v.begin(); mcItr != v.end(); mcItr++)
    {
      cout << mcItr->sum() << " ";
    }
    cout << "\n\n";

    // Can allocate and delete a pointer to a GCPtr
    // normally, just like any other pointer.
    cout << "Use a pointer to a GCPtr.\n";
    GCPtr<int> *pp = new GCPtr<int>();
    *pp = new int(100);
    cout << "Value at **pp is: " << **pp;
    cout << "\n\n";
    // Because pp is not a garbage collected pointer,
    // it must be deleted manually.
    delete pp;
  }
  catch (bad_alloc exc)
  {
    // A real application could attempt to free
    // memory by collect() when an allocation
    // error occurs.
    cout << "Allocation error.\n";
  }

  return 0;
}