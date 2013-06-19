/*
Big picture:: 
	implement a quick find of union find.
	union is still expensive o(n)

key ideas:
  * Try to find the percolation limit (in percentage) by monte Carlo simulation. (No analytical solution know so far)
  

*/
#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "../UnionFind.h"
using namespace std;
enum SITESTATE{
  BLOCKED,OPEN
};
enum LOCATION{
  LEFT,RIGHT,TOP,BOTTOM
};
class Percolation {
  int *storage ;
  int dim;
  UnionFind* Ufobj;
public:
   Percolation(int N){              // create N-by-N grid, with all sites blocked
	 dim = N;
	 storage = new int[N*N];
	 for(int i=0; i< N*N ;i ++){
	   storage[i] = BLOCKED;
	 }
	 initPercolate();
   }
  void open(int i, int j){         // open site (row i, column j) if it is not already
	int neighbour;
	storage[i * dim + j] = OPEN;
	i = i * dim + j;
	for(int j = 0 ; j < 4 ; j++){ /* build the connections */
	  neighbour = calculateIndex(i,(LOCATION)j);		
	  if(neighbour != -1 && isOpen(neighbour/dim,neighbour%dim)) 
		Ufobj->DoUnion(i,neighbour);
	}	
  }
   bool isOpen(int i, int j){    // is site (row i, column j) open?
	 return storage[i*dim + j];
   }
   bool isFull(int i, int j){    // is site (row i, column j) full?
	 return false;	
   }
  void initPercolate(){
	 int topPseudoVarIndex = dim*dim;
	 int bottomPseudoVarIndex = topPseudoVarIndex +1;
	 Ufobj = new UnionFind(dim*dim+2); /* 0 to dim*dim -1 is regular grid var */
	 for(int i =0;i< dim;i++){ /* top row */
	   Ufobj->DoUnion(topPseudoVarIndex,i);
	 }	
	 for(int i =dim*(dim-1);i< dim*dim;i++){ /* bottom row */
	   Ufobj->DoUnion(bottomPseudoVarIndex,i);
	 }	
  }

   void BuildBatchConnection(){            // does the system percolate?

	 for(int i=0;i<dim*dim;i++){ /*build connection to neighbour sites*/
	   int neighbour;
	   if(isOpen(i/dim,i%dim)){ /* if this is open site cal the connection to open neighbour */
		 for(int j = 0 ; j < 4 ; j++){
		   neighbour = calculateIndex(i,(LOCATION)j);		
		   if(neighbour != -1 && isOpen(neighbour/dim,neighbour%dim)) 
			 Ufobj->DoUnion(i,neighbour);
		 }
	   }
	 }
   }
  bool percolates(){
	int topPseudoVarIndex = dim*dim;
    int bottomPseudoVarIndex = topPseudoVarIndex +1;
 	return Ufobj->connected(topPseudoVarIndex,bottomPseudoVarIndex);		 
  }
  int calculateIndex(int i,LOCATION loc){
	int index;
	if(loc == LEFT){
	  index = i - 1;
  	  if (index > 0 && ((index / dim) == (i / dim))) /* same row */
		  return index;
	}else if(loc == RIGHT) {
	  index = i + 1;
	  if ((index < (dim * dim)) && ((index / dim) == (i / dim))) /* same row */
		  return index;
	}else if(loc == TOP){
	  index = i - dim;
	  if ((index / dim >= 0 ) && ((index / dim) + 1 == (i / dim)))
		  return index;
	}else if (loc == BOTTOM){
	  index = i + dim;
	  if (((index / dim) < dim) && ((index / dim)  == (i / dim) + 1 ))
		  return index;
    }
    return -1;
  }
	  
};
int GenerateRandomNumberBetweenRange(int lowest,int highest){ /* generate Random number between [lowest,highest) - higheset non inclusive */
	
    int random_integer; 
    int range=(highest-lowest); 
	random_integer = lowest+int(range*(rand()/(RAND_MAX + 1.0)));
	return random_integer;
}	
void  RunMonteCarlo(){
  int size = 10000;
  int opensites = 0;
  Percolation* pobj = new Percolation(size);
  srand((unsigned)time(0));  /* system call should not be inside the loop */
  while(1){
	int sindex = GenerateRandomNumberBetweenRange(0,size*size);
	if(pobj->isOpen(sindex/size,sindex%size)){
	  continue;
	}
	//cout<< "Adding site: " << sindex << " As open" <<endl;
	pobj->open(sindex/size,sindex%size);
	opensites++;
	if(pobj->percolates()){
	  cout<< "percolation started after: " << opensites << "out of " << size * size <<endl;
	  break;
	}
   
  }
	
}
void TestMonteCarlo(){
  int size = 5;
  int opensites = 0;
  Percolation* pobj = new Percolation(size);
  pobj->open(7/size,7%size);
  pobj->open(6/size,6%size);
  pobj->open(5/size,5%size);
  
  if( pobj->percolates()){
	  cout<< "percolation started after: " << opensites << "out of " << size * size <<endl;

	}
 
}

int  main(){
  RunMonteCarlo();
	
  return 1;
}
