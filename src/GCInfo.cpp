#include "GCInfo.h"

template <typename T>
GCInfo<T>::GCInfo(T *t, int size)
{
  referenceCount = 1;
  m_ptr = t;

  if (size > 0)
  {
    isArray = true;
  }
  else
  {
    isArray = false;
  }
  arraySize = size;
}

template <typename T>
bool GCInfo<T>::operator==(const GCInfo<T> &gci)
{
  return m_ptr == gci.m_ptr;
}