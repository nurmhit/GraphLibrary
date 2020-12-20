#ifndef GRAPHLIB_CUSTOMLIST_H
#define GRAPHLIB_CUSTOMLIST_H

#include <any>
#include <vector>
#include "TypeList.h"

class CustomList
{
  std::vector <std::any> list;
public:
  CustomList(){}


  template <typename T>
  void add(T some = T())
  {
    list.push_back(std::any_cast<T>(some));
  }

  template <typename T>
  T val_at(int i)
  {
    return std::any_cast<T>(list[i]);
  }

  template <typename T>
  void change(int i, T val)
  {
    list[i] = val;
  }

  int len()
  {
    return list.size();
  }

  template <typename T,  typename ...Args, typename FuncRes = T (*)(Args...)>
  auto apply(int i, FuncRes f)
  {
    try {
      return f(std::any_cast<T>(list[i]).val);
    }
    catch(const std::bad_any_cast& e){
      std::cout << "You have Invalid type in your vertexes for this func. Number " << ' ' << i << std::endl;
    }
  }


};

#endif //GRAPHLIB_CUSTOMLIST_H
