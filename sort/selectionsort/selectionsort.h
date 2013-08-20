#include "../utils.h"
#include <vector>
template <typename T>
/* 
	 n^2 worst case
	 n^2 best case (Even if the input array is sorted)
	
*/
void selectionsort(std::vector<T> &a,bool (*compare)(int l,int r)){
  int mini;
  for(int i =0; i< a.size();i++){
    mini = i;
	for(int j=i; j< a.size() -1; j++){	
	  if(compare(a[mini],a[j+1])){ // < 
	  }else{
		mini = j+1;
	  }
	}
	swap(a[mini],a[i]);
  }
}
