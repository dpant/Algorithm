#include <cstddef>
#include <stdexcept>
#include <iostream>
using namespace std;

class List{

  class ListNode{ /* remember inner class does not have access to outer class variable/funcs. if needed have to add ref to outer calss inside the inner class*/
  public:
	int data;
	ListNode* next;
	static ListNode* MkNode(){ return new ListNode(); }
  };
  ListNode *head, *tail;
  size_t msize;
  /* to make iterator functionality work. we need to make end() which return iterator past the list */
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
	int &operator *(){ 
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
  void push_front(int i){
	ListNode *ln = ListNode::MkNode();
	ln->data = i;
	ln->next = head;
	head = ln;
	if(msize == 0){
	  tail = ln;
	}
	msize++;
  }

  int pop_front() throw(underflow_error){	/* exception specification. usually dont write it, its runtime garantee but might have performace hit due to non inlining of function */
	int data;
	if(msize == 0){ /* STL behaviour is undefined in case of underflow */
	  throw underflow_error("List already empty");
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

  void printList(){
	ListNode* Ln = head;
	while(Ln != NULL){
	  cout<< Ln->data << "-->";
	  Ln= Ln->next;
	}
	cout << endl;
  }

};

void myunexpected(){
  std::cerr <<"unexpected called\n";
  throw 0;
}
int testList(){
  List l = List();
  //List::ListNode lnd; /* can't do this.Class ListNode is  is private */

  std::set_unexpected (myunexpected);
  l.push_front(10);
  l.push_front(20);
  l.push_front(30);
  l.push_front(40);
  cout<<endl << l.pop_front()<<endl;
  cout<<endl << l.pop_front()<<endl;
  cout<<endl << l.pop_front()<<endl;
  cout<<endl << l.pop_front()<<endl;
  try{
  cout<<endl << l.pop_front()<<endl;
  }catch(underflow_error &e){
	cout<<e.what();
  }

  l.printList();	
}
void iteratorTest(){
  List l = List();
  l.push_front(11);
  l.push_front(22);
  l.push_front(33);
  l.push_front(44);
  l.printList();
  for(List::iterator i = l.begin();i != l.end(); i++){
	cout << *i << endl;
  }
}
int main(){
  iteratorTest();
}
