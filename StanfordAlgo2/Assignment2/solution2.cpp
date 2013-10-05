#include <iostream>
#include <vector>
#include <sstream>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <fstream>
#include "../../UnionFind/UnionFind.h"
#include <algorithm>
using namespace std;

class Edge;
class Vertex{
public:
  int index;
  int code;
  vector<Edge *> edgelist;
  Vertex(int i,int c):index(i),code(c){}
  void addEdge(Edge *e){
    edgelist.push_back(e);
  }
};
class Edge{
public:
  int weight;
  Vertex* start;
  Vertex* end;
  Edge(Vertex* s,Vertex* e, int w):weight(w),start(s),end(e){}
};

class Graph{
public:
  vector<Edge *> edgelist;
  vector<Vertex *> vertexlist;

  Vertex* findVertex(int id){
	for(int i =0; i< vertexlist.size(); i++){
	  if(vertexlist[i]->index == id)
		return vertexlist[i];		
	}
	return NULL;
  }
  Vertex* addVertex(int i,int code){
	  Vertex *nv = new Vertex(i,code);
      vertexlist.push_back(nv);
	  return nv;
  }
  Edge * addEdge(Vertex* s, Vertex* e, int w){
	Edge *edge = new Edge(s,e,w);
	edgelist.push_back(edge);	
    s->addEdge(edge);
	return edge;
  }
  
};
Graph* ReadTestFile(string filename){
  int sv,ev,weight;
  string line;
  int bit;
  int num;
  ifstream fobj(filename.c_str(), ios::in);
  if(!fobj.is_open()){
	cout << "can't open input file to read" << endl;
	exit(1);
  }
  Graph* G = new Graph();
  Vertex *src,*end;
  Edge* e;
  int lineindex =0 ;
  while(getline(fobj,line)){

	int i=0;
	stringstream s(line);
	if(lineindex ==0){
		s >> i;
		lineindex++;
		continue;
	}else{
	  num = 0;
	  while(s >> bit){
		num = num <<  1;
		if(bit)
		  num = num +1;
	  }
	}
	s.clear();
	if((s.rdstate() & std::ifstream::failbit) != 0 ){
	  cout<< "Error: Unexpected input in test file:" << filename  <<endl;
	  exit(1);
	}
    G->addVertex(lineindex-1,num);

	lineindex ++;
  }
  return G;
}

struct less_than_key
{
    inline bool operator() (const Vertex* struct1, const Vertex* struct2)
    {
        return (struct1->code < struct2->code);
    }
};
struct less_than_key2
{
  inline bool operator() (const Vertex* struct1,int value)
    {
        return (struct1->code < value);
    }
};
struct less_than_key3
{
  inline bool operator() (int value , const Vertex* struct1)
    {
        return (value < struct1->code	);
    }
};
int  DoClustering(Graph *G){
  //sort the edges with weights
  UnionFind uf(200000);// index in our UnionFind start with 0	
  sort(G->vertexlist.begin(),G->vertexlist.end(),less_than_key());
  for(int i =0; i< G->vertexlist.size();i++){
	Vertex* vertex = G->vertexlist[i];
	int code = vertex->code;
    // find nearby codes
    for(int x = 0 ; x< 24;x++){ /* dist 0 */
	  int nval = code ;
	  vector<Vertex*>::iterator lower = lower_bound(G->vertexlist.begin(), G->vertexlist.end(), nval, less_than_key2());
	  vector<Vertex*>::iterator upper = upper_bound(G->vertexlist.begin(), G->vertexlist.end(), nval, less_than_key3());
	  if (lower == G->vertexlist.end()){ // not found
		continue;
	  }else{
		for(vector<Vertex*>::iterator itr = lower;itr !=upper;itr++){
		  if(!uf.connected(vertex->index,(*itr)->index)){
			uf.DoUnion(vertex->index,(*itr)->index);
		  }
		}
	  }
	}
    for(int x = 0 ; x< 24;x++){ /* dist 1 */
	  int nval = code ^ (1 << x);
	  vector<Vertex*>::iterator lower = lower_bound(G->vertexlist.begin(), G->vertexlist.end(), nval, less_than_key2());
	  vector<Vertex*>::iterator upper = upper_bound(G->vertexlist.begin(), G->vertexlist.end(), nval, less_than_key3());
	  if (lower == G->vertexlist.end()){ // not found
		continue;
	  }else{
		for(vector<Vertex*>::iterator itr = lower;itr !=upper;itr++){
		  if(!uf.connected(vertex->index,(*itr)->index)){
			uf.DoUnion(vertex->index,(*itr)->index);
		  }
		}
	  }
	}
	for(int x = 0; x<24;x++){
	  for(int y = x+1 ; y<24;y++){
		int nval = code ^ ( (1 << x) | (1 << y));
		vector<Vertex*>::iterator lower = lower_bound(G->vertexlist.begin(), G->vertexlist.end(), nval, less_than_key2());
		vector<Vertex*>::iterator upper = upper_bound(G->vertexlist.begin(), G->vertexlist.end(), nval, less_than_key3());
		if (lower == G->vertexlist.end()){ // not found
		  continue;
		}else{
		  for(vector<Vertex*>::iterator itr = lower;itr !=upper;itr++){
			if(!uf.connected(vertex->index,(*itr)->index)){
			  uf.DoUnion(vertex->index,(*itr)->index);
			}
		  }
		}	
	  }
	}
  } /* outer for ends */
  cout << "----" << uf.clustersremaining << endl;
  int maxs =100000000;
#if 0
  for(int i =0; i< G->edgelist.size();i++){
	Edge* edge = G->edgelist[i];
	if(uf.connected(edge->start->index,edge->end->index))
	  continue;
	else
	  maxs = min(maxs,edge->weight);
  }
#endif 
  return maxs;
  
}
main(){
  Graph* G;
  G = ReadTestFile("testGraph2.txt");
  sort(G->vertexlist.begin(),G->vertexlist.end(),less_than_key());
  for(int i =0 ;i < G->vertexlist.size(); i++){
	cout<< G->vertexlist[i]->index << "--> " << G->vertexlist[i]->code << endl;
  }
  
#if 0
  for(int i =0; i< G->vertexlist[1]->edgelist.size();i++){
	cout<< G->vertexlist[1]->edgelist[i]->weight << " " ;
  }
#endif
  cout << DoClustering(G) << endl;

  //uf.connected();
  //uf.DoUnion()
}
