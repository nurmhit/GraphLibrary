#include <iostream>
#include <vector>
#include <any>
#include "CustomGraph.h"
#include <string>
#include "Composite.h"

template <typename T>
T f(int r)
{
  std::cout << r << std::endl;
  return r;
}

int main() {
  CustomGraph <TypeList<int, TypeList<int, TypeList<int, Nulltype> > >, TypeList<int, TypeList<std::string, Nulltype> > > x;
  x.add_vertex(5);
  x.add_vertex(7);
  x.add_vertex(3);
  x.add_edge<0, 1>(8);
  x.add_edge<1, 2>(std::string("OKO"));
  x.FullNodeIteration<2, int, int> (f);
  std::cout << x.get_v_at<0>() << std::endl;



  CompositeGraph <TypeList<SuperHero, TypeList<CompositeGraph <TypeList<SuperHero, Nulltype>, TypeList<SuperHero, Nulltype> >, Nulltype>>, TypeList<SuperHero, Nulltype> > y;
  y.add__vertex(SuperHero(10));
  std::cout << y.get_strength() << std::endl;

  CompositeGraph <TypeList<SuperVillian, Nulltype>, TypeList<SuperVillian, Nulltype> > z;
  z.add__vertex(SuperVillian(10));

  y.add__vertex(z);
  std::cout << y.get_strength() << std::endl;
  return 0;
}
