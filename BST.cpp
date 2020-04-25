/*Note: you must create the BST.cpp file.  I'm only including a few 
Otherwise, as specified in the directions, you must write the BST.cpp.
including the method definitions to accompany the method declarations 
in BST.hpp
Partners: Nicholas Samulewicz, Geoff Bonnanzio, Chloe Griffiths
*/
#include "BST.hpp"
#include <math.h>
#include <cstdbool>
using namespace std;

BST::BST() {
	root = NULL;
}
BST::BST(string s){
	root = new TNode(s);
}


void BST::printTreePost(TNode *n){
	if(n==NULL){
		return;
	}
	else{
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}
}


void BST::setHeight(TNode *n){
	if(n == NULL){
		return;
	}
	else if(n->left==NULL && n->right==NULL && n->parent == NULL){
		n->height = 1;
		setHeight(n->parent);
	}
	else if(n->left==NULL && n->right==NULL){
			n->height = 1;
			setHeight(n->parent);
	}
	else if(n->left == NULL){
		n->height = n->right->height + 1;
		setHeight(n->parent);
	}
	else if(n->right == NULL){
		n->height = n->left->height + 1;
		setHeight(n->parent);
	}
	else{
		if(n->left->height > n->right->height){
			n->height = n->left->height + 1;
		}
		else{
			n->height = n->right->height + 1;
		}
		setHeight(n->parent);
	}
}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}


void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}

void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);

	}
}


TNode *BST::remove(string s){
	TNode *test = find(s);
	TNode *removed = new TNode();
	TNode *replace = new TNode();
	if(test == NULL){
		cout << "This string is not in the tree." << endl;
		return test;
	}
	if(test->right == NULL && test->left == NULL){
		removed = removeNoKids(test);
		return removed;
	}
	else if(test->right == NULL && test->left){
		removed = removeOneKid(test, 1);
		return removed;
	}
	else if(test->left == NULL && test->right){
		removed = removeOneKid(test, 0);
		return removed;
	}
	else{
		cout << "test d" << endl;
		//remove two kids
		replace = test->left;
		while(replace->right !=NULL){
			replace = replace->right;
		}
		TNode *tmp = replace;
		 tmp->right = tmp->parent->right;
		cout << "test b" << endl;
		TNode *tmp2 = tmp->parent;
		if(tmp->left != NULL){
			tmp->left->parent = tmp2;
		}
		tmp->right = test->right;
		if(test->left == tmp){

			tmp->parent = test->parent;
		}
		else{
			test->left->parent = tmp;
		}
		test->right->parent = tmp;
		tmp->parent = test->parent;

		if(test->parent == NULL){
			root = tmp;
			setHeight(tmp);
			return test;
		}
		else if(test->parent->right == test){
			test->parent->right = replace;
			test->right = NULL;
			test->parent = NULL;
			test->left = NULL;
			setHeight(tmp->parent);
			return test;
		}
		else{
			test->parent->left = replace;
			test->right = NULL;
			test->parent = NULL;
			test->left = NULL;
			setHeight(tmp->parent);
			return test;
		}
	}
}

void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}

void BST::printTreeIO(TNode *n){
	if (n==NULL){
		return;
	}
	else {
		printTreeIO(n->left);
		n->printNode();
		printTreeIO(n->right);
	}
}
void BST::printTreePre(TNode *n){
	if (n==NULL){
		return;
	}
	else {
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

TNode* BST::removeNoKids(TNode *tmp){
	//no kids means we just need to disconnect it
	TNode *tmp2 = tmp->parent;
	if (tmp->parent->left==tmp){
		tmp->parent->left=NULL;
	}
	else {
		tmp->parent->right=NULL;
	}
	tmp->parent=NULL;
	setHeight(tmp2);
	return tmp;
}

TNode* BST::removeOneKid(TNode *tmp, bool leftFlag){
	//we need to figure out if the tmp is on the left or the right of it's parent
	TNode *tmp2 = tmp->parent;
	if (tmp->parent->left==tmp){

		//reassign the child to the parent of the node
		if (leftFlag){//left child present
			tmp->left->parent=tmp->parent;
			tmp->parent->left=tmp->left;
		}
		else {//right child present
			tmp->right->parent=tmp->parent;
			tmp->parent->left=tmp->right;
		}
	}
	else {

		//reassign the child to the parent of the node
		if (leftFlag){//left child present
			tmp->left->parent=tmp->parent;
			tmp->parent->right=tmp->left;
		}
		else {//right child present
			tmp->right->parent=tmp->parent;
			tmp->parent->right=tmp->right;
	}

	}

	//remove the node by disconnecting it
	tmp->parent=NULL;
	tmp->left=NULL;
	tmp->right=NULL;

	setHeight(tmp2);
	return tmp;
}

TNode *BST::find(string s){
	TNode *tmp = root;
	while (s!=tmp->data->phrase){
		//move along to the next one
		//but if you hit the end of the line
		//the string does not exist
		if (s.compare(tmp->data->phrase)>0){
			if (tmp->right==NULL){
				return NULL;
			}
			else {
				tmp=tmp->right;
			}
		}
		else {
			if (tmp->left==NULL){
				return NULL;
			}
			else {
				tmp=tmp->left;
			}
		}

	}
	return tmp;
}


bool BST::insert(string s){
	TNode *tmp = root;
	TNode *holder =NULL;
	if (root!=NULL){
		while (tmp!=NULL){
			holder = tmp;
			//go through and find the spot
			if (s.compare(tmp->data->phrase) > 0){
				tmp=tmp->right;
			}
			else if (s.compare(tmp->data->phrase)<0){
				tmp=tmp->left;
			}
			else {
				return false;
			}
		}
		TNode *n = new TNode(s);
		n->parent=holder;
		if (s.compare(holder->data->phrase) > 0){
			holder->right=n;
		}
		else {
			holder->left=n;
		}
		setHeight(n);
		return true;
	}
	else {
		TNode *n = new TNode(s);
		root=n;
		setHeight(n);
		return true;
	}

}

