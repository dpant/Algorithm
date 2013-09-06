#include "../utils.h"
#include "assert.h"
#include "heapsort.h"
#include <vector>
#include <time.h>
#include<iostream>
using namespace std;
int main(){
  vector<int> v;
  // for(int i =0; i < 10;i ++ )
  //	   	v.push_back(i);
  GenerateTestFile("test.txt");	
  v = ReadTestFile("test.txt");
  clock_t startc = clock();	
  int size = v.size();
  heapsort(v,size,&comparef);
  clock_t endc = clock();
  cout<< "Sorting:" << v.size() << " took " <<  ((double)(endc-startc))/CLOCKS_PER_SEC << "sec" <<endl;
  //for(int i=0; i< v.size();i++){
  //	cout << v[i] <<" ";
  //}
  if(!validateSort(v,comparef)){
	std::cout<<"Mismatch. Incorrect sorting"<< std::endl;
  }
  cout<<std::endl;
}
