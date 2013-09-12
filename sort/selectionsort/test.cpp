#include "../utils.h"
#include "selectionsort.h"
#include <vector>
#include<iostream>
using namespace std;
int main(){
  vector<int> v;
  GenerateTestFile("test.txt");//	Random generated number
  //GenerateTestFile2("test.txt");	/* already sorted file */
  v = ReadTestFile("test.txt");
  clock_t startc = clock();	
  selectionsort(v,&comparef);
  clock_t endc = clock();
  cout<< "Sorting:" << v.size() << " took " <<  ((double)(endc-startc))/CLOCKS_PER_SEC << "sec" <<endl;
  //for(int i=0; i< v.size();i++){
  //	cout << v[i] <<endl;
  //}
  if(!validateSort(v,comparef)){
	std::cout<<"Mismatch. Incorrect sorting"<< std::endl;
  }
  cout<<std::endl;
}
