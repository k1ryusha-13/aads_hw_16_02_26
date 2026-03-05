#include <iostream>

template< class T >
struct BiList
{
  T val;
  BiList< T >* next;
  BiList< T >* prev;
};

template< class T >
BiList< T >* fakeStart(BiList< T >* next)
{
  BiList< T >* el = static_cast< BiList< T >* >(::operator new(sizeof(BiList< T >)));
  el->next = next;
  next->prev = el;
  return el;
}

template< class T >
BiList< T >* fakeEnd(BiList< T >* prev)
{
  BiList< T >* el = static_cast< BiList< T >* >(::operator new(sizeof(BiList< T >)));
  el->prev = prev;
  prev->next = el;
  return el;
}

template< class T >
void dlfake(BiList< T >* fake) noexcept
{
  ::operator delete(fake);
}

template< class T >
BiList< T >* insert(BiList< T >* prev, const T& data)
{
  BiList< T >* el = new BiList< T >;
  el->val = data;
  el->prev = prev;
  el->next = prev->next;
  el->prev->next = el;
  el->next->prev = el;
  return el;
}

template< class T >
BiList< T >* add(BiList< T >* next, const T& data)
{
  BiList< T >* el = new BiList< T >;
  el->val = data;
  el->next = next;
  el->prev = next->prev;
  el->prev->next = el;
  el->next->prev = el;
  return el;
}

template< class T >
BiList< T >* makeBiList()
{
  BiList< T >* el = new BiList< T >;
  BiList< T >* rt = fakeStart(el);
  fakeEnd(el);
  el->prev->next = el->next;
  el->next->prev = el->prev;
  delete el;
  return rt;
}

template< class T >
BiList< T >* makeBiList(const T& data)
{
  BiList< T >*el = new BiList< T >;
  el->val = data;
  fakeStart(el);
  fakeEnd(el);
  return el;
}

template< class T >
BiList< T >* cut(BiList< T >* el)
{
  BiList< T >* r = el->next;
  el->next = el->next->next;
  el->next->prev = el;
  delete r;
  return el;
}

template< class T >
void clear(BiList< T >* fakeStart, BiList< T >* fakeEnd)
{
  while(fakeStart->next != fakeEnd)
  {
    cut(fakeStart);
  }

  dlfake(fakeStart);
  dlfake(fakeEnd);
}

int main ()
{
  return 0;
}
