//
// Created by Ioannis Baraklilis - Sofia Katsaki on 4/13/2020.
//

#include "AVL_Node.h"

AVL_Node::AVL_Node( std::string a_word ) {
	Data=a_word;
	timesAppeared=1;
	leftChild=nullptr;
	rightChild=nullptr;
	leftHeight=0;
	rightHeight=0;
}

AVL_Node::AVL_Node() {
	Data="";
	timesAppeared=1;
	leftChild=nullptr;
	rightChild=nullptr;
	leftHeight=0;
	rightHeight=0;
}

long AVL_Node::getHeight() { // Το ύψος κάθε κόμβου μεγαλύτερο απο τα αποθηκευμένα ύψη απο τα δύο παιδιά.
	if (leftHeight>rightHeight){
		return leftHeight;
	}
	else{
		return rightHeight;
	}
}