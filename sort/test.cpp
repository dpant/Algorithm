#include "utils.h"
#include "assert.h"
#include "./qsort/qsort.h"
#include "./mergesort/mergesort.h"
#include "./shellsort/shellsort.h"
#include "./selectionsort/selectionsort.h"
#include "./insertionsort/insertionsort.h"
#include <vector>
#include <time.h>
#include<iostream>
using namespace std;
int main(){
  void (*sortingAlgo[100])(vector<int> &a,int ,int,bool (*comp)(int,int));	
  sortingAlgo = {quicksort,shellsort,mergesort};
  vector<int> v;
  GenerateTestFile("test.txt");	
  for(int i =0 ; i < 3;i++){
	v = ReadTestFile("test.txt");
	clock_t startc = clock();	
	(*sortingAlgo[i])(v,0,v.size()-1,&comparef);
	clock_t endc = clock();
	cout<< "Sorting:" << v.size() << " took " <<  ((double)(endc-startc))/CLOCKS_PER_SEC << "sec" <<endl;

	if(!validateSort(v,comparef)){
	  std::cout<<"Mismatch. Incorrect sorting"<< std::endl;
	}
  }
  cout<<std::endl;
}
