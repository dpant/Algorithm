/*
	Binary Search.

*/
#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "UnionFind.h"
using namespace std;

/*
	Return the index to key in the array 
	Returns -1 if key not found 
*/
int BinarySearch(int* array,int len, int key){
  /* int len = sizeof(array)/sizeof(array[0]); can't do this !!! */
  int low = 0;
  int mid = 0;
  int high = len-1;
  while(low <= high){ /* notice <= rather than < */
	mid  = low + (high - low)/2; // to prevent overflow
	if(key < array[mid]){
	  high = mid -1;
	}else if( key > array[mid]){
	  low  = mid+1;
	}else{
	  return mid;
	}
  }
  return -1;
}
#define MYARRSIZE(X) (sizeof(X)/sizeof(X[0]))
int main(){
  int myarr[] = {0,1,2,3,4,5,6,7,8,9};
  cout<< BinarySearch(myarr,MYARRSIZE(myarr),9) << endl;
}
