//
// Created by Ioannis Baraklilis - Sofia Katsaki on 4/12/2020.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <iostream>
#include <fstream>

#include "AVL_Node.h"

class AVL_Tree {
public:
	///Constructor - Destructor
	AVL_Tree();
	~AVL_Tree();

	///Μέθοδοι
	int getheight() { return height; }
	bool insertNode(const std::string &a_word); // Δημιουργεί και εισάγει νεο κόμβο στην δομή αν δεν υπάρχει.
	// Διαφορετικά απλά αυξάνει τον δείκτη appeared του αντίστοιχου κόμβου. Αν η εισαγωγή πετύχει επιστρέφει true.

	bool deleteNode(const std::string &a_word); // Διαγράφει τον κόμβο με τιμή Data==a_word και επιστρέφει true. Επιστρέφει false αν δεν βρεθεί.

	const AVL_Node* searchNode(const std::string &key); // Αναζητά τον κόμβο με τιμή Data==key και δείκτη σε αυτό ή nullptr σε περίπτωση που δεν βρεθεί.
	// Διαφορετικά επιτρέφει ένα αντικείμενο AVL_Node με κενά όλα τα μέλη.

	void inorder(std::ofstream &out) const; // Καλεί την internalPrintInorder με τιμή root για να τυπώσει τα στοιχεία της δομής στo ρεύμα εξόδου out με προδιατεταγμένη (inorder) διαπέραση.

	void preorder(std::ofstream &out) const; // Καλεί την internalPrintPreorder με τιμή root για να τυπώσει τα στοιχεία της δομής στo ρεύμα εξόδου out με ενδοδιατεταγμένη (preorder) διαπέραση.

	void postorder(std::ofstream &out) const; // Καλεί την internalPrintPostorder με τιμή root για να τυπώσει τα στοιχεία της δομής στo ρεύμα εξόδου out με μεταδιατεταγμένη (postorder) διαπέραση.

	int getNumberOfNodes() { return numOfNodes; }


private:
	///Μέλη δεδομένων
	AVL_Node* root; // Δείκτης προς την ρίζα
	long numOfNodes; // Αριθμός κόμβων του δένδρου
	long height; // Ύψος του δένδρου

	///Εσωτερικές συναρτήσεις της κλάσης (χρησιμοποιούνται για υποβοήθηση υλοποίησης των άλλων λειτουργιών που έχουν επαφή με τον χρήστη)

	//Βοηθητικές μέθοδοι για destructor (διαγραφή ολόκληρου δένδρου):
	void deleteTree(AVL_Node *pt);

	//Βοηθητικές Μέθοδοι για διαπέραση:
	void internalPrintInorder(AVL_Node *pt, std::ofstream &out) const; // Τυπώνει τα στοιχεία της δομής στo ρεύμα εξόδου out με προδιατεταγμένη (inorder) διαπέραση.
	void internalPrintPreorder(AVL_Node *pt, std::ofstream &out) const; // Τυπώνει τα στοιχεία της δομής στo ρεύμα εξόδου out με ενδοδιατεταγμένη (preorder) διαπέραση.
	void internalPrintPostorder(AVL_Node *pt, std::ofstream &out) const; // Τυπώνει τα στοιχεία της δομής στo ρεύμα εξόδου out με μεταδιατεταγμένη (postorder) διαπέραση.

	//Βοηθητικές Μέθοδοι για διαχείριση δένδρου AVL
	void updateTree_Insert( AVL_Node** routeStack, int top ); // Ενημερώνει (αυξάνει) τις μεταβλητές ύψους και κάνει περιστροφές, εφόσον χρειαστεί.
	void updateTree_Delete( AVL_Node** routeStack, int top ); // Ενημερώνει (μειώνει) τις μεταβλητές ύψους και κάνει περιστροφές, εφόσον χρειαστεί.
	void leftRotation( AVL_Node* targetNode, AVL_Node** parentPtr ); // Κάνει μία αριστερή περιστροφή στο παιδί στο οποίο εμφανίζεται πρόβλημα
	void rightRotation( AVL_Node* targetNode, AVL_Node** parentPtr ); // Κάνει μία αριστερή περιστροφή στο παιδί στο οποίο εμφανίζεται πρόβλημα

	//Βοηθητικές Μέθοδοι για αναζήτηση:
	AVL_Node** internalSearchNode_WithStack(const std::string &a_word, AVL_Node** &stackOfSerches, int &top); // Όμοια λειτουργία με την internalSearchNode, με εξαίρεση ότι εκτός της αναζήτης δημιουργεί και ένα array δεικτών προς τα Nodes απο τα οποία "έχω περάσει"

	//Βοηθητικές μέθοδοι για διαγραφή στοιχείου της δομής:
	void deleteNode_NoChildren(AVL_Node **targetPtrPtr, AVL_Node** &routeStack, int& top);
	void deleteNode_OneChild(AVL_Node **targetPtrPtr, AVL_Node** &routeStack, int& top);
	void deleteNode_TwoChildren(AVL_Node **targetPtrPtr , AVL_Node** &routeStack, int &top);
};


#endif //AVL_TREE_H
