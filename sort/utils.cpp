#include<iostream>
#include<set>
#include<fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

bool comparef(int l, int r){	
  return l < r;
}
bool comparefeq(int l, int r){	
  return l <= r;
}
void swap (int &i, int & j){
  int temp = i;
  i = j;
  j = temp;
}

void GenerateTestFile2(string filename){
  enum { DATASIZE = 100000};
  ofstream fobj(filename.c_str(), ios::out);
  if(!fobj.is_open())
	exit(1);
  for(int i = 0 ; i < DATASIZE; i++){
	  fobj << i <<endl;
  }
}

void GenerateTestFile(string filename){
  enum { DATASIZE = 10000000};
  enum { RANGE_START = 0, RANGE_END = 10000000 };
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
void GenerateTestFileDuplicateKeys(string filename){
  enum { DATASIZE = 10000000};
  enum { RANGE_START = 0, RANGE_END = 10000000 };
  set<int> setcontainer;
  ofstream fobj(filename.c_str(), ios::out);
  if(!fobj.is_open())
	exit(1);
  srand(time(0));
  int num =10 ;
  for(int i = 0 ; i < DATASIZE; i++){
	  fobj << num <<endl;
	  if(i % 100000 ==0){
		num++;
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
