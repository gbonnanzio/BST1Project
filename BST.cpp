/*Note: you must create the BST.cpp file.  I'm only including a few 
Otherwise, as specified in the directions, you must write the BST.cpp.
including the method definitions to accompany the method declarations 
in BST.hpp
*/
#include "BST.hpp"


BST::BST() {
	root = NULL;
}
BST::BST(string s){
	root = new TNode(s);
}

void BST::setHeight(TNode *n){
	if(n->parent != NULL){
		if(n == n->parent->right){
			if(n->parent->left->height <= n->height){
				n->parent->height++;
				setHeight(n->parent);
			}
		}
		else{
			if(n->parent->right->height <= n->height){
				n->parent->height++;
				setHeight(n->parent);
			}
		}
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

