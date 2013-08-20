#include "../utils.h"
#include "assert.h"
#include "insertionsort.h"
#include <vector>
#include<iostream>
using namespace std;
int main(){
  vector<int> v;
  GenerateTestFile2("test.txt");	
  v = ReadTestFile("test.txt");
  insertionsort(v,&comparef);
  for(int i=0; i< v.size();i++){
	cout << v[i] <<endl;
  }
  assert(validateSort(v,comparef));
}
