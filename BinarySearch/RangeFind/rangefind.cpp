#include <iostream>
using namespace std;
int upper_boundR(int *a,int start,int end,int elem,int found){
  if(start >= end){
	if(a[start] == elem){
	  return start+1;		
	}else if (found){
	  return start +1;
	}else{
	  return -1;
	}
  }
  int mid = start + (end - lstart)/2;
  if(a[mid] == elem){
	int ind =  upper_boundR(a,mid+1,end,elem,1); /* start and mid can be same so this call can make end < start */
	return ind;
  }else if(a[mid]> elem){
	int ind =  upper_boundR(a,start,mid-1,elem,found); /* start and mid can be same so this call can make end < start */
	return ind;
  } else{
	int ind =  upper_boundR(a,mid+1,end,elem,found); /* end and mid can be same so  this call can make end < start */
	return ind;
  }
}
int lower_boundR(int *a,int start,int end,int elem,int found){
  if(start >= end){
	if(a[start] == elem){
	  return start;		
	}else if (found){
	  return start +1;
	}else{
	  return -1;
	}
  }
  int mid = start + (end - start)/2;
  if(a[mid] == elem){
	int ind =  lower_boundR(a,start,mid-1,elem,1); /* start and mid can be same so this call can make end < start */
	return ind;
  }else if(a[mid]> elem){
	int ind =  lower_boundR(a,start,mid-1,elem,found); /* start and mid can be same so this call can make end < start */
	return ind;
  } else{
	int ind =  lower_boundR(a,mid+1,end,elem,found); /* end and mid can be same so  this call can make end < start */
	return ind;
  }
}
int lower_bound(int *a,int start,int end,int elem){
  lower_boundR(a,start,end,elem,0);
}
int upper_bound(int *a,int start,int end,int elem){
  upper_boundR(a,start,end,elem,0);
}
int main(){
  int a[] = {8,8,8,8,8,8};
  int lowerindex = lower_bound(a,0,sizeof(a)/sizeof(a[0])-1,8);
  cout << lowerindex <<endl;
  int higherindex = upper_bound(a,0,sizeof(a)/sizeof(a[0])-1,8);
  cout << higherindex <<endl;
}


