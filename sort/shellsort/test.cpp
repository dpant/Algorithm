#include "../utils.h"
#include "assert.h"
#include "shellsort.h"
#include <vector>
#include<iostream>
using namespace std;
int main(){
  vector<int> v;
  //for(int i =10; i > 0;i -- )
  //	v.push_back(i);
  GenerateTestFile("test.txt");	
  v = ReadTestFile("test.txt");
  shellsort(v,&comparef);
  for(int i=0; i< v.size();i++){
	cout << v[i] <<endl;
  }
  if(!validateSort(v,comparef)){
	std::cout<<"Mismatch. Incorrect sorting"<< std::endl;
  }
}
