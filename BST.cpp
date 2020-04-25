/*Note: you must create the BST.cpp file.  I'm only including a few 
Otherwise, as specified in the directions, you must write the BST.cpp.
including the method definitions to accompany the method declarations 
in BST.hpp
Partners: Nicholas Samulewicz, Geoff Bonnanzio, Chloe Griffiths
TA Name: Chunbo Song
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

bool BST::insert(string s){
/* Input: A string to be the phrase for the new node
 * Output: A boolean that's true if a new node was sucessfully inserted
 * Action: Find the correct spot for a new node with phrase S and insert it
 */
	TNode *tmp = root;
	TNode *holder =NULL;
	if (root!=NULL){ //case when the tree is not empty
		while (tmp!=NULL){//iterate through the array to find the spot for new node
			holder = tmp;
			if (s.compare(tmp->data->phrase) > 0){
				tmp=tmp->right;
			}
			else if (s.compare(tmp->data->phrase)<0){
				tmp=tmp->left;
			}
			else {//there is no spot for it because the phrase already is a node elsewhere
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
		setHeight(n); //reset heights starting with the node we just inserted
		return true;
	}
	else { //case when the tree is empty
		TNode *n = new TNode(s);
		root=n;
		setHeight(n); //rest the height of the node we just inserted
		return true;
	}

}

TNode *BST::find(string s){
/*Input: A string that represent the phrase we are looking for
 * Output: A pointer to the node that holds the same phrase as string s
 * Action: Go through the tree and find a spot with a specific node holding phrase S
 */
	TNode *tmp = root;
	while (s!=tmp->data->phrase){//iterate through the tree. Stop if we hit a node with phrase s
		if (s.compare(tmp->data->phrase)>0){ //s is greater than current node's phrase
			if (tmp->right==NULL){//if s phrase does not exist in the tree
				return NULL;
			}
			else {
				tmp=tmp->right;
			}
		}
		else { //s is less than current node's phrase
			if (tmp->left==NULL){//if s phrase does not exist in the tree
				return NULL;
			}
			else {
				tmp=tmp->left;
			}
		}

	}
	return tmp;
}

void BST::printTreeIO(TNode *n){
	/*Input: A pointer to a node to start with in the print
	 * Output: None
	 * Action: Goes through the tree in-order and prints each node
	 */
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
	/*Input: A pointer to a node to start with in the print
	 * Output: None
	 * Action: Goes through the tree pre-order and prints each node
	 */
	if (n==NULL){
		return;
	}
	else {
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

void BST::printTreePost(TNode *n){
	/*Input: A pointer to a node to start with in the print
     * Output: None
   	* Action: Goes through the tree post-order and prints each node
	 */
	if(n==NULL){
		return;
	}
	else{
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}
}

TNode *BST::remove(string s){
/*Input:
 * Output:
 * Action:
 */
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

TNode* BST::removeNoKids(TNode *tmp){
/*Input: A pointer to a node that holds no kids
 * Output: A pointer to the node we just deleted
 * Action: remove a node from the tree that has no kids
 */
	TNode *tmp2 = tmp->parent; //set as the parent of the one we are deleting

	//figure out which direction the node we are deleting sits on its parent
	if (tmp->parent->left==tmp){
		tmp->parent->left=NULL; //Then disconnect the node from the tree
	}
	else {
		tmp->parent->right=NULL; //Then disconnect the node from the tree
	}
	tmp->parent=NULL;
	setHeight(tmp2); ///reset heights starting with the parent of the node just deleted
	return tmp;
}


TNode* BST::removeOneKid(TNode *tmp, bool leftFlag){
/*Input: A pointer to the node we want to delete, a boolean flag telling whether the node's child is a left of a right
 * Output: A pointer to the node we just deleted
 * Action: Remove a node with one kid
 */
	TNode *tmp2 = tmp->parent;
	if (tmp->parent->left==tmp){ //if the node sits on the left of its parent
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
	else {//if the node sits on the right of it's parent
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

	setHeight(tmp2); //reset heights starting with the parent of the deleted
	return tmp;
}


void BST::setHeight(TNode *n){
/*Input:
 * Output: None
 * Action:
 */
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






