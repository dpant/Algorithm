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
#include "UnionFind.h"
using namespace std;
/*  
Try to speed up
	connected() //find operation
	DoUnion()   // union

	** Use the path compression and weighted (by size) heuristic .**  
		only merge small tree below large tree
		path compression will make the tree almost flat!!!

*/

UnionFind::UnionFind(int N){ /* initialize  O(n) */
  storage = new int[N];
  treesize = new int[N];
  size = N;
  for(int i=0 ; i< N; i++){
	treesize[i] = 1; /* all tree are of 1 node at the begining */ 
	storage[i]= i; /* put each object in different component class */
  }
}
int UnionFind::Root(int p){ /* returns the root object id - Worst case O(lgN) - do path compression */
  int root,elem,parent;
  elem = p;
  while(storage[p] != p){
	p = storage[p];
  }
  /* now flatten the tree - to achieve the path compression*/
  root = p;
  while(storage[elem] != root){
	parent = storage[elem];
	storage[elem] = root;
	elem = parent;
  }
  return root;
}
/* O(lg N) - worst case  */
bool UnionFind::connected(int p,int q){ /* p and q represents object index */
  return Root(p) == Root(q);

}
/* this will take linear time O(lg N)  !!*/
void UnionFind::DoUnion(int p,int q){ /* p and q represent object index */
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
UnionFind::~UnionFind(){
  delete storage;
}
