//
// Created by Ioannis Baraklilis - Sofia Katsaki on 3/29/2020.
//

#include "BinarySearchTree.h"

///////////////		Public μέθοδοι		///////////////////////////////////////////////////////////////////////////////////////////////

BinarySearchTree::BinarySearchTree(){
	root = nullptr;
	numOfNodes = 0;
}

BinarySearchTree::~BinarySearchTree(){
	if (root)
		deleteTree(root);
}

bool BinarySearchTree::insertNode( const std::string &a_word ) {
	if (root== nullptr){ // Ελέγχω άν το δένδρο είναι κενό
		try {
			root = new BST_Node( a_word ); // Εισάγω νέο κόμβο (ρίζα) στο δένδρο
			numOfNodes++; // Αυξάνω τον μετρητή κόμβων
		}
		catch(...){ // Υπήρξε πρόβλημα στην δέσμευση μνήμης, επιστρέφω false
			return false;
		}
	}
	else {
		// Ψάχνω το a_word στο δένδρο. Η τιμή που θα επιστρέψει είναι δείκτης σε δείκτη που δείχνει στον κόμβο που περιέχει το a_word.
		//Διαφορετικά επιστρέφει δείκτη σε δείκτη που δείχνει σε κόμβο που θα περιείχε το a_word, αν αυτό υπήρχε ήδη.
		BST_Node **found = internalSearchNode( a_word );
		if ( *found ) {
			(*found)->timesAppeared++; // Υπάρχει ήδη, αυξάνω απλά μετρητή
		} else {
			try {
				(*found) = new BST_Node( a_word ); // Δεν υπάρχει, δημιουργώ και εισαγω καινούριο κόμβο.
				numOfNodes++; // Αυξάνω μετρητή στοιχείων δένδρου
			}
			catch ( ... ) { // Υπήρξε πρόβλημα στην δέσμευση μνήμης, επιστρέφω false
				return false;
			}
		}
	}
	return true; // Επιτυχία εισαγωγής, επιστρέφω true
}



bool BinarySearchTree::deleteNode( const std::string &a_word ) {
	if (root){ // Ελέγχω άν το δένδρο είναι άδειο
		BST_Node **found = internalSearchNode( a_word ); // Ψάχνω να βρώ άν υπάρχει στο δένδρο το στοιχείο που ζητείται να διαγραφεί
		if (*found){ // Υπάρχει το στοιχείο
			numOfNodes--;
			BST_Node &target = (**found); // Δίνω "ψευδώνυμο" στον κόμβο για πιο εύκολη και κατανοητή διαχείρηση
			//Περίπτωση που δεν έχει παιδιά
			if ( (target.leftChild == nullptr) && (target.rightChild == nullptr)){
				deleteNode_NoChildren(found);
				return true;
			}
			else{
				//Περίπτωση που έχει δύο παιδιά
				if ( target.leftChild && target.rightChild ) {
					deleteNode_TwoChildren( found );
					return true;
				} else {
					//Περίπτωση που έχει μόνο ένα παιδί
					deleteNode_OneChild(found);
					return true;
				}
			}
		}
	}
	return false;
}

const BST_Node* BinarySearchTree::searchNode( const std::string &key ){
	BST_Node* currentNode = root; // Ξεκινάω την αναζήτηση απο την ρίζα
	while (currentNode){ // Συνεχίζεται η αναζήτηση - δεν έχω φτάσει στο τέλος του δένδρου
		if (currentNode->Data > key){ // Ψάχνω σε αριστερό υποδένδρο
			currentNode = currentNode->leftChild;
		}
		else if(currentNode->Data < key){ // Ψάχνω στο δεξί υποδένδρο
			currentNode = currentNode->rightChild;
		}
		else{ // Βρήκα τον κόμβο που ψάχνω
			return currentNode;
		}
	}
	return nullptr; // Δεν βρέθηκε ο κόμβος

}


