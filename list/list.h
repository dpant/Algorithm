#include <cstddef>
#include <stdexcept>
#include <exception>
#include <iostream>

template <typename T>
class List{
  class ListNode{ /* remember inner class does not have access to outer class variable/funcs. if needed have to add ref to outer calss inside the inner class*/
  public:
	T data;
	ListNode* next;
	static ListNode* MkNode(){ return new ListNode(); }
  };
  ListNode *head, *tail;
  size_t msize;

  /* to make iterator functionality adhere to conventions, we need to make end() which return iterator past the list */
  ListNode *dummyendnode;  /* Notice dummyend can't be part of iterator, as we have to return same end for multiple iterator end() calls */

public:
  /* iterator implementation  */
  class iterator{
	ListNode *p;

  public:
	iterator(ListNode *ln):p(ln){

	}
	iterator():p(NULL){

	}
	T &operator *(){ 
	  return p->data;
	}
	iterator& operator ++(){ //prefix
	  p = p->next;
	  return *this;
	}
	iterator& operator ++(int){ //prefix
	  iterator toreturn = *this;
	  p = p->next;
	  return *this;
	}
	bool operator !=(const iterator &itr){
	  return p != itr.p;
	}
	bool operator ==(const iterator &itr){
	  return ! (*this != itr);
	}

  };

  iterator begin(){
	iterator *iobj = new iterator(head);
	return *iobj;
  }
  iterator end(){
	iterator *iobj = new iterator(dummyendnode);
    return *iobj;
  }
  /* constructors */
  List():msize(0){
	ListNode *ln = ListNode::MkNode();
	head = tail = ln;
	dummyendnode = ln;
  }
  size_t size(){
	return msize;
  }
  /* member fucntions */
  void push_front(T i){
	ListNode *ln = ListNode::MkNode();
	ln->data = i;
	ln->next = head;
	head = ln;
	if(msize == 0){
	  tail = ln;
	}
	msize++;
  }

  T pop_front() throw(std::underflow_error){	/* exception specification. usually dont write it, its runtime garantee but might have performace hit due to non inlining of function */
	int data;
	if(msize == 0){ /* STL behaviour is undefined in case of underflow */
	  throw std::underflow_error("List already empty");
	}
	ListNode* tmp = head;
	head = head->next;
	msize--;	
	if(msize == 0){
	  tail = dummyendnode;
	  head = dummyendnode;
	}
	data = tmp->data;
	delete tmp;
	return data;
  }
#if 0
  void printList(){
	ListNode* Ln = head;
	while(Ln != NULL){
	  std::cout<< Ln->data << "-->";
	  Ln= Ln->next;
	}
	std::cout << std::endl;
  }
#endif 
};


#if 0
void iteratorTest(){
  List<int> l = List<int>();
  l.push_front(11);
  l.push_front(22);
  l.push_front(33);
  l.push_front(44);
  l.printList();
  for(List<int>::iterator i = l.begin();i != l.end(); i++){
	std::cout << *i << std::endl;
  }
}
#endif 
//int main(){
// iteratorTest();
//}
