#include "../utils.h"
#include "assert.h"
#include "insertionsort.h"
#include <vector>
#include<iostream>
#include <time.h>
using namespace std;
int main(){
  vector<int> v;
  GenerateTestFile("test.txt");	
  v = ReadTestFile("test.txt");
  clock_t startc = clock();	
  insertionsort(v,&comparef);
  clock_t endc = clock();
  cout<< "Sorting:" << v.size() << " took " <<  ((double)(endc-startc))/CLOCKS_PER_SEC << "sec" <<endl;
  // for(int i=0; i< v.size();i++){
  //	cout << v[i] <<endl;
  //}
  if(!validateSort(v,comparef)){
	std::cout<<"Mismatch. Incorrect sorting"<< std::endl;
  }
}
