#include "../utils.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
/* shell sort implemention. much faster than insertion and selection sort */
/* 
	Basic idea:
	sort in different passes with distances d
	no know perfect solution for how to pick perfect sequence for d;
	heuristic solution is to choose sequence 2^i -1

*/

template <typename T>
void shellsort(std::vector<T> &a, bool (*comp)(int ,int)){

  std::vector<int> seq;			
  for(int i=1;i< a.size();i = i*2+1 ){ /* generate the h sorting sequence highest to lowest */
	seq.push_back(i);
  }
  std::sort(seq.begin(),seq.end(),std::greater<int>());

  for(int dist = 0 ; dist < seq.size(); dist++){ /* distance sequence highest to lowest */
	int distv = seq[dist];	

	for(int i  = distv ; i < a.size() ; i++){ /* do h sort passes */
	  for(int si = i ; si >= distv ; si = si - distv){/* now do h sort , go backwards.*/
		if(comp(a[si],a[si - distv])){
		  swap(a[si],a[si-distv]);
		}else{
		  break;
		}
	  }
	}
  }
} 


