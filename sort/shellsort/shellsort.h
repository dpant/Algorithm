#include "../utils.h"
#include <vector>

template <typename T>
void shellsort(std::vector<T> &a, bool (*comp)(int ,int)){
  for(int dist = a.size()/2; dist > 0 ; dist = dist/2){
	for(int i = 0 ; i < dist; i++){
	  int endv =  (a.size()) - ((a.size() -i ) % dist);
	  for(int si = i ; si < a.size(); si = si + dist){
		for(int end  = si ; end >= i + dist ; end = end - dist ){
		  if(comp(a[end],a[end- dist])){
			swap(a[end],a[end-dist]);
		  }
		}
	  }
	}
  } 
}
