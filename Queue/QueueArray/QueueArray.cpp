/* Circular array based Queue implementation */
/* 
At the begining when no item is there array looks like this.

Start
 |
---------------------------------------------
	|	|	|	|	|	|	|	|	|	|	| 
---------------------------------------------


After 3 enqueue operation 

Start
 |
---------------------------------------------
 1	| 2	| 7	|	|	|	|	|	|	|	|	| 
---------------------------------------------

After 3 enqueue operation 

	Start
	 |
---------------------------------------------
 	| 2	| 7	|	|	|	|	|	|	|	|	| 
---------------------------------------------


Several insert (Queue is Full)

	Start
	 |
---------------------------------------------
 11	| 2	| 7	| 3	| 3	| 2	| 1	| 6	| 5	| 3	| 2	| 
---------------------------------------------




*/

#include <iostream>
#include <cstddef>
using namespace std;
class queueArray{
private:
  size_t size;
  int* Array;
  int start;
  int items;

  public:
  queueArray(size_t sizep){
	size = sizep;
	Array = new int[size];
	start = 0;
	items = 0;
  }
  void enqueue(int i){
	size_t end;
	if(items == size){
	  cout << "Queue full" << endl;
	  return ;
	}
	end = (start + items) % size;
	Array[end] = i;
	items++;
   
  }
  int dequeue(){
	int fronte;
	if(items == 0){
	  cout<<"Queue Empty" << endl;
	  return -1;
	}
	fronte = Array[start];
	start = (start +1 )% size;
	items-- ;
	return fronte;
  }
};
int testQueue(){
  queueArray qA(10);
  for(int i = 0; i < 11 ; i ++){
	qA.enqueue(i);
  }
  for(int i = 0 ; i < 5 ; i ++){
	cout << qA.dequeue() << " " ;
  }
  for(int i = 10; i < 15 ; i ++){
	qA.enqueue(i);
  }
  cout<< endl;
  for(int i = 0 ; i < 10 ; i ++){
	cout << qA.dequeue() << " " ;
  }
}

int main(){
  testQueue();
}
