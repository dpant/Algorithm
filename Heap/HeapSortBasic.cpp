#include<iostream>
using namespace std;


/* 

Heap is a **Tree structure** in which root nodes is greater than its child node.
--  So leaf node is always a **heap subtree**

Think it as an array representing a "Heap" 
For element i
				2i is left child
				2i + 1 is right child
*/
#define ARRAYSIZE(X) (sizeof(X)/sizeof(X[0]))
void swap(int *x , int *y){
  int tmp;
  tmp = *y;
  *y= *x;
  *x = tmp;
}
/* 

heapify the structure assuming the index { starting from 0 } is the one 
voilating the heap property 

*/
void maxheapify(int *a,int len, int index){
  int max = 0;
  int lci = -1;
  int rci = -1;
  while(index < len/2 ){ /* index starts at 0 */
	lci = 2*(index+1) -1;
	rci = 2*(index+1)+1 -1;
	if((a[index] < a[lci]) || (a[index] < a[rci])){
	  max = (a[rci] > a[lci]) ? rci : lci;
	  swap(&a[index],&a[max]);
	  maxheapify(a,len,max);	
	}else{
	  break;
	}	 
  }
}	
/* 
Think it as an array representing a "Heap" 
For element i
				2i is left child
				2i + 1 is right child

- you have to start index from 1 to make above relation validate.
-  Think what will happen if you do this calculation based on 0 start 
index? [hint what will the children of node 0?]

*/

/* builds a max heap structure */

void BuildHeap(int *a,int len){
  for(int i = len/2; i >=0 ; i--){ /* leafs are already heap */
	maxheapify(a,len,i);
  }
}

void HeapSort(int *a , int len){
  BuildHeap(a,len);
  for(int i = len -1 ; i > 0 ; i--){
	swap(a[0],a[i]);/* put the max element at the end of array */
	maxheapify(a,i-1,0); /* do heapify at index 0 but reduce the array size */
  }	
}

int main(){

  int a[] = {3,4,5,0,1,2,3};

  HeapSort(a,ARRAYSIZE(a));

  for(int i=0;i<ARRAYSIZE(a);i++){ // print
	cout<<a[i]<< " ";
  }
}
