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

int main ()
{
  return 0;
}
