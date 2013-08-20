#include "../utils.h"
#include <vector>
/* 
	n^2 worst case
   	n best case ( input already sorted.
	Think that invariant is all element to the left of i is sorted

		move the index i forward and the invariant is invalidated
		Fix the invariant failure.
		when the i is the last element the whole array is sorted.
		
*/
void insertionsort(std::vector<int> &v,bool (*compare)(int i,int j)){
  int j = 0;
  for(int i=0;i<v.size();i++){
	int index = i;
	for(j = i-1; j >= 0 ;j--){ // notice i-1 if i than sorting will not happen correctly.
	  if(compare(v[index],v[j])){ // <
		swap(v[index],v[j]);
		index = j; // notice we have to store the j for next iteration of inner loopl.
	  }else{
		break;
	  }
	}
  }
}
