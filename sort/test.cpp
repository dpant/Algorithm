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
/* compare different sorting versions

Quick Sorting:100000000 took 55.16sec
Shell Sorting:100000000 took 372.33sec
Merge Sorting:100000000 took 37.95sec

*/
int main(){
  void (*sortingAlgo[4])(vector<int> &a,int ,int,bool (*comp)(int,int));	
  sortingAlgo = {mergesort,quicksort,quicksortHeuristic1,quicksortFixForDuplicateKeys};
  vector<int> v;
  //GenerateTestFile("test.txt");	

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

  v = ReadTestFile("test.txt");
  clock_t startc = clock();	
  sort(v.begin(),v.end());
  clock_t endc = clock();
  cout<< "Sorting:" << v.size() << " took " <<  ((double)(endc-startc))/CLOCKS_PER_SEC << "sec" <<endl;

  cout<<std::endl;
}
