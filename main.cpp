#include <iostream>
#include <cstddef>


template< class T >
struct BiList {
  T val;
  BiList<T>* next;
  BiList<T>* prev;
};

/*
ЗАДАЧА № 2
*/

template< class T >
BiList<T>* create(const T& value);

template< class T >
BiList<T>* add(BiList<T>* h, const T& value);

template< class T >
BiList<T>* insert(BiList<T>* h, const T& value);

template< class T >
BiList<T>* cut(BiList<T>* h) noexcept;

template< class T >
BiList<T>* erase(BiList<T>* h) noexcept;

template< class T >
BiList<T>* clear(BiList<T>* h) noexcept;

template< class T >
BiList<T>* fake(BiList<T>* h);

template< class T >
BiList<T>* rmFake(BiList<T>* h) noexcept;

template< class T, class F >
F traverse(F f, BiList<T>* h, BiList<T>* e);

/*
ЗАДАЧА № 3
*/

template< class T >
BiList<T>* create(const T& value)
{
  BiList<T>* ret = new BiList<T>{value, nullptr, nullptr};
  ret->next = ret;
  ret->prev = ret; 
  return ret;
}

template< class T >
BiList<T>* add(BiList<T>* h, const T& value)
{
  BiList<T>* newNode = new BiList<T>{value, h, h->prev};
  h->prev->next = newNode;
  h->prev = newNode;
  return newNode;
}

template< class T >
BiList<T>* insert(BiList<T>* h, const T& value) 
{
  return add(h->next, value);
}

template< class T >
BiList<T>* cut(BiList<T>* h) noexcept
{
  BiList<T>* ret = h->next;
  h->prev->next = ret;
  ret->prev = h->prev;
  delete h;
  return ret;
}

template< class T >
BiList<T>* erase(BiList<T>* h) noexcept
{
  return cut(h->next);
}

template< class T >
BiList<T>* clear(BiList<T>* h) noexcept
{
  while (h->next != h)
  {
    erase(h);
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

/*
ЗАДАЧА № 4
*/

template< class T >
T* convert(BiList<T>* h, size_t& s)
{

  size_t counter = 1;
  BiList<T>* f = fake(h);
  while (h->next != f->next)
  {
    counter++;
    h = h->next;
  }
  h = h->next;

  T* res = new T[counter];
  s = counter;
  size_t j = 0;

  while (h->next != f->next)
  {
    try
    {
      res[j++] = h->val;
    } catch(...)
    {
      delete[] res;
      throw;
    }
    h = h->next;
  }
  res[j++] = h->val;
  rmFake(f);
  return res;
}

/*
Демонстрационная программа
*/

int main()
{
  BiList<int>* a = create(1);
  BiList<int>* b = insert(a, 2);
  BiList<int>* c = insert(b, 4);
  BiList<int>* d = add(c, 3);

  size_t s = 0;
  int* res = convert<int>(a, s);

  for (size_t i = 0; i < s; ++i)
  {
    std::cout << res[i] << '\n';
  }

  delete[] res;
  clear(a);
  cut(a);
  return 0;
}

/*
ЗАДАЧА № 1

НЕЯВНЫЙ ИНТЕРФЕЙС ДЛЯ T:
-Конструктор по умолчанию
-Конструктор копирования
-Оператор копирования
*/