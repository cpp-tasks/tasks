// g++ -std=c++11 mem_fn_std11.cpp

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

struct Animal {
  virtual void bark() = 0;
};

struct Cat : Animal {
  void bark() {
    std::cout << "Meow-meow!" << std::endl;
  }
};

struct Dog : Animal {
  void bark() {
    std::cout << "Bow-wow!" << std::endl;
  }
};

template<class T, class R>
struct Functor {
  R (T::*fn_)();

  Functor(R (T::*fn)()): fn_(fn) {
  }

  R operator()(T* obj) {
    return (obj->*fn_)();
  }
};

template<class T, class R>
Functor<T, R> mem_fn(R (T::*bark)()) {
  return Functor<T, R>(bark);
}

int main(int ARGC, char *ARGV[]) {
  std::vector<Animal*> animals { new Cat(), new Dog() };
  mem_fn(&Animal::bark)(new Dog);
  std::for_each(animals.begin(), animals.end(), mem_fn(&Animal::bark));
}
