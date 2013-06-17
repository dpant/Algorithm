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

/*  
Try to speed up
	connected() //find operation
	DoUnion()   // union

	** Use the path compression and weighted (by size) heuristic .**  
		only merge small tree below large tree
		path compression will make the tree almost flat!!!

*/
class UnionFind{
  int *storage; /* stores the relation between the object id and the component id . How to get object id use symbol table*/
int *treesize; /* stores the size(number of objects) of trees */
  int size; 
public:
  UnionFind(int N);
  int Root(int p);
  bool connected(int p,int q);
  void DoUnion(int p,int q);
  ~UnionFind();
};

