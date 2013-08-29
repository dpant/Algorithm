#include "../utils.h"
#include <vector>
#include <iostream>

/* 
perform the bottomup  mergesort
elements are part of array a
start and end index are both inclusive [start,end]
This is a iterative version of mergesort.

*/
template<typename T>
void mergesortBottomup(T *a,T* temp,int start,int end,bool (*comp)(T,T)){
  int size = (end - start + 1);
  for(int gap =1 ; gap < size; gap *=2){ /* gap represent size of one subarray while merging */
	for(int i= 0; i < size; i += 2*gap){ /* find out all chunks which need to be merged withing array bounds  */
	  int end,mid;
	  end = i + 2* gap -1;
	  end = (end < size) ? end: size -1;
	  mid =  i + gap -1;
	  mid = (mid< size)? mid: size -1;

	  merge(a,temp,i,mid,end,comp);
	}
  }
}

/* 
Merge operation, using aux space O(n) for merging.



In place merge is more complex and eats more runtime.
so inplace merge is only used when memory requirement is tight

* you can always create an auxilary array inside the merge routine,
but to save time of creating and destructing the array better to pass 
fixed size array to the function.

** implemented keeping in mind to make the merge operation stable 
merge elements of v[start..mid] and v[mid+1... end]
results are stored back to v.

 */
template <typename T>
void merge(T* v, T* aux,int start,int mid,int end,bool (*comp)(T,T)){
  int len = end - start +1;
  int i,j,k;

  i = start;
  j = mid+1;	
  for(int i = start; i<=end; i++)
	aux[i] = v[i];
  for(k=start;k<=end;k++){
	if(i > mid){
	  v[k] = aux[j++];
	  continue;
	}
	if(j > end){
	  v[k] = aux[i++];
	  continue;
	}
	if(!comp(aux[i],aux[j])){ /* notice this will make merge operation stable  */
	  v[k] = aux[j++];
	}else{
	  v[k]= aux[i++];
	}
  }	
}

/* Do merge sort on a vector  */
template <typename T>
void mergesort(std::vector<T> &a, bool (*comp)(T ,T)){
  T* temp = new T[a.size()]; /* aux array for merge op */
  T* inputarray = new T[a.size()]; // notice even if we need temp array of smaller size we allocate bigger to simplify in merge routine

  for(int i =0 ;i <a.size();i++){ /* store in array to make aux and temp same */
	temp[i] = inputarray[i] = a[i];
  }

  mergesortBottomup(inputarray,temp,0,a.size()-1,comp);

  for(int i =0 ;i <a.size();i++){ /* store back to vector */
	a[i] = inputarray[i];
  }

  delete[] temp;
  delete[] inputarray;
}

/* Do merge sort on a array  */
template <typename T>
void mergesort(T *a,int size, bool (*comp)(T ,T)){
  T* temp = new T[size]; /* aux array for merge op */
  mergesortBottomup(a,temp,0,size-1,comp);
  delete[] temp;
}
