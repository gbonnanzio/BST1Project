/*
 * TNode.cpp
 *
 *  Created on: Apr 3, 2020
 *      Author: 13027
 */

#include <iostream>
#include <string>
#include "TNode.hpp"
using namespace std;

TNode::TNode(string s) {
	left = NULL;
	right = NULL;
	parent = NULL;
	height = 1;
	data = new Phrase(s);
	heightFlag = false;
}
TNode::TNode() {
	left = NULL;
	right = NULL;
	parent = NULL;
	height = 1;
	data = new Phrase();
	heightFlag = false;
}
TNode::~TNode(){
	cout <<"Deleting "<<data->phrase<<endl;
}
void TNode::printNode() {
	cout << data->phrase<<","<<height<<endl;
}
