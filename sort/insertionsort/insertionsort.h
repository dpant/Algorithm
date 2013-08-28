#include "../utils.h"
#include <vector>
/* 
	n^2 worst case (input reverse sorted)
   	n best case (input already sorted).

	Think that invariant is all element to the left of an "index i" is sorted

		1) move the index i forward and the invariant is invalidated
		2) Fix the invariant failure.
		3) when the i is the last element the whole array is sorted.

	Also notice that the number of swap performed in insertion sort is equal to
	the number of inversion in the array (pair wise element which are out of or      der)
		
*/
void insertionsort(std::vector<int> &v,bool (*compare)(int i,int j)){
  int j = 0;
  for(int i=0;i<v.size();i++){
	int index = i;
	for(j = i; j > 0 ;j--){ // notice j > 0 otherwise run out of bound
	  if(compare(v[j],v[j-1])){ // <
		swap(v[j],v[j-1]);
	  }else{
		break;
	  }
	}
  }
}
