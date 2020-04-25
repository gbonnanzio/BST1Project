/*Note: you must create the BST.cpp file.  I'm only including a few 
Otherwise, as specified in the directions, you must write the BST.cpp.
including the method definitions to accompany the method declarations 
in BST.hpp
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


/*TNode *BST::removeNoKids(TNode *tmp){
	if(tmp = tmp->parent->right){
		tmp->parent->right = NULL;
	}
	else{
		tmp->parent->left = NULL;
	}
	setHeight(tmp);

}*/





void BST::setHeight(TNode *n){
	if(n == NULL){
		return;
	}

	else if(n->left==NULL && n->right==NULL && n->parent == NULL){
		//cout << "test 1" <<endl;
		n->height = 1;
		n->heightFlag = true;
		cout << "test 8" <<endl;
		setFlags(root);
		setHeight(n->parent);
	}
	else if(n->left==NULL && n->right==NULL){
			//cout << "test 1" <<endl;
			n->height = 1;
			n->heightFlag = true;
			setHeight(n->parent);
	}
	else if(n->left == NULL && !n->right->heightFlag){
		//cout << "test 2" <<endl;
		n->height = n->right->height + 1;
		n->heightFlag = true;
		setHeight(n->parent);
	}
	else if(n->right == NULL && !n->left->heightFlag){
		//cout << "test 3" <<endl;
		n->height = n->left->height + 1;
		n->heightFlag = true;
		setHeight(n->parent);
	}
	else if(n->left->heightFlag && n->right->heightFlag){
		//cout << "test 4" <<endl;
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
		//cout << "test 5" <<endl;
		setHeight(n->left);
	}
	else if(!n->right->heightFlag){
		//cout << "test 6" <<endl;
		setHeight(n->right);
	}
	else{
		cout << "test 7" <<endl;
		setFlags(root);
	}
}

void BST::setFlags(TNode *n){
	if(n==NULL){
		return;
	}
	n->heightFlag = false;
	setFlags(n->left);
	setFlags(n->right);
}











//TNode *BST::find(string s){
//	if(s == root->data->phrase){
//		return root;
//	}
//	else if(s > root->data->phrase){
//		root = root->right;
//		find(s);
//	}
//	else if(s < root->data->phrase){
//		root = root->left;
//		find(s);
//	}
//	else if(root == NULL){
//		return NULL;
//	}
//}











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
		//remove two kids
		replace = test->right;
		while(replace->left !=NULL){
			replace = replace->left;
		}
		TNode *tmp = replace;
		cout << "test b" << endl;
		tmp->parent->left = tmp->right;
		cout << "test b" << endl;
		TNode *tmp2 = tmp->parent;
		if(tmp->right != NULL){
			tmp->right->parent = tmp2;
		}
		tmp->right = test->right;
		cout << "test b" << endl;
		tmp->left = test->left;
		test->right->parent = tmp;
		test->left->parent = tmp;
		tmp->parent = test->parent;

		if(test->parent->right == test){
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






/*bool BST::insert(string s){
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

}*/







/*bool BST::insert(string s){
	TNode *tmp = new TNode(s);
	cout << "test c" <<  endl;
	if(root->data->phrase != ""){
		cout << "test b" << endl;
		if(s >= root->data->phrase){
			if(root->right == NULL){
				root->right=tmp;
				return true;
			}
			root = root->right;
			insert(s);
		}
		else{
			if(root->left == NULL){
				root->right=tmp;
				root->left=tmp;
				return true;
			}
			root = root->left;
			insert(s);
		}
	}

	else{
		cout << "test d" << endl;
		cout << root << endl;
		root = tmp;
		cout << "test e" << endl;
		cout << root->data->phrase << endl;
		return true;
	}
}*/








TNode* BST::removeNoKids(TNode *tmp){
	//no kids means we just need to disconnect it
	TNode *tmp2;
	if (tmp->parent->left==tmp){
		tmp->parent->left=NULL;
	}
	else {
		tmp->parent->right=NULL;
	}
	tmp->parent=NULL;
	return tmp;
}






TNode* BST::removeOneKid(TNode *tmp, bool leftFlag){
	//we need to figure out if the tmp is on the left or the right of it's parent
	TNode *tmp2;
	if (tmp->parent->left==tmp){
		//tmp on parent's left
		tmp2 = tmp->parent->left;
	}
	else {
		//tmp on it's parents right
		tmp2 = tmp->parent->right;
	}

	//reassign the child to the parent of the node
	if (leftFlag){//left child present
		tmp->left->parent=tmp->parent;
		tmp2=tmp->left;
	}
	else {//right child present
		tmp->right->parent=tmp->parent;
		tmp2=tmp->right;
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
		setHeight(root);
		return true;
	}
	else {
		TNode *n = new TNode(s);
		root=n;
		setHeight(n);
		return true;
	}

}





