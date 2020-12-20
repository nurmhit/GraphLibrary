#ifndef GRAPHLIB_CUSTOMGRAPH_H
#define GRAPHLIB_CUSTOMGRAPH_H

#include "TypeList.h"
#include "CustomList.h"
#include <map>
#include <type_traits>

template <typename T, typename U>
class CustomGraph;

template <typename T>
class Node
{
public:
  T val;
  explicit Node(T val): val(val)
  {}
};

template <typename T>
class Edge
{
public:
  T val;
  int from, to;
  explicit Edge(T val, int from , int to): val(val), from(from), to(to)
  {}
};

template <typename ...T, typename ...U>
class CustomGraph<TypeList<T...>, TypeList<U...>>
{
protected:
  CustomList nodes;
  CustomList edges;
  std::vector <std::vector <int>> relations;
  std::vector <std::vector <int>> matrix;
  std::map <std::pair<int, int>, std::any> edge_relations;
  std::map <std::pair<int, size_t>, int> num;
  int e_size;
  using v = TypeList<T...>;
  using e = TypeList<U...>;
public:
  CustomGraph()
  {
    matrix.assign(Length<v>::value, std::vector<int>(Length<v>::value, 0));
    e_size = 0;
  }

  template <typename Z>
  int add_vertex(Z val)
  {
    nodes.add(Node(val));
    relations.push_back(std::vector<int>());
    return relations.size() - 1;
  }

  template <int i, int j, typename Z>
  void add_edge(Z val)
  {
    edges.add(Edge(val, i, j));
    relations[i].push_back(j);
    matrix[i][j] = 1;
    e_size++;
    edge_relations[std::make_pair(i, j)] = val;
    num[std::make_pair(i, j)] = e_size;

  }

  template <int place>
  auto get_v_at()
  {
    return nodes.val_at<Node<typename TypeAt<place, v>::res>>(place).val;
  }


  template <int i, typename Z, typename E, typename FuncRes = Z (*)(E)>
  auto NodeIteration(FuncRes f)
  {
    if(std::is_same<typename TypeAt<i, v>::res, Z>::value) {
      return nodes.apply<Node<typename TypeAt<i, v>::res>>(i, f);
    }
  }

  template <int i, typename Z, typename E, typename FuncRes = Z (*)(E)>
  class BreakClass
  {
  public:
        int res;
        BreakClass(CustomGraph<TypeList<T...>, TypeList<U...>> boss, FuncRes r)
        {
          res = boss.NodeIteration<i, Z, E>(r) + BreakClass<i-1, Z, E, FuncRes>(boss, r).res;
        }
        static const bool f = true;

  };

  template <typename Z, typename E>
  class BreakClass<-1, Z, E, Z (*)(E)> {
  public:
    using q = Z(*)(E);
    BreakClass(CustomGraph<TypeList<T...>, TypeList<U...>> boss, q d) {}
    static const int res = 0;
  };

  template <int i, typename Z, typename E, typename FuncRes = Z (*)(E)>
  auto FullNodeIteration(FuncRes f)
  {
    return BreakClass<i, Z, E, FuncRes>(*this, f).res;
  }


};

#endif //GRAPHLIB_CUSTOMGRAPH_H
