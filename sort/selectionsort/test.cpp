#include "../utils.h"
#include "selectionsort.h"
#include <vector>
#include<iostream>
using namespace std;
int main(){
  vector<int> v;
  //GenerateTestFile("test.txt");	Random generated number
  GenerateTestFile2("test.txt");	/* already sorted file */
  v = ReadTestFile("test.txt");
  selectionsort(v,&comparef);
  for(int i=0; i< v.size();i++){
	cout << v[i] <<endl;
  }
}
