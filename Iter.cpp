#include "Iter.h"

template <typename T>
Iter<T>::Iter() : current(NULL), begin(NULL), end(NULL)
{
  m_size = 0;
}

template <typename T>
Iter<T>::Iter(T *ptr, T *begin, T *end) : current(ptr), begin(begin), end(end)
{
  m_size = end - begin;
}

// template <typename T>
// Iter<T>::~Iter()
// {
// }

// returns the size in case of an array, otherwise 0
template <typename T>
unsigned Iter<T>::size()
{
  return m_size;
}

template <typename T>
T &Iter<T>::operator*()
{
  if (current < begin or current >= end)
    throw OutOfRangeException();
  return *current;
}

template <typename T>
T *Iter<T>::operator->()
{
  if (current < begin or current >= end)
    throw OutOfRangeException();
  return current;
}

template <typename T>
T &Iter<T>::operator[](int index)
{
  if (index < 0 or index >= size())
    throw new OutOfRangeException();
  return current[index];
}

// prefix
template <typename T>
Iter<T> Iter<T>::operator++()
{
  ++current;
  return *this;
}

template <typename T>
Iter<T> Iter<T>::operator--()
{
  --current;
  return *this;
}

// postfix
template <typename T>
Iter<T> Iter<T>::operator++(int _)
{
  Iter temp = *this;
  ++(*this);
  return temp;
  // return Iter<T>(temp, begin, end);
}

template <typename T>
Iter<T> Iter<T>::operator--(int _)
{
  T *temp = current;
  --(current);
  return Iter<T>(temp, begin, end);
}

// Compare length between two Iterator
template <typename T>
int Iter<T>::operator-(Iter<T> &it)
{
  return current - it.current;
}

// arithmetic
template <typename T>
Iter<T> Iter<T>::operator+(int n)
{
  T *temp = current;
  temp += n;
  return Iter<T>(temp, begin, end);
}

template <typename T>
Iter<T> Iter<T>::operator-(int n)
{
  T *temp = current;
  temp -= n;
  return Iter<T>(temp, begin, end);
}

// equal
template <typename T>
bool Iter<T>::operator==(Iter it)
{
  return current == it.current;
}

// not equal
template <typename T>
bool Iter<T>::operator!=(Iter it)
{
  return current != it.current;
}

template <typename T>
bool Iter<T>::operator<(Iter it)
{
  return current < it.current;
}

template <typename T>
bool Iter<T>::operator>(Iter it)
{
  return current > it.current;
}

template <typename T>
bool Iter<T>::operator<=(Iter it)
{
  return current <= it.current;
}

template <typename T>
bool Iter<T>::operator>=(Iter it)
{
  return current >= it.current;
}
