#include <iostream>
using namespace std;
int upper_bound(int *a,int start,int end,int elem){
  int mid;
  int foundindex = -1;
  while(start<=end){
	mid = start + (end-start)/2;
	if(a[mid] ==  elem){
	    foundindex = mid+1;
		start = mid+1;
	}else if(a[mid] <= elem){ /* notice <= */
	  start = mid+1;
	}else{
	  end = mid-1;
	}
  }
  return foundindex;
}

int lower_bound(int *a,int start,int end,int elem){
  int mid;
  int foundindex = -1;
  while(start<=end){
	mid = start + (end-start)/2;
	if(a[mid] ==  elem){
	    foundindex = mid;
		end = mid-1;
	}else if(a[mid] < elem){ /* notice <= */
	  start = mid+1;
	}else{
	  end = mid-1;
	}
  }
  return foundindex;
}
int main(){
  int a[] = {1,8,8,8,8,8,8};
  int higherindex = upper_bound(a,0,sizeof(a)/sizeof(a[0])-1,8);
  cout << higherindex <<endl;
  int lowerindex = lower_bound(a,0,sizeof(a)/sizeof(a[0])-1,9);
  cout << lowerindex <<endl;
}


