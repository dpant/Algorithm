#include<iostream>
using namespace std;
/*
An array is bitonic if it is comprised of an increasing sequence of integers followed immediately by a decreasing sequence of integers. Write a program that, given a bitonic array of N distinct integer values, distinct integer values, determines whether a given integer is in the array.
*/

/* logn complexity */
int searchbitonicarrayPeak(int *a,int size){
  int low =0;
  int high =size -1 ;
  int mid =0;
  while (low <= high){
    mid = (high - low )/2 + low;
	if(mid-1 >=0 && mid+1 <= size-1 && a[mid]> a[mid-1] && a[mid] > a[mid+1]){ // found it
	  return mid;  
	}else if(mid-1 >=0 && mid+1 <= size-1 && a[mid] > a[mid-1] && a[mid] <a[mid+1]){ //part of increasing seq
	  low = mid+1;
	}else{ // part of dec seq
	  high = mid-1;
	}
  }
  return -1;
}

main(){
  // int a[] = {0,1,2,3,4,10,9,8,7,6,5};
  int a[] = {2,3};
  int peak  = searchbitonicarrayPeak(a,sizeof(a)/sizeof(a[0]));
  cout << endl <<  peak <<endl;
	
	
}
