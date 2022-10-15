//
// Created by Ioannis Baraklilis - Sofia Katsaki on 4/13/2020.
//

#ifndef PROJECT_DOMES_DEDOMENON_AVL_NODE_H
#define PROJECT_DOMES_DEDOMENON_AVL_NODE_H

#include <string>
#include <iostream>

class AVL_Node{ /// Αποθηκεύει τα δεδομένα του δένδρου και τα επόμενα στοιχεία του
public:
	//Constructors
	AVL_Node(std::string a_word);
	AVL_Node();

	std::string Data;  // Λέξη
	long timesAppeared; // Αριθμός επαναλήψεων της λέξης

	AVL_Node* leftChild; // Δείκτης προς αριστερό παιδί
	AVL_Node* rightChild; // Δείκτης προς δεξί παιδί

	long leftHeight; // Ύψος αριστερού υποδένδρου
	long rightHeight; // Ύψος δεξιού υποδένδρου

	//Method
	long getHeight(); // Επιστρέφει το ύψος του κόμβου

	//Ostream Operator
	friend std::ostream &operator<<(std::ostream &os, const AVL_Node &n){
		os << "Word: " << n.Data << ", appeared: " << n.timesAppeared << " times";
		return os;
	}
};


#endif //PROJECT_DOMES_DEDOMENON_AVL_NODE_H
