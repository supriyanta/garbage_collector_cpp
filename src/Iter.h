#pragma once

#include <stdlib.h>
#include "OutOfRangeException.cpp"

template <typename T>
class Iter
{
private:
  T *begin;
  T *end;
  T *current;
  unsigned m_size;

public:
  Iter();

  Iter(T *ptr, T *begin, T *end);

  // ~Iter()
  // {
  // }

  // returns the size in case of an array, otherwise 0
  unsigned size();

  T &operator*();

  T *operator->();

  T &operator[](int index);

  // prefix
  Iter operator++();

  Iter operator--();

  // postfix
  Iter operator++(int _);

  Iter operator--(int _);

  // Compare length between two Iterator
  int operator-(Iter<T> &it);

  // arithmetic
  Iter operator+(int n);

  Iter operator-(int n);

  // equal
  bool operator==(Iter it);

  // not equal
  bool operator!=(Iter it);

  bool operator<(Iter it);

  bool operator>(Iter it);

  bool operator<=(Iter it);

  bool operator>=(Iter it);
};