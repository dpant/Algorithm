#include<iostream>
#include <cstdlib>
using namespace std;
/**

   A rotated sorted array is an array which is sorted (have unique entries) and than rotated.
	eg: 6,7,8,9,0,1,2,3,4,5

   To detect an array(or its subarray) is sorted and rotated we need to check a[start] > a[end]
   if you find a mid of a sortated rotated array it can do the following things
   * partition array in two pieces A) "sorted roated array" B) "sorted array"
   * partition array on two pieces A) "sorted array" B) "sorted rotated Array"
   * partition array in two pieces A) "sorted array" B) "sorted array" in this case it will be max item or min item.
   	
*/
/* logn complexity */
int issorted(int *a, int start,int end){
  return a[start] <= a[end];
}
int isInRange(int *a,int start,int end,int elem){
  if(a[start] <= elem && a[end] >= elem)
	return true;
  else
	return false;
}
int isMinElem(int *a,int size,int index){
  int prev = -1;
  int next = -1;	
  if(index == 0){
	prev = size -1;
  }
  if(index == size-1){
	next = 0;
  }
  if(prev ==-1) 
	prev = index -1;
  if(next == -1){
	next = index +1;
  }
  if(a[prev] > a[index] && a[index] < a[next])
	return true;
  else
	return false;
}
int searchRotatedSortedArrayFindMin(int *a,int size){
  int low =0;
  int high =size -1 ;
  int mid =0;
  while (low <= high){
    mid = (high - low )/2 + low;
	if(isMinElem(a,size,mid))
	  return mid;
	if(issorted(a,mid+1,high)){/*upper half is sorted, i.e :  mid +1 - high is sorted */
		high = mid -1;
	}else{ /* lower half is must  be sorted */
		low = mid+1;
	}
   }
  return -1;
}
main(){
  int a[] = {6,7,8,9,0,1,2,3,4};
  //int a[] = {2,3};
  int peak  = searchRotatedSortedArrayFindMin(a,sizeof(a)/sizeof(a[0]));
  cout << endl <<  peak <<endl;
}
