#include<iostream>
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
int searchRotatedSortedArray(int *a,int size,int elem){
  int low =0;
  int high =size -1 ;
  int mid =0;
  while (low <= high){
    mid = (high - low )/2 + low;
	if(a[mid] == elem)
	  return mid;
	if(issorted(a,mid+1,high)){/*upper half is sorted, i.e :  mid +1 - high is sorted */
	  if(isInRange(a,mid+1,high,elem)){ /* check if number is in range */
		low = mid+1;	  
	  }else{
		high = mid -1;
	  }
	}else{ /* lower half is must  be sorted */
	  if(isInRange(a,low,mid-1,elem)){ /* check if number is in lower range */
		high = mid-1;
	  }else{
		low = mid+1;
	  }
	}
   }
  return -1;
}
main(){
  //int a[] = {6,7,8,9,0,1,2,3,4};
  int a[] = {1,1,1,0,1,1,1,1,1,1,1};
  //int a[] = {2,3};
  int peak  = searchRotatedSortedArray(a,sizeof(a)/sizeof(a[0]),0);
  cout << endl <<  peak <<endl;
}
