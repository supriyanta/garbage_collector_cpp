# Garbage Collector for C++

<<<<<<< HEAD
This is an experimental project which enables user not to take care of manual release of Dynamically allocated memory when it goes out of scope or goes into the state when it will no longer be used.
=======
This is an experimental project which enables user not to take care of manual release of Dynamically allocated memory when it goes out of use or goes into the state when it will no longer be used.

> > > > > > > 1e963a8bfe0758cf1c9b7a71c220e1119dd82dfc

Here, Reference Counting method is used for creating the Garbage Collector.

### What is Reference counting?

**Reference counting** approach is super simple. It is based on the idea of counting the number of pointer references to each allocated object. It’s a direct method that also happens to be naturally incremental as it distributes the memory management overhead throughout the program.
[Read more...](https://www.educative.io/courses/a-quick-primer-on-garbage-collection-algorithms/jR8ml "Educative.io")

### Usage

Include the files inside [src](https://github.com/supriyanta/garbage_collector_cpp/tree/master/src) folder and add

```cpp
#include "GCPtr.cpp"
```

into your file and your good to go.
For usage take a look at the [examples](https://github.com/supriyanta/garbage_collector_cpp/tree/master/examples) folder.

### Restrictions

- You can't use GCPtr object as a global object.
- You must always specify the size, in case of allocating memory for arrays
- GCPtr object must point to only dynamically allocated memory using **new**.

* You must not free memory manually using **delete**.
