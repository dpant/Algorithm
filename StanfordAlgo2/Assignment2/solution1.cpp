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
  vector<Edge *> edgelist;
  Vertex(int i):index(i){}
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
  Vertex* addVertex(int i){
	  Vertex *nv = new Vertex(i);
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
	  s >> sv;
      s >> ev;
	  s >> weight;
	}
	
	if((s.rdstate() & std::ifstream::failbit) != 0 ){
	  cout<< "Error: Unexpected input in test file:" << filename  <<endl;
	  exit(1);
	}
	if (!(src = G->findVertex(sv))){
	  src = G->addVertex(sv);
	}
	if (!(end =G->findVertex(ev))){
	  end = G->addVertex(ev);
	}
	G->addEdge(src,end,weight);
	//G->addEdge(end,src,weight);
	lineindex ++;
  }
  return G;
}

struct less_than_key
{
    inline bool operator() (const Edge* struct1, const Edge* struct2)
    {
        return (struct1->weight < struct2->weight);
    }
};

int  DoClustering(Graph *G){
  //sort the edges with weights
  UnionFind uf(501);// index in our UnionFind start with 0	
  sort(G->edgelist.begin(),G->edgelist.end(),less_than_key());
  for(int i =0; i< G->edgelist.size();i++){
	if(uf.clustersremaining == 5) // 0 will be always loner
	  break;
	Edge* edge = G->edgelist[i];
	if(uf.connected(edge->start->index,edge->end->index))
	  continue;
	else{
	  uf.DoUnion(edge->start->index,edge->end->index);
	}
  }
  int maxs =100000000;
  for(int i =0; i< G->edgelist.size();i++){
	Edge* edge = G->edgelist[i];
	if(uf.connected(edge->start->index,edge->end->index))
	  continue;
    else
      maxs = min(maxs,edge->weight);
  }
  return maxs;
  
}
main(){
  Graph* G;
  G = ReadTestFile("testGraph.txt");
#if 0
  for(int i =0 ;i < G->vertexlist.size(); i++){
	cout<< G->vertexlist[i]->index <<endl;
  }
  for(int i =0; i< G->vertexlist[1]->edgelist.size();i++){
	cout<< G->vertexlist[1]->edgelist[i]->weight << " " ;
  }
#endif
  cout << DoClustering(G) << endl;

  //uf.connected();
  //uf.DoUnion()
}
