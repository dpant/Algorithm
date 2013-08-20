#ifndef _UTILS_
#define _UTILS_
#include <vector>
#include <string>
bool comparef(int l, int r);
void swap (int &i, int & j);
void GenerateTestFile(std::string filename);
std::vector<int> ReadTestFile(std::string filename);
void GenerateTestFile2(std::string filename);

template <typename T>
bool validateSort(std::vector<T> &v,bool (*comparef)(int,int)){

  for(int i=0; i < v.size() -1;i++){
	if(comparef(v[i],v[i+1])){
	}else{
	  return false;
	}
  }
  return true;
}
#endif
