#ifndef GRAPHLIB_TYPELIST_H
#define GRAPHLIB_TYPELIST_H

#include <typeinfo>

class Nulltype {};

template <typename ...Args>
struct TypeList
{
  using Head = Nulltype;
  using Tail = Nulltype;
};

template <typename H, typename ...T>
struct TypeList<H, T...>
{
  using Head = H;
  using Tail = TypeList<T...>;
};

typedef TypeList<> EmptyTypeList;

template <typename H>
struct TypeList<H>
{
  using Head = H;
  using Tail = EmptyTypeList;
};

template <size_t ind, typename T>
struct TypeAt;

template <typename T1, typename T2>
struct TypeAt<0, TypeList<T1, T2> >
{
  using res = T1;
};

template <size_t ind, typename T1, typename T2>
struct TypeAt<ind, TypeList<T1, T2>>
{
  using res = typename TypeAt<ind - 1, T2>::res;
};

template <size_t ind>
struct TypeAt<ind, Nulltype>
{
  using res = Nulltype;
};



template <class T>
struct Length
{
};

template <class T1, class T2>
struct Length <TypeList<T1, T2> >
{
  static const int value = 1 + Length<T2>::value;
};

template <class T1>
struct Length <TypeList<T1, Nulltype> >
{
  static const int value = 1;
};

#endif //GRAPHLIB_TYPELIST_H
