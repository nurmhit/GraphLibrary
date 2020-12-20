# Graph Library

## Типы выершин и ребер
Принимаются только вершины и ребра тех типов, у которых есть конструктор.

## Создание графа

```cpp
CustomGraph <TypeList<int, TypeList<std::string, TypeList<char, Nulltype> > >, 
    TypeList<int, TypeList<std::string, Nulltype> > > x;
```
Первый Тайплист представляет из себя все типы вершин, в том порядке, в котором они будут внесены в граф.
Второй Тайплист то же самое, но для ребер.

## Добавление Вершин
```cpp
x.add_vertex(5);
x.add_vertex(std::string("JOJO"));
x.add_vertex('c');
```
Добавление происходит с помощью функции add_vertex. В ответ будет выдан номер вершины.

## Добавление Ребер

```cpp
x.add_edge<0, 1>(8);
x.add_edge<1, 2>(std::string("JOJOJO"));
```

Аналогично добавлению вершин, но здесь еще нужно указать откуда и куда идет ребро.

## Получение значения в вершине

```cpp
x.get_v_at<0>();
```
Возвращается значение в вершине, номер которой передан через шаблонный аргумент.

## Применение функций к вершинам

```cpp
int f(int r)
{
  std::cout << r << std::endl;
  return r;
}

x.NodeIteration<0, int, int> (f);
```

Первый шаблонный аргумент - номер вершины, остальные 2, возвращаемое и принимаемое значение.
Работает только с нодами, к которым можно применить функцию.


## Применение функции ко всем вершинам графа

```cpp
int f(int r)
{
  std::cout << r << std::endl;
  return r;
}

x.FullNodeIteration<2, int, int> (f);
```

```
Вывод:
3
7
5
```

Граф изначально был заполнен 3мя вершинами 3, 7, 5.

## Паттерн Компоновщик

```cpp
  CompositeGraph <TypeList<SuperHero, TypeList<CompositeGraph <TypeList<SuperHero, Nulltype>, TypeList<SuperHero, Nulltype> >, Nulltype>>, TypeList<SuperHero, Nulltype> > y;
  y.add__vertex(SuperHero(10));
  std::cout << y.get_strength() << std::endl;

  CompositeGraph <TypeList<SuperVillian, Nulltype>, TypeList<SuperVillian, Nulltype> > z;
  z.add__vertex(SuperVillian(10));

  y.add__vertex(z);
  std::cout << y.get_strength() << std::endl;
```

Как можно заметить, в данном случае подсчитается ответ для всех членов класса, даже, учитывая, что один из них граф.

## Этап компиляции

Схема графа строится на этапе компиляции, это можно заметить по шаблонным параметрам, необходимым для построения самого графа.

## Хранение графа в разных видах

Внутри граф хранится в виде графа смежности и матрицы смежности. 