//
// Created by John on 4/13/2020.
//

#ifndef PROJECT_DOMES_DEDOMENON_BST_NODE_H
#define PROJECT_DOMES_DEDOMENON_BST_NODE_H

#include <string>
#include <iostream>

class BST_Node{ /// Αποθηκεύει τα δεδομένα του δένδρου και τα επόμενα στοιχεία του
public:
	//Constructors
	BST_Node( std::string a_word);
	BST_Node();

	std::string Data;  // Λέξη
	long timesAppeared; // Αριθμός επαναλήψεων της λέξης

	BST_Node* leftChild; // Δείκτης προς αριστερό παιδί
	BST_Node* rightChild; // Δείκτης προς δεξί παιδί

	//Ostream Operator
	friend std::ostream &operator<<(std::ostream &os, const BST_Node &n){
		os << "Word: " << n.Data << ", appeared: " << n.timesAppeared << " times";
		return os;
	}
};


#endif //PROJECT_DOMES_DEDOMENON_BST_NODE_H