void BinarySearchTree::inorder(std::ofstream &out) const{
	internalPrintInorder(root,out);
}

void BinarySearchTree::preorder(std::ofstream &out) const{
	internalPrintPreorder(root,out);
}

void BinarySearchTree::postorder(std::ofstream &out) const{
	internalPrintPostorder(root,out);
}


///////////////		Private Μέθοδοι		///////////////////////////////////////////////////////////////////////////////////////////////

void BinarySearchTree::deleteTree( BST_Node *pt ) // Ίδια υλοποίση με την postorder παρακάτω με την διαφορά ότι διαγράφει τα στοιχεία του δενδρου.
{
	if (pt->leftChild) // Διαγράφω αριστερό παιδί, αν υπάρχει
		deleteTree(pt->leftChild);

	if (pt->rightChild) // Διαγράφω δεξί παιδί, αν υπάρχει
		deleteTree(pt->rightChild);

	delete pt; // Διαγράφω τον τρέχον κόμβο
}

void BinarySearchTree::internalPrintInorder( BST_Node *pt,std::ofstream &out) const{
	if (pt->leftChild)
		internalPrintInorder(pt->leftChild,out);

	out << "Word: " << pt->Data << ", appeared: " << pt->timesAppeared << " times" << std::endl;

	if (pt->rightChild)
		internalPrintInorder(pt->rightChild,out);
}

void BinarySearchTree::internalPrintPreorder( BST_Node *pt,std::ofstream &out) const{
	out << "Word: " << pt->Data << ", appeared: " << pt->timesAppeared << " times" << std::endl;

	if (pt->leftChild)
		internalPrintPreorder(pt->leftChild,out);

	if (pt->rightChild)
		internalPrintPreorder(pt->rightChild,out);
}

void BinarySearchTree::internalPrintPostorder( BST_Node *pt,std::ofstream &out) const{
	if (pt->leftChild)
		internalPrintPostorder(pt->leftChild,out);

	if (pt->rightChild)
		internalPrintPostorder(pt->rightChild,out);

	out << "Word: " << pt->Data << ", appeared: " << pt->timesAppeared << " times" << std::endl;
}

BST_Node **BinarySearchTree::internalSearchNode( const std::string &a_word )
{
	BST_Node *currentNode; // Δείκτης που αποθηκεύει την τιμή του τρέχοντος κόμβου και επιτρέπει την μετάβαση απο κόμβο σε κόμβο
	BST_Node **pointTo; /* Δείκτης που δείχνει στην αντίστοιχη μεταβλητή που αποθηκεύει την διεύθυνση του παιδιου (δείκτης σε παιδί) που έχει ως δεδομένα την τιμή που ψάχνουμε.
	 πχ. αν έχουμε τον κόμβο Χ με αριστερό παιδί το Υ και ψάχνουμε τον κόμβο Υ, στο τέλος ο δείκτης pointTo θα δείχνει στο X.leftChild (δηλαδή θα έχει τιμή &(X.leftChild))
	 (παρακάτω χρησιμοποιείται -> λόγω του ότι θα έχουμε πρόσβαση σε υποτιθέμενο Χ μέσω δείκτη*/
	currentNode = root; // Αρχίζω την αναζήτηση απο την ρίζα
	pointTo = &root; // Το pointTo δείχνει αρχικά στην μεταβλητή (ρίζα) που δείχνει στον πρώτο κόμβο του δένδρου
	while (currentNode){
		if (a_word > currentNode->Data){ // Αν η δοθείσα λέξη είναι λεξικογραφικά μεγαλύτερη απο την λέξη του τρέχων κόμβου, ψάχνω στο δεξί υποδένδρο.
			pointTo = &currentNode->rightChild; // Ενημέρωση για δεξί υποδένδρο
			currentNode = currentNode->rightChild;
		}
		else if(a_word < currentNode->Data){ // Αν η δοθείσα λέξη είναι λεξικογραφικά μικρότερη απο την λέξη του τρέχων κόμβου, ψάχνω στο αριστερό υποδένδρο.
			pointTo = &currentNode->leftChild; // Ενημέρωση για αριστερό υποδένδρο
			currentNode = currentNode->leftChild;
		}
		else{ // Η λέξη του κόμβου είναι ίση με την δοθείσα λέξη, βρήκα τον κόμβο που ψάχνω, επιστρέφω τον κατάλληλο δείκτη.
			return pointTo; // Επιστρέφω δείκτη σε μελός που δείχνει στο αντίστοιχο παιδί (δηλαδή επιστρέφω δείκτη σε δείκτη (μέλος γονέα) στο παιδί που είναι το αποτέλεσμα της αναζήτησης.
		}
	}
	return pointTo; // Το currentNode δείχνει σε nullptr, επιστρέφω δείκτη σε μελός που δείχνει στο αντίστοιχο nullptr.
}

