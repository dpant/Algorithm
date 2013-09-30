#include <iostream>
#include <vector>
#include <sstream>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <fstream>
#include "../../UnionFind/UnionFind.h"
#include <algorithm>
#include <utility>
using namespace std;


void  ReadTestFile(vector< pair<int,int> >& data,string filename){
  string line;
  ifstream fobj(filename.c_str(), ios::in);
  if(!fobj.is_open()){
	cout << "can't open input file to read" << endl;
	exit(1);
  }
  int value,weight,knapsackSize,numberofItems;
  int lineindex =0 ;
  while(getline(fobj,line)){

	int i=0;
	stringstream s(line);
	if(lineindex ==0){
	  s >> knapsackSize;
	  s >> numberofItems;
	  data.push_back(make_pair(knapsackSize,numberofItems));		
	  lineindex++;
	  continue;
	}else{
	  s >> value;
      s >> weight;
	}
   
	if((s.rdstate() & std::ifstream::failbit) != 0 ){
	  cout<< "Error: Unexpected input in test file:" << filename  <<endl;
	  exit(1);
	}
	data.push_back(make_pair(value,weight));
	lineindex ++;
  }			   
}

main(){
  vector< pair<int,int> > d;
  ReadTestFile(d,"knapsack_big.txt");
  int val,val1,val2,val3;
  int** OptSolutionCost;
  for(int i =0 ; i < 2001;i ++){
	  OptSolutionCost[i] = new int[2000000+1];// = new int[d[0].second * d[0].first+1]; // knapsacksize,number of items
  }
  int knapsackSize = d[0].first;
  int numberofItems  = d[0].second;
  for(int i =0; i <= numberofItems; i ++){ /* initialize weight 0 to 0 */
	OptSolutionCost[i][0]=0;
  }
  for(int i =0; i <= knapsackSize; i ++){ /* item 0 is null item */
	OptSolutionCost[0][i]=0;
  }
  for(int w=1; w <= knapsackSize; w++) { // weight index from 1 to d[0].first
  	for(int i = 1 ; i <= numberofItems;i++){ // item index from 1 to d[0].second 
	  int itemw = d[i].second;
	  int itemv = d[i].first;
	  int val2 =  w-itemw >=0 ? OptSolutionCost[i-1][w-itemw] + itemv:0;
	  int val = max(OptSolutionCost[i-1][w], val2);
	  OptSolutionCost[i][w] = val;
	} /* inner for ends */
  } /* outer for ends */
  for (int i=0;i<5;i++){
	for(int j =0;j<7;j++){
	  cout<< OptSolutionCost[i][j] << " ";
	}
	cout<< endl;
  }
  cout<< OptSolutionCost[d[0].second][d[0].first];
}
		

