/* Array based circular queue implementation */
/*  end indicated the next locaiton where the item need to be inserted */
/* start indicate the location whose next item need to be poped if it is not end 

At the begining when no item is there array looks like this.

start+1 == end ==> queue is empty;

Start
 |
---------------------------------------------
	|	|	|	|	|	|	|	|	|	|	| 
---------------------------------------------
	  |
	End

After two enqueue operation 

Start
 |
---------------------------------------------
	| 2	| 7	|	|	|	|	|	|	|	|	| 
---------------------------------------------
	  	      |
		 	 End

Several insert (Queue is Full)

Start
 |
---------------------------------------------
	| 2	| 7	| 3	| 3	| 2	| 1	| 6	| 5	| 3	| 2	| 
---------------------------------------------
 |
End


One cell is always empty !! that is how we can differentiate 
between if queue if Full vs queue is empty

*/

#include <iostream>
#include <cstddef>
using namespace std;
class queueArray{
private:
  size_t size;
  int* Array;
  int start;
  int end;

  public:
  queueArray(size_t sizep){
	size = sizep+1;
	Array = new int[size];
	start = 0;
	end = start + 1;
  }
  void enqueue(int i){
	if(start == end){
	  cout << "Queue full" << endl;
	  return ;
	}
	Array[end] = i;
	end = (end + 1) % size;
   
  }
  int dequeue(){
	if(start+1 == end){
	  cout<<"Queue Empty" << endl;
	  return -1;
	}
	start = (start +1)% size;
	return Array[start];
  }
	

};
int main(){
  queueArray qA(10);
  for(int i = 0; i < 10 ; i ++){
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
