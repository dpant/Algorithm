/*
Big picture:: 
	implement a quick find of union find.
	union is still expensive o(n)

key ideas:
  * Try to represend objects a integers for now. Later we will find a way to map objects to integer (symbol table). it simplify the implemention.
  * 

*/
#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;
#if QUICKFIND
class QuickFind{
  int *storage; /* stores the relation between the object id and the component id . How to get object id use symbol table*/
  int size;
public:
  QuickFind(int N){ /* O(n) */
	storage = new int[N];
	size = N;
	for(int i=0 ; i< N; i++){
	  storage[i]= i; /* put each object in different componenet class */
	}
  }
  /* O(1) */
  bool connected(int p,int q){ /* p and q represents object index */
	return storage[p] == storage[q];
  }
  /* This will take linear time O(N) - always */
  void DoUnion(int p,int q){ /* p and q represent object index */
	if(connected(p,q))
	  return;
	for(int i =0; i< size; i++){
	  if(storage[i] == storage[q])
		storage[i] = storage[p];
	}
  }
  ~QuickFind(){
	delete storage;
  }
};


bool test(){
  QuickFind Ufobj(100);
  string line;
	vector<int> v1;
	vector<int> v2;
  ifstream fileobj("test.txt",ios::in);
  if(!fileobj.is_open()){
	exit(1);
  }
  while(getline(fileobj,line)){
	stringstream ss(line);
	int i ;
	ss >> i;
	v1.push_back(i);
	ss>>i;
	v2.push_back(i);
  }
  for(unsigned int i=0 ; i< v1.size(); i++){
	Ufobj.DoUnion(v1[i],v2[i]);
  }
  cout<<"Ufobj.connected(4,8);" << Ufobj.connected(1,0) <<endl;
  return true;
}
#endif

#if QUICKUNION

class QuickUnion{
  int *storage; /* stores the relation between the object id and the component id . How to get object id use symbol table*/
  int size;
public:
  QuickUnion(int N){ /* initialize  O(n) */
	storage = new int[N];
	size = N;
	for(int i=0 ; i< N; i++){
	  storage[i]= i; /* put each object in different component class */
	}
  }
  int Root(int p){ /* returns the root object id - Worst case O(N)*/
	while(storage[p] != p){
	  p = storage[p];
	}
	return p;
  }
  /* O(N) - worst case  */
  bool connected(int p,int q){ /* p and q represents object index */
	return Root(p) == Root(q);
  }
  /* this will take linear time O(N) - worst case - long skinny trees !!*/
  void DoUnion(int p,int q){ /* p and q represent object index */
	storage[Root(p)] = Root(q);
  }
  ~QuickUnion(){
	delete storage;
  }
};


bool test(){
  QuickUnion Ufobj(100);
  string line;
	vector<int> v1;
	vector<int> v2;
  ifstream fileobj("test.txt",ios::in);
  if(!fileobj.is_open()){
	exit(1);
  }
  while(getline(fileobj,line)){
	stringstream ss(line);
	int i ;
	ss >> i;
	v1.push_back(i);
	ss>>i;
	v2.push_back(i);
  }
  for(unsigned int i=0 ; i< v1.size(); i++){
	Ufobj.DoUnion(v1[i],v2[i]);
  }
  cout<<"Ufobj.connected(4,9);" << Ufobj.connected(4,9) <<endl;
  return true;
}
#endif 

/*  
Try to speed up
	connected() //find operation
	DoUnion()   // union

	**weighted size heuristic is used.**  
		only merge small tree below large tree
		this will limit the size of tree to lg(N);

*/
class UnionFind{
  int *storage; /* stores the relation between the object id and the component id . How to get object id use symbol table*/
int *treesize; /* stores the size(number of objects) of trees */
  int size; 
public:
  UnionFind(int N){ /* initialize  O(n) */
	storage = new int[N];
	treesize = new int[N];
	size = N;
	for(int i=0 ; i< N; i++){
	  treesize[i] = 1; /* all tree are of 1 node at the begining */ 
	  storage[i]= i; /* put each object in different component class */
	}
  }
  int Root(int p){ /* returns the root object id - Worst case O(lgN)*/
	while(storage[p] != p){
	  p = storage[p];
	}
	return p;
  }
  /* O(lg N) - worst case  */
  bool connected(int p,int q){ /* p and q represents object index */
	return Root(p) == Root(q);
  }
  /* this will take linear time O(lg N)  !!*/
  void DoUnion(int p,int q){ /* p and q represent object index */
	int proot = Root(p);
	int qroot = Root(q);
	if(treesize[proot] > treesize[qroot]){
	  storage[qroot] = storage[proot];
	  treesize[qroot] += treesize[proot];
	}else{
	  storage[proot] = storage[qroot];
	  treesize[proot] += treesize[qroot];
	}
  }
  ~UnionFind(){
	delete storage;
  }
};


bool test(){
  UnionFind Ufobj(100);
  string line;
	vector<int> v1;
	vector<int> v2;
  ifstream fileobj("test.txt",ios::in);
  if(!fileobj.is_open()){
	exit(1);
  }
  while(getline(fileobj,line)){
	stringstream ss(line);
	int i ;
	ss >> i;
	v1.push_back(i);
	ss>>i;
	v2.push_back(i);
  }
  for(unsigned int i=0 ; i< v1.size(); i++){
	Ufobj.DoUnion(v1[i],v2[i]);
  }
  cout<<"Ufobj.connected(1,7);" << Ufobj.connected(1,7) <<endl;
  return true;
}

int main(){
  test();
  return 0;
}
