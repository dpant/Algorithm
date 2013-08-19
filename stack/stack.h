#include "../list/list.h"
#include <iostream>
template <typename T>
class stack{
  List<T> store;
public:
  void push(T i){
	store.push_front(i);
  }
  T pop(){
	return store.pop_front();
  }
  size_t size(){
	return store.size();
  }
};

#if 0
int test(){
  stack<int> s;
  s.push(1);
  s.push(2);
  std::cout<< s.pop() << std::endl;

}
#endif 
