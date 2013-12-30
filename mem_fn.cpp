/*Dmitry Meleshko*/
/* mem_fn */

#include <algorithm>
#include <iostream>
#include <vector>
//#include <functional>

template<class T, class R>
struct Functor
{
  R (T::*_fn) ();
  Functor(R (T::*func) ()):_fn(func)
  {}

R  operator()(T * obj)
  {
//    k.bark();
    return (obj->*_fn)();
  }
};

template<class T, class R>
Functor<T, R> mem_fn(R (T::*func) ())
{
  Functor<T,R> A = Functor<T,R>(func);
  return A;
}

struct Animal
{
  virtual void bark() = 0;
};
 
struct Cat : Animal
{
  void bark() { std::cout << "Meow-meow!" << std::endl; }
};
 
struct Dog : Animal
{
  void bark() { std::cout << "Bow-wow!" << std::endl; }
};
 
int main(int ARGC, char *ARGV[])
{
  Animal *animals[2] = { new Cat(), new Dog() };
 
//  Functor<Animal, void> K = mem_fn(&Animal::bark);
//  K(new Cat());
  mem_fn(&Animal::bark)(new Dog);
  std::for_each(animals, animals+2, mem_fn(&Animal::bark));
 

}
