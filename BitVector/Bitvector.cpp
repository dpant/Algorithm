#include<iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class BitVector{
  int memsize;
  unsigned int *mem; /* unsigned otherwise get() below  wont work for MSB bit of integer chunk*/
  static const int wordsize = sizeof(int) * 8;
public:
  BitVector(long int noofelements):memsize((noofelements/wordsize)+1){ /* assign and initialize to 0 */
	mem = new unsigned int[memsize];
	for(int i =0 ;i < memsize; i ++){
	  mem[i] = 0;
	}
  } 
  bool get(unsigned  int  i){
	return  (mem[i/wordsize] & (0x1 <<  (i % wordsize))) > 0 ;
  }
  void set(unsigned int  i){
	mem[i/wordsize] |= (1 <<  ((i % wordsize)));
  }
  void clr(unsigned int i){
	mem[i/wordsize] &= ~(0x1 <<  (i % wordsize));
  }
  void print(){
	for(int i= 0;i< memsize; i++){
	  printInBinary(mem[i]);
	  cout<< "  ";
	}
	cout <<endl;
  }
  void printInBinary(unsigned int integer){
	for(int i= 0; i < sizeof(int) * 8; i++){
	  cout<< ((integer & ( 1 <<i )) > 0);
	}

  }
  unsigned int numberofelements(){
	return memsize * wordsize;
  }
};
/* load data from input and sort based on bit vector. write the result in a output file*/
void BitSort(const string inputfilename,const string outputfilename){
  string line;
  /* http://stackoverflow.com/questions/492061/why-doesnt-stdstring-provide-implicit-conversion-to-char */	
  ifstream fileobj(inputfilename.c_str(),ios::in); /* ifstream ctor takes const char* rather than string */
  if(!fileobj.is_open())
	exit(1);
  BitVector bv(10000000);
  while(getline(fileobj,line)){
	stringstream ss(line);
	int i;
	ss >> i;
	if(bv.get(i)){
		cout << "duplicate entry in data  " << i <<endl;
		//exit(1);
	}
	bv.set(i);
  }
  ofstream fileobjout(outputfilename.c_str(),ios::out);
  if(!fileobjout.is_open())
	exit(1);
  for(int i =0; i < 1000000; i++){
	if(bv.get(i)){
	  fileobjout << i <<endl;
	}
  }
}
/* load data from input and sort based on bit vector. write the result in a output file*/
void SystemSort(const string inputfilename,const string outputfilename){
  string line;
  vector<int> v;
  v.reserve(1000000);
  /* http://stackoverflow.com/questions/492061/why-doesnt-stdstring-provide-implicit-conversion-to-char */	
  ifstream fileobj(inputfilename.c_str(),ios::in); /* ifstream ctor takes const char* rather than string */
  if(!fileobj.is_open())
	exit(1);
  int k =0;
  while(getline(fileobj,line)){
	stringstream ss(line);
	int i;
	ss >> i;
	v[k++] = i ;
  }
  std::sort(v.begin(),v.end());
  ofstream fileobjout(outputfilename.c_str(),ios::out);
  if(!fileobjout.is_open())
	exit(1);
  for(vector<int>::iterator itr = v.begin(); itr != v.end() ; itr++){
	  fileobjout << *itr <<endl;
  }
}
void CreateTestDataFile(string testdatafile){
  enum x{MAXNUM = 1000000};
  srand(time(0));
  BitVector bv2(10000000);
  ofstream fileobjout(testdatafile.c_str(),ios::out);
  if(!fileobjout.is_open())
	exit(1);
  for(int i = MAXNUM; i > 0; i--){
	int num = int((MAXNUM) *(rand()/(RAND_MAX + 1.0)));
	if(bv2.get(num)){
	  i++;
	  continue;
	}else{
	  bv2.set(num);
	  if(!bv2.get(num)){
		  cout <<"problem in insertion" << num <<endl;
		  exit(1);
	  }
	  fileobjout << num << endl;
	}
  }
}

void test(){
  BitVector b(10000000);
  b.set(31);
  cout << b.get(31);
}

main(){
  CreateTestDataFile("test.txt");
  BitSort("test.txt" , "sorted.txt");
   // SystemSort("test.txt","sorted.txt");
}
