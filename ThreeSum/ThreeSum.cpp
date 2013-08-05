#include<iostream>
#include<set>
#include<fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void GenerateTestFile(string filename){
  enum { DATASIZE = 1000};
  enum { RANGE_START = -1000, RANGE_END = 1000 };
  set<int> setcontainer;
  ofstream fobj(filename.c_str(), ios::out);
  if(!fobj.is_open())
	exit(1);
  srand(time(0));
  for(int i = 0 ; i < DATASIZE; i++){
	int randomnum = RANGE_START + (int) (RANGE_END - RANGE_START) * (rand()/(RAND_MAX + 1.0));
	if(setcontainer.find(randomnum) != setcontainer.	end()){
	  i --;
	  continue;
	}else{
	  fobj << randomnum <<endl;
	  setcontainer.insert(randomnum);
	}
  }
}
vector<int> ReadTestFile(string filename){
  vector<int> v;
  string line;
  ifstream fobj(filename.c_str(), ios::in);
  if(!fobj.is_open())
	exit(1);
  while(getline(fobj,line)){
	int i=0;
	stringstream s(line);
	s >> i;
	if((s.rdstate() & std::ifstream::failbit) != 0 ){
	  cout<< "Error: Unexpected input in test file:" << filename  <<endl;
	  exit(1);
	}
	v.push_back(i);
  }
  return v;
}
/* 
    N^3 solution for ThreeSum.
	Notice here the loop below j starts from i+1 and k starts from j+1
    This is needed for correctness otherwise you will count same tuple multiple times (incorrect version)

    * Also note that inside if(v[i]+v[j]+v[k]) can be improve to handle overflow!

*/

int ThreeSumBruteForce(vector<int> v){
  int total = 0;
  for(int i=0;i< v.size();i++){
	for(int j= i+1; j < v.size();j++){ /* notice i+1 , not only for the speed but for correctness*/
	  for(int k= j+1 ; k <  v.size(); k++){ /* notice j+1 , not only for the speed but for correctness*/
		if(v[i] + v[j]+ v[k] ==0){
		  //cout<<i<<" "<<j<<" "<<k<<"       "<< v[i] << " " <<v[j] << "  "<<v[k] <<" "<<endl;
		  total ++;
		}
	  }
	}
  }
  return total;
}
/*
Uses hash to speed up
notice " if( (it = m.find(-(v[i]+v[j]))) != m.end() && it->second > i && it->second > j)"
it->second() > i && it->second() > j to avoid counting same tuple multiple times

*/
int ThreeSumN2(vector<int> v){
  int total = 0;
  map<int,int> m;
  map<int,int>::iterator it;
  for(int i =0 ; i < v.size(); i++){
	m.insert(std::pair<int,int>(v[i],i));
  }
  for(int i=0;i< v.size();i++){
	for(int j= i+1; j < v.size();j++){ /* notice i+1 */
	  if( (it = m.find(-(v[i]+v[j]))) != m.end() && it->second > i && it->second > j){
		//cout<<i<<" "<<j<<" "<< it->second <<"       "<< v[i] << " " <<v[j] << "  "<< it->first <<" "<<endl;
		total ++;
	  }
	}
  }
  return total;
}

int main(){
  vector<int> v;
  int total;
  GenerateTestFile("test.txt");
  v = ReadTestFile("test.txt");
  total = ThreeSumBruteForce(v);
  cout << "Total pair found " << total  <<endl;
  total = ThreeSumN2(v);
  cout << "Total pair found " << total  <<endl;
}







