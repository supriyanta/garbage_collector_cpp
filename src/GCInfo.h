#pragma once

template <typename T>
class GCInfo
{
public:
  unsigned referenceCount;
  T *m_ptr;
  bool isArray;
  unsigned arraySize;

  GCInfo(T *t, int size = 0);

  bool operator==(const GCInfo<T> &gci);
};