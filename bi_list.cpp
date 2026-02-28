#include "bi_list.hpp"

template< class T >
BiList<T>* add(BiList<T>* h, BiList<T> pr, const T& d)
{
  return new BiList<T>{d, h, pr};
}

template< class T >
BiList<T>* insert(BiList<T>* h, BiList<T>* begin, const T& d)
{
  return h->next = add(d, begin, h);
}

template< class T >
BiList<T>* cut(BiList<T>* h) noexcept
{
  BiList<T>* ret = h->next;
  ret->prev = h->prev;
  delete h;
  return ret;
}

template< class T >
BiList<T>* erase(BiList<T>* h) noexcept
{
  return h->next = cut(h->next);
}

template< class T >
BiList<T>* clear(BiList<T>* h) noexcept
{
  while (h->next != h)
  {
    h = cut(h);
  }
  return h;
}

template< class T >
BiList<T>* fake(BiList<T>* h)
{
  BiList<T>* r = static_cast< BiList<T>* >(::operator new (sizeof(BiList<T>*)));
  r->prev = nullptr;
  r->next = h;
  h->prev = r;
  return r;
}

template< class T >
BiList<T>* rmFake(BiList<T>* h) noexcept
{
  BiList<T>* ret = h->next;
  ::operator delete(h);
  return ret;
}
