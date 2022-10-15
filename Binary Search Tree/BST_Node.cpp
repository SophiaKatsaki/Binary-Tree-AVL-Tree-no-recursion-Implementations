//
// Created by Ioannis Baraklilis - Sofia Katsaki on 4/13/2020.
//

#include "BST_Node.h"

///Constructors

BST_Node::BST_Node( std::string a_word ) {
	Data=a_word;
	timesAppeared=1;
	leftChild=nullptr;
	rightChild=nullptr;
}

BST_Node::BST_Node() {
	Data="";
	timesAppeared=1;
	leftChild=nullptr;
	rightChild=nullptr;
}

