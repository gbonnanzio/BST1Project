/*Note: you must create the BST.cpp file.  I'm only including a few 
Otherwise, as specified in the directions, you must write the BST.cpp.
including the method definitions to accompany the method declarations 
in BST.hpp
*/
#include "BST.hpp"
#include <math.h>

BST::BST() {
	root = NULL;
}
BST::BST(string s){
	root = new TNode(s);
}





void printTreePost(TNode *n){
	if(n==NULL){
		return;
	}
	else{
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}
}


TNode *removeNoKids(TNode *tmp){
	if(tmp = tmp->parent->right){
		tmp->parent->right = NULL;
	}
	else{
		tmp->parent->left = NULL;
	}
	setHeight(tmp);

}





void BST::setHeight(TNode *n){
	if(n == NULL){
		return;
	}
	if(n->left==NULL && n->right==NULL){
		n->height = 1;
		n->heightFlag = true;
		setHeight(n->parent);
	}
	else if(n->left == NULL && n->right->heightFlag){
		n->height = n->right->height + 1;
		n->heightFlag = true;
		setHeight(n->parent);
	}
	else if(n->right == NULL && n->left->heightFlag){
		n->height = n->left->height + 1;
		n->heightFlag = true;
		setHeight(n->parent);
	}
	else if(n->left->heightFlag && n->right->heightFlag){
		if(n->left->height > n->right->height){
			n->height = n->left->height + 1;
		}
		else{
			n->height = n->right->height + 1;
		}
		n->heightFlag = true;
		setHeight(n->parent);
	}
	else if(!n->left->heightFlag){
		setHeight(n->left);
	}
	else if(!n->right->heightFlag){
		setHeight(n->right);
	}
}












TNode *BST::find(string s){
	if(s == root->data->phrase){
		return root;
	}
	else if(s > root->data->phrase){
		root = root->right;
		find(s);
	}
	else if(s < root->data->phrase){
		root = root->left;
		find(s);
	}
	else if(root == NULL){
		return NULL;
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
	if(test == NULL){
		cout << "This string is not in the tree." << endl;
		return s;
	}
	if(test->right == NULL && test->left == NULL){

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
		printTreeIO(n->left);
		printTreeIO(n->right);
	}
}






bool BST::insert(string s){
	TNode *tmp = root;
	if (root!=NULL){
		while (tmp->left!=NULL && tmp->right!=NULL){
			//go through and find the spot
			if (s.compare(tmp->data->phrase) < 0){
				tmp=tmp->right;
			}
			else if (s.compare(tmp->data->phrase)>0){
				tmp=tmp->left;
			}
			else {
				return false;
			}
		}
		TNode *n = new TNode(s);
		n->data->phrase=s;
		n->parent=tmp;
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

