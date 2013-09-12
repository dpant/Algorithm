#include<iostream>
using namespace std;
/* 
Heap is a **Tree structure** in which root nodes is greater than its child node.
--  So leaf node is always a **heap subtree**

Think it as an array representing a "Heap" 
For element i [ if index starts at 1 ] 
				2i is left child
				2i + 1 is right child
*/
#define ARRAYSIZE(X) (sizeof(X)/sizeof(X[0]))

/* 
Elements are out of order, not following heap property 
if x is parent of y and x is smalle than y.
in that case we need to return TRUE;

*/


/* 

heapify the structure assuming the index { starting from 0 } is the one 
voilating the heap property 

*/
template <typename T>
int ifChildPresent(T ci,T len){
  return ci < len;
}
template <typename T>
void heapify(vector<T> &a,int len, int index,bool (*cmp)(int x, int y)){
  int max = 0;
  int lci = -1;
  int rci = -1;
  while(index < len/2 ){ /* index starts at 0 */
	lci = 2*(index+1) -1;
	rci = 2*(index+1) +1 -1;
	if(ifChildPresent(lci,len) && cmp(a[index],a[lci]) || ifChildPresent(rci,len) && cmp(a[index] , a[rci])){ /* comparision function true means heap property satisfied, no need to swap and go down further*/
	  break;
	}else{
	if(!ifChildPresent(rci,len))
		max = lci;	
	  else
		max = cmp(a[rci], a[lci]) ? rci : lci;
	  swap(a[index],a[max]);
	  heapify(a,len,max,cmp);
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

/* builds an heap structure */
template <typename T>
void BuildHeap(vector<T> &a,int len, bool (*cmp)(int x,int y)){
  for(int i = len/2; i >=0 ; i--){ /* leafs are already heap */
	heapify(a,len,i,cmp);
  }
}
/* 
	sort an array a of integer with length len 
   	* not a stable sort consider the data set 3 1 5 3  
	* its a in place sort. don't need extra space
    * a very good datastructure for doing a partial sort
    * nlogn complexity
    * use in priority queue. biggest/smallest  element in root of tree
    * Linked list (?) 
		heapify operation will become linear O(n)
        so overall complexity become n^2

*/
template<typename T>
void heapsort(vector<T> &a , int len,bool (*cmp)(int x,int y)){
  BuildHeap(a,len,cmp);
  for(int i = len ; i > 0 ; i--){
	swap(a[0],a[i-1]);/* put the max element at the end of array */
	heapify(a,i-1,0,cmp); /* do heapify at index 0 but reduce the array size */
  }	
}
