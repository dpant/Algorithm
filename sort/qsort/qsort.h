#include "../utils.h"
#include <vector>
#include <iostream>
#include <cstdlib>


/* 
	Partition operation, using O(n) time
	** At the end of partition function pivot is in its final position

	** This will have uneven partiton problem if you have many duplicate 
       in the array. Think what happen when you have all the elements same 
       in the arrray?.
 */
template <typename T>
int partition(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  int i = start;
  int j = end;
  int randindex = start + (end -start) *(rand()/(RAND_MAX +1.0));
  swap(a[randindex],a[start]); /* put pivot in it final position */	
  T pivot = a[start]; /* pivot element */
  while(i<j){ /* we can make it while(1) */
	while(a[i] <= pivot && i < end) {
		i++;
	}
	while(a[j] > pivot && j > start){/* at end j will point to element which is smaller than or equal to pivot */
		 j--;
	}
	if(j <= i){
	  break; 
	}else if(j ==i){ /* to avoid unnecessary swaps */
	}else{ /* out of order relative to pivot element swap */
	  swap(a[i],a[j]);
	}
  }
  swap(a[start],a[j]); /* put pivot in it final position */
  return j;
}

/* 
perform the recursive quick sort
elements are part of array/vector a
start and end index are both inclusive [start,end]
* complexity (nlogn) for random inputs
* complexity n^2 for already sorted inputs or reverse sorted inputs
* bottom line is if you are choosing a pivot such that it just add one element 
  in the sorted sequence then you are going to hit worst case complexity
  eg
   array 1,3,5,4,2
   Pivot selection of [1,2,3,4,5] or [5,4,3,2,1] will give n^2 complexity.

   (Use randomized quicksort version to avoid these cases.)
   or you can use median of 3 to decide the pivot element


*/
template<typename T>
void quicksort(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  srand(time(0)); /* make qsort random - based on time seed */
  quicksortR(a,start,end,comp);
}

template<typename T>
void quicksortR(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  int pindex = partition(a,start,end,comp);
  if(pindex - start > 0)/* Can we move this check if(start<= end) at begining of fucntion ? */
	  quicksortR(a,start,pindex-1,comp);
  if(end - pindex > 0)
	  quicksortR(a,pindex+1,end,comp);
}

/* median of 3 heuristic for quicksort */
template<typename T>
void quicksortHeuristic1(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  if(end <=start)
	return;
  int pivot = medianof3(a,start,start + (end -start)/2,end);
  swap(a[start],a[pivot]); /* put pivot in it start position */
  int pindex = partition(a,start,end,comp);

  quicksort(a,start,pindex-1,comp);
  quicksort(a,pindex+1,end,comp);
}


/* 
	Partition operation, using O(n) time
	** At the end of partition function pivot is in its final position

	** This will **NOT** have uneven partiton problem if you have many duplicate 
       in the array. Think what happen when you have all the elements same 
       in the arrray?.
 */
template <typename T>
int partition2(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  int i = start;
  int j = end;
  int randindex = start + (end -start) *(rand()/(RAND_MAX +1.0));
  swap(a[randindex],a[start]); /* make qsort randomized */
  T pivot = a[start]; /* pivot element */
  /* std::cout << "random-Index" << randindex << std::endl;
  for(i = 0 ; i < a.size(); i++){
	std::cout << a[i] <<" ";
	}
  std::cout << std::endl;
  */
  i = start +1; /* this is important now since the first while is changed */
  while(1){ /* we can make it while(1) */

	while(a[i] < pivot && i < end) { /* notice < avoid n^2 loop in qsort for identical input */
		i++;
	}
	while(a[j] > pivot && j >= start){/* at end j will point to element which is smaller than or equal to pivot */	
	 j--;
	}
	if(j <= i){
	  break; 
	}else{ /* out of order relative to pivot element swap */
	  swap(a[i++],a[j--]);
	}
  }
  swap(a[start],a[j]); /* put pivot in it final position */
  /* std::cout << "j" << j  << std::endl;
  for(i = 0 ; i < a.size(); i++){
	std::cout << a[i] <<" ";
  }
  std::cout << std::endl;
  */
  return j;
}

/* avoids n^2 complexity in array with many input identical */

template<typename T>
void quicksortRadomFixForDupKeys(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
   
  if(end <= start)
	return;
  int pindex = partition2(a,start,end,comp);

  quicksortRadomFixForDupKeys(a,start,pindex-1,comp);
  quicksortRadomFixForDupKeys(a,pindex+1,end,comp);
}



/* avoids n^2 complexity in array with many input identical */
template<typename T>
void quicksortFixForDuplicateKeys(std::vector<T>& a,int start,int end,bool (*comp)(T,T)){
  srand(time(0));    /* make qsort randomized - random seed based on time */
  quicksortRadomFixForDupKeys(a,start,end,comp);
}
