#include <cstddef>
#include <stdexcept>
#include <iostream>
using namespace std;

class List{
  class ListNode{
  public:
	int data;
	ListNode* next;
	static ListNode* MkNode(){ return new ListNode(); }
  };
  ListNode *head, *tail;
  size_t msize;

public:

  List():head(NULL),tail(NULL),msize(0){
  }
  
  size_t size(){return msize;
  }
  
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
	if(msize == 0){ /* standard STL behaviour is undefined in case of underflow */
	  throw underflow_error("List already empty");
	}
	ListNode* tmp = head;
	head = head->next;
	msize--;	
	if(msize == 0){
	  tail = NULL;
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
int main(){
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
