//
// Created by Ioannis Baraklilis - Sofia Katsaki on 3/29/2020.
//

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <fstream>
#include <iostream>

#include "BST_Node.h"

class BinarySearchTree
{
public:
	//Constructor - Destructor
	BinarySearchTree();
	~BinarySearchTree();

	//Μέθοδοι
	bool insertNode(const std::string &a_word); // Δημιουργεί και εισάγει νεο κόμβο στην δομή αν δεν υπάρχει.
												// Διαφορετικά απλά αυξάνει τον δείκτη appeared του αντίστοιχου κόμβου. Αν η εισαγωγή πετύχει επιστρέφει true.

	bool deleteNode(const std::string &a_word); // Διαγράφει τον κόμβο με τιμή Data==a_word και επιστρέφει true. Επιστρέφει false αν δεν βρεθεί.

	const BST_Node* searchNode( const std::string &key); // Αναζητά τον κόμβο με τιμή Data==key και δείκτη σε αυτό ή nullptr σε περίπτωση που δεν βρεθεί.

	void inorder(std::ofstream &out) const; // Καλεί την internalPrintInorder με τιμή root για να τυπώσει τα στοιχεία της δομής στo ρεύμα εξόδου out με προδιατεταγμένη (inorder) διαπέραση.

	void preorder(std::ofstream &out) const; // Καλεί την internalPrintPreorder με τιμή root για να τυπώσει τα στοιχεία της δομής στo ρεύμα εξόδου out με ενδοδιατεταγμένη (preorder) διαπέραση.

	void postorder(std::ofstream &out) const; // Καλεί την internalPrintPostorder με τιμή root για να τυπώσει τα στοιχεία της δομής στo ρεύμα εξόδου out με μεταδιατεταγμένη (postorder) διαπέραση.

	int getNumberOfNodes() { return numOfNodes; }

private:
	///Μέλη δεδομένων
	BST_Node* root; // Δείκτης προς την ρίζα
	long numOfNodes; // Αριθμός κόμβων του δένδρου

	///Εσωτερικές συναρτήσεις της κλάσης (χρησιμοποιούνται για υποβοήθηση υλοποίησης των άλλων λειτουργιών που έχουν επαφή με τον χρήστη)

	//Βοηθητικές μέθοδοι για destructor (διαγραφή ολόκληρου δένδρου):
	void deleteTree( BST_Node *pt);

	//Βοηθητικές Μέθοδοι για διαπέραση:
	void internalPrintInorder( BST_Node *pt,std::ofstream &out) const; // Τυπώνει τα στοιχεία της δομής στo ρεύμα εξόδου out με προδιατεταγμένη (inorder) διαπέραση.
	void internalPrintPreorder( BST_Node *pt,std::ofstream &out) const; // Τυπώνει τα στοιχεία της δομής στo ρεύμα εξόδου out με ενδοδιατεταγμένη (preorder) διαπέραση.
	void internalPrintPostorder( BST_Node *pt,std::ofstream &out) const; // Τυπώνει τα στοιχεία της δομής στo ρεύμα εξόδου out με μεταδιατεταγμένη (postorder) διαπέραση.

	//Βοηθητικές Μέθοδοι για αναζήτηση:
	BST_Node** internalSearchNode( const std::string &a_word); // Αναζητά στην δομή κόμβο με τιμή Data==a_word και επιτρέφει δείκτη σε μέλος leftchild/rightchild που δείχνει στον κόμβο που αναζητείται

	//Βοηθητικές μέθοδοι για διαγραφή στοιχείου της δομής:
	void deleteNode_NoChildren( BST_Node **found);
	void deleteNode_OneChild( BST_Node **found);
	void deleteNode_TwoChildren( BST_Node **found);
};


#endif //BINARYSEARCHTREE_H
