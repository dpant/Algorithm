#ifndef _UTILS_
#define _UTILS_
#include <vector>
#include <string>
bool comparef(int l, int r);
void swap (int &i, int & j);
void GenerateTestFile(std::string filename);
std::vector<int> ReadTestFile(std::string filename);
void GenerateTestFile2(std::string filename);

/*compute median(middle) of 3 element */
template <typename T>
int medianof3(T& a,int i,int j,int k){
  if(a[i]>=a[j]){
	if(a[k]>=a[j])
	  return j;
	else if(a[i]>a[k])
	  return k;
	else
	  return i;
  }else{
	if(a[k]>=a[i])
	  return i;
	else if(a[j]>a[k])
	  return k;
	else
	  return j;
  }
}
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
