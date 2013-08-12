#include <cstddef>
#include <iostream>
using namespace std;
class List{
  class ListNode{
  public:
	int data;
	ListNode* next;
	static ListNode* MkNode(){ return new ListNode(); }
  };
  ListNode* head;

public:

  List():head(NULL){}
  void addnodeToFront(int i){
	ListNode *ln = ListNode::MkNode();
	ln->data = i;
	ln->next = head;
	head = ln;
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

int main(){
  List l = List();
  //List::ListNode lnd; /* can't do this.Class ListNode is  is private */
  l.addnodeToFront(10);
  l.addnodeToFront(20);
  l.addnodeToFront(30);
  l.addnodeToFront(40);
  l.printList();	
	
}
