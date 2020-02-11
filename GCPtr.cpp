#include "GCPtr.h"

template <typename T, int size>
GCPtr<T, size>::GCPtr(T *t)
{
  // Registering callback function which runs right before the exit
  if (init)
    atexit(clearAll);
  init = false;

  typename std::list<GCInfo<T>>::iterator it = findAddress(t);
  if (it != gcList.end())
  {
    it->referenceCount += 1;
  }
  else
  {
    GCInfo<T> gcInfo(t, size);
    gcList.push_front(gcInfo);
  }

  ptr = t;
  m_size = size;

  if (m_size > 0)
    isArray = true;
  else
    isArray = false;
}

template <typename T, int size>
GCPtr<T, size>::GCPtr(const GCPtr &copy)
{
  typename std::list<GCInfo<T>>::iterator it = findAddress(copy.ptr);
  if (it != gcList.end())
  {
    it->referenceCount += 1;
  }

  ptr = copy.ptr;
  m_size = copy.m_size;

  if (m_size > 0)
    isArray = true;
  else
    isArray = false;
}

template <typename T, int size>
GCPtr<T, size>::~GCPtr()
{
  typename std::list<GCInfo<T>>::iterator it;
  it = findAddress(ptr);
  if (it->referenceCount > 0)
    it->referenceCount -= 1;

  if (it->referenceCount == 0)
    collect();
}

template <typename T, int size>
T *GCPtr<T, size>::operator=(T *t)
{
  typename std::list<GCInfo<T>>::iterator it;
  it = findAddress(ptr);
  it->referenceCount -= 1;

  it = findAddress(t);

  if (it != gcList.end())
  {
    it->referenceCount += 1;
  }
  else
  {
    GCInfo<T> gcInfo(t, size);
    gcList.push_front(gcInfo);
  }
  ptr = t;
  return t;
}

template <typename T, int size>
GCPtr<T, size> &GCPtr<T, size>::operator=(GCPtr &other)
{
  typename std::list<GCInfo<T>>::iterator it;
  it = findAddress(ptr);
  it->referenceCount -= 1;

  it = findAddress(other.ptr);
  ptr = other.ptr;

  if (it != gcList.end())
  {
    it->referenceCount += 1;
  }
  return other;
}

// conversion from GCPtr to T*
template <typename T, int size>
GCPtr<T, size>::operator T *()
{
  return ptr;
}

template <typename T, int size>
T &GCPtr<T, size>::operator*()
{
  return *ptr;
}

template <typename T, int size>
T *GCPtr<T, size>::operator->()
{
  return ptr;
}

// operator[]
template <typename T, int size>
T &GCPtr<T, size>::operator[](unsigned index)
{
  return ptr[index];
}

template <typename T, int size>
bool GCPtr<T, size>::operator==(GCPtr gcPtr)
{
  return ptr == gcPtr.ptr;
}

// begin()
template <typename T, int size>
Iter<T> GCPtr<T, size>::begin()
{
  unsigned f_size = isArray ? m_size : 1;
  return Iter<T>(ptr, ptr, ptr + f_size);
}

// end()
template <typename T, int size>
Iter<T> GCPtr<T, size>::end()
{
  unsigned f_size = isArray ? m_size : 1;
  return Iter<T>(ptr + f_size, ptr, ptr + f_size);
}

template <typename T, int size>
unsigned GCPtr<T, size>::gcListSize()
{
  return gcList.size();
}

// static bool showGCList();

template <typename T, int size>
typename std::list<GCInfo<T>>::iterator GCPtr<T, size>::findAddress(T *t)
{
  typename std::list<GCInfo<T>>::iterator it;
  for (it = gcList.begin(); it != gcList.end(); ++it)
  {
    if (it->m_ptr == t)
      return it;
  }
  return it;
}

template <typename T, int size>
void GCPtr<T, size>::clearAll()
{
  if (gcListSize() == 0)
    return;

  typename std::list<GCInfo<T>>::iterator it;
  for (it = gcList.begin(); it != gcList.end(); ++it)
  {
    it->referenceCount = 0;
  }
  collect();
}

template <typename T, int size>
bool GCPtr<T, size>::init = true;

template <typename T, int size>
std::list<GCInfo<T>> GCPtr<T, size>::gcList;

template <typename T, int size>
bool GCPtr<T, size>::collect()
{
  bool memoryFreed = false;

  typename std::list<GCInfo<T>>::iterator it;
  do
  {
    for (it = gcList.begin(); it != gcList.end(); ++it)
    {
      if (it->referenceCount > 0)
        continue;

      gcList.remove(*it);

      if (it->isArray)
      {
        delete[] it->m_ptr;
      }
      else
      {
        delete it->m_ptr;
      }

      memoryFreed = true;
      break;
    }
  } while (it != gcList.end());

  return memoryFreed;
}