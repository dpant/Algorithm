#include<iostream>
using namespace std;

class BitVector{
  int memsize;
  unsigned int *mem; /* unsigned otherwise get() below  wont work for MSB bit of integer chunk*/
  static const int wordsize = sizeof(int) * 8;
public:
  BitVector(long int noofelements):memsize((noofelements/wordsize)){
	mem = new unsigned int[memsize];
  } 
  bool get(unsigned long int  i){
	return  mem[i/wordsize] & (0x1 <<  (i % wordsize)) > 0 ;
  }
  void set(long i){
	mem[i/wordsize] |= (1 <<  ((i % wordsize)));
  }
  void clr(long i){
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
};


main(){
  BitVector b(64);
  for(int i =0 ;i < 64; i ++){
	b.set(i);
	b.print();
	b.clr(i);
	}
}
