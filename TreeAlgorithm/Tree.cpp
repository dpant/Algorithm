/*
Big picture:: 
	implement a Tree for building a BST.
	Print a BST;
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

class TreeNode{
  TreeNode *left;
  TreeNode *right;
  int data;
public:
  TreeNode*  & Left(){
	return left;
  }
  TreeNode * &Right(){
	return right;
  }	
  static TreeNode * MkNode(int ndata){
   TreeNode *tn = new TreeNode();
   tn->data = ndata;
   tn->right = NULL;
   tn->left = NULL;
   return tn;
  }
  int TreeNodeData(){
	return data;
  }
};
class Tree{
  TreeNode *rootNode;
public:
  TreeNode* AddNode(TreeNode *parent,TreeNode *lChild, TreeNode *rChild){
	parent->Left() = lChild; /* need a referece to a TreeNode* to  make this work */
	parent->Right() = rChild; /* need a referece to a TreeNode* to  make this work */
	return parent;
  }
  TreeNode * GetRootNode(){
	return rootNode;
  }
  void SetRootNode(TreeNode *tn){
	rootNode = tn;
  }
  TreeNode * BuildBST(){/* create a test binary serch tree */
	TreeNode * n1 = TreeNode::MkNode(20);
	SetRootNode(n1);

	TreeNode * n2 = TreeNode::MkNode(10);
	TreeNode *n3 = AddNode(TreeNode::MkNode(11),NULL,AddNode(TreeNode::MkNode(12),NULL,AddNode(TreeNode::MkNode(13),NULL,AddNode(TreeNode::MkNode(15),TreeNode::MkNode(14),NULL))));
    TreeNode *n4 = AddNode(TreeNode::MkNode(5),TreeNode::MkNode(4),TreeNode::MkNode(6));
	AddNode(n2,n4,n3);
	
	n3 = AddNode(TreeNode::MkNode(25),TreeNode::MkNode(23),AddNode(TreeNode::MkNode(28),NULL,AddNode(TreeNode::MkNode(30),TreeNode::MkNode(29),NULL)));
    AddNode(rootNode,n2,n3);
	return rootNode;
  }
  TreeNode * FindTreeNodeR(TreeNode * &tnp, int Data){
	TreeNode *foundnp =NULL;
	if(tnp->Left())
	  foundnp = FindTreeNodeR(tnp->Left(),Data);
	if(!foundnp && tnp->TreeNodeData() == Data){
 	  return tnp;
	}
	if(!foundnp && tnp->Right())
	  foundnp = FindTreeNodeR(tnp->Right(),Data);
	return foundnp;
  }
  TreeNode * FindTreeNode(int Data){ /* Searches all nodes in a tree -- not optimized for BST */
	TreeNode *found = FindTreeNodeR(rootNode,Data);
	if(!found){
	  cout << "Node with Data:" << Data << "  Not Found" <<endl;
	}else{
	  cout<< "Found Node :" << Data  << "   " << found << endl;;
	}
	return found;
  }
  void TraverseInOrderAndPrintR(TreeNode * &tnp){
	if(tnp->Left())
		TraverseInOrderAndPrintR(tnp->Left());
	cout<< tnp->TreeNodeData() << "    ";
	if(tnp->Right())
		TraverseInOrderAndPrintR(tnp->Right());
  }
  void TraversePreOrderAndPrintR(TreeNode * &tnp){
	cout<< tnp->TreeNodeData() << "    ";
	if(tnp->Left())
		TraversePreOrderAndPrintR(tnp->Left());
	if(tnp->Right())
		TraversePreOrderAndPrintR(tnp->Right());
  }
  void TraversePostOrderAndPrintR(TreeNode * &tnp){
	if(tnp->Left())
		TraversePostOrderAndPrintR(tnp->Left());
	if(tnp->Right())
		TraversePostOrderAndPrintR(tnp->Right());
	cout<< tnp->TreeNodeData() << "    ";
  }

  void TraverseInOrderAndPrint(){
	cout<< "In order Traversal" <<endl;
	TraverseInOrderAndPrintR(rootNode);
	cout<<endl;
  }
  void TraversePreOrderAndPrint(){
	cout << "Pre order Traversal" <<endl;
	TraversePreOrderAndPrintR(rootNode);
	cout<<endl;
  }
  void TraversePostOrderAndPrint(){
	cout << "Post order Traversal" <<endl;
	TraversePostOrderAndPrintR(rootNode);
	cout<<endl;
  }

  /* 
	Idea is simple 
		return p if tree (rooted at rnode) only contain p
		return q if tree (rooted at rnode) only contains q
		return different node (LCA) if you found one

 */
  TreeNode*   LCAR(TreeNode* rnode,TreeNode *p,TreeNode* q){
	TreeNode* left = NULL ,*right = NULL;
	if( rnode->Left() == NULL &&  rnode->Right() == NULL){
	  if(rnode == p || rnode == q){
		return rnode == p ? p : q;
	  }else{
		return NULL;
	  }
	}
	left = rnode->Left() ? LCAR(rnode->Left(),p,q) : NULL;
	if(left != p && left != q && left != NULL) /* found LCA in left subtree return */
	  return left; /* found it - return and don't recurse to other side */

	right = rnode->Right() ? LCAR(rnode->Right(),p,q) : NULL;
	if(right != p && right != q && right != NULL) /* found LCA in right subtree return */
	  return right; /* found it - return and don't recurse to other side*/
	
	if(( left && right) && ((left == p && right == q) ||( left == q && right == p))) /* one node in left tree other in right tree return this node  as LCA*/
	  return rnode;
	else if(((left && (left == p)) || (right && (right  == p)))) /* either p or q is in the left tree, return the one */
	  return p;
	else if(((left && (left == q)) || (right && (right  == q))))  /* either p or q is in the right tree return the one */
	  return q;
	else 
	 return NULL;
  }
 TreeNode*  LeastCommonAncestor(TreeNode *p,TreeNode* q){
	TreeNode* lca =  LCAR(rootNode,p,q);
	if(!lca || lca == p || lca == q){
	  cout<< "Error: No common ancestor found. Are both nodes in the Tree?" <<endl;
	}else{
	  cout<< "LCA node is : " << lca << "    " << lca->TreeNodeData()<< endl;
	}
	return lca;
  }	

};
void test(){
  Tree *tp = new Tree();
  tp->BuildBST();
  cout<<"BST build successfull" <<endl;
  tp->TraverseInOrderAndPrint();
  tp->TraversePreOrderAndPrint();
  tp->TraversePostOrderAndPrint();
  tp->LeastCommonAncestor(tp->FindTreeNode(4),tp->FindTreeNode(141));
	
}

int main(){
  test();
  return true;
}