void BinarySearchTree::deleteNode_NoChildren( BST_Node **found ) {
	delete *found; // Διαγράφω το παιδί
	*found= nullptr;
}

void BinarySearchTree::deleteNode_OneChild( BST_Node **found ) {
	BST_Node &target = (**found); // Δίνω "ψευδώνυμο" στον κόμβο για πιο εύκολη και κατανοητή διαχείρηση
	if (target.leftChild){ // Είναι αριστερό παιδί
		BST_Node *temp;
		temp = *found; // "Κρατάω" δείκτη στο "παλιό" παιδί
		*found = target.leftChild; // Αντικαθιστώ γονέα με παιδί
		delete temp; // Διαγράφω "παλιό" παιδί
	}
	else{ // Είναι δεξί παιδί
		BST_Node *temp;
		temp = *found; // "Κρατάω" δείκτη στο "παλιό" παιδί
		*found = target.rightChild; // Αντικαθιστώ γονέα με παιδί
		delete temp; // Διαγράφω "παλιό" παιδί
	}
}

void BinarySearchTree::deleteNode_TwoChildren( BST_Node **found ) {
	//Αναζήτηση μεγαλύτερου κόμβου του αριστερού υποδένδρου με όμοιο τρόπο με internalSearchNode
	BST_Node **pointTo;
	BST_Node *currentNode,*buffer;
	pointTo = &((*found)->leftChild); // Το pointTo δείχνει στην μεταβλητή (ρίζα) που δείχνει στον πρώτο κόμβο του δένδρου
	buffer = (*found)->leftChild; // Κρατάω τον προηγούμενο δείκτη απο αυτόν του currentNode ώστε να έχω το "τελευτάιο" currentNode πριν αυτό γίνει nullptr
	currentNode = (*found)->leftChild->rightChild; // Με αυτή την αρχική τιμή ξεκινάω αναζήτηση στο μεγαλύτερο στοιχείο του αριστερού υποδένδρου
	while (currentNode){ // Ψάχνω μέχρι το currentNode να γίνει nullptr όπου το buffer έχει το BST_Node** του οποίου το ** θα είναι ο μεγαλύτερος κόμβος του αριστερού υποδένδρου
		pointTo = &buffer->rightChild;
		buffer=buffer->rightChild;
		currentNode = currentNode->rightChild;
	}

	//Αντικατάσταση του κόμβου προς διαγραφή με τον κόμβο που βρέθηκε προηγουμένως
	(**found).Data = (**pointTo).Data;
	(**found).timesAppeared = (**pointTo).timesAppeared;

	//Διαγραφή του μεγαλύτερου κόμβου του αριστερού υποδένδρου
	if ((**pointTo).leftChild || (**pointTo).rightChild){ // Έχει ένα μόνο παιδί
		deleteNode_OneChild(pointTo);
	}
	else{ // Δεν έχει παιδιά
		deleteNode_NoChildren(pointTo);
	}
}





