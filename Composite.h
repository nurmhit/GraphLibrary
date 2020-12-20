#ifndef GRAPHLIB_COMPOSITE_H
#define GRAPHLIB_COMPOSITE_H

#include "CustomGraph.h"

class SuperHero
{
public:
  int strength;
  SuperHero(int x): strength(x)
  {}
  int get_strength()
  {
    return strength;
  }
};

class SuperVillian
{
public:
  int strength;
  SuperVillian(int x): strength(x){}
  int get_strength()
  {
    return strength*2;
  }
};

#define define_has_member(member_name)                                         \
    template <typename T>                                                      \
    class has_member_##member_name                                             \
    {                                                                          \
        typedef char yes_type;                                                 \
        typedef long no_type;                                                  \
        template <typename U> static yes_type test(decltype(&U::member_name)); \
        template <typename U> static no_type  test(...);                       \
    public:                                                                    \
        static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes_type);  \
    }
#define has_member(class_, member_name)  has_member_##member_name<class_>::value

define_has_member(get_strength);

template<typename T, typename U>
class CompositeGraph: public CustomGraph<T, U> {
private:
  std::vector<int> some;
public:
  CompositeGraph(): CustomGraph<T, U>(){};

  template <typename Z>
  int add__vertex(Z val) {
    static_assert(has_member(Z, get_strength), "You are waaaay too weak, little hero! No strength in yout class.");
    this->nodes.add(Node(val));
    this->relations.push_back(std::vector<int>());
    some.push_back(val.get_strength());
    return this->relations.size() - 1;
  }

  int get_strength() {
    int ans = 0;
    for(auto i: some) {
      ans += i;
    }
    return ans;
  }

};

#endif //GRAPHLIB_COMPOSITE_H
