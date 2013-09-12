#include "../utils.h"
#include "assert.h"
#include "mergesort.h"
#include <vector>
#include<iostream>
using namespace std;
int main(){
  vector<int> v;
  // for(int i =10; i > 6;i -- )
  //	   	v.push_back(i);
  GenerateTestFile("test.txt");	
  v = ReadTestFile("test.txt");
  clock_t startc = clock();	
  mergesort(v,0,v.size()-1,&comparef);
  clock_t endc = clock();
  cout<< "Sorting:" << v.size() << " took " <<  ((double)(endc-startc))/CLOCKS_PER_SEC << "sec" <<endl;
  if(!validateSort(v,comparef)){
	std::cout<<"Mismatch. Incorrect sorting"<< std::endl;
  }
  cout<<std::endl;
}
