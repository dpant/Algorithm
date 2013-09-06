#include "../utils.h"
#include <vector>
#include <iostream>


/* 
	Partition operation, using O(n) time
 */
template <typename T>
int partition(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  int i = start;
  int j = end;
  while(i<j){
	while(a[i] <= a[start] && i < end) {
		i++;
	}
	while(a[j] > a[start] && j > start){
		 j--;
	}
	if(j <= i){
	  return j;
	}else if(j ==i){

	}else{
	  swap(a[i],a[j]);
	}
  }
  return j;
}

/* 
perform the recursive quick sort
elements are part of array a
start and end index are both inclusive [start,end]

*/
template<typename T>
void quicksort(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  int pindex = partition(a,start,end,comp);
  swap(a[start],a[pindex]);
#if 0
  std::cout<< pindex << std::endl;
  for(int i=0;i<a.size();i++){
	std::cout<< a[i]<< " ";
  }
  std::cout<< std::endl;
#endif 
  if(pindex - start > 0)
	  quicksort(a,start,pindex-1,comp);
  if(end - pindex > 0)
	  quicksort(a,pindex+1,end,comp);
}
