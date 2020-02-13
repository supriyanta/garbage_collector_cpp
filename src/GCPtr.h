#pragma once

#include <iostream>
#include <list>
#include <cxxabi.h>

#include "Iter.cpp"
#include "GCInfo.cpp"

template <typename T, int size = 0>
class GCPtr
{
private:
  static std::list<GCInfo<T>> gcList;
  static bool init;

  unsigned m_size;
  bool isArray;
  T *ptr;

public:
  static bool displayLog;

  static void change()
  {
    displayLog = false;
  }

  GCPtr(T *t = nullptr);

  GCPtr(const GCPtr &copy);

  static bool collect();

  ~GCPtr();

  typedef Iter<T> GCiterator;

  T *operator=(T *t);

  GCPtr<T, size> &operator=(GCPtr &other);

  // conversion from GCPtr to T*
  operator T *();

  T &operator*();

  T *operator->();

  // operator[]
  T &operator[](unsigned index);

  bool operator==(GCPtr gcPtr);

  // begin()
  Iter<T> begin();

  // end()
  Iter<T> end();

  static unsigned gcListSize();

  // static bool showGCList();

  typename std::list<GCInfo<T>>::iterator findAddress(T *t);

  static void clearAll();

  static void showList();
};