//
// Created by Ioannis Baraklilis - Sofia Katsaki on 4/12/2020.
//

#include "AVL_Tree.h"

///////////////		Public μέθοδοι		///////////////////////////////////////////////////////////////////////////////////////////////

AVL_Tree::AVL_Tree(){
	root = nullptr;
	numOfNodes = 0;
	height=0;
}

AVL_Tree::~AVL_Tree(){
	if (root)
		deleteTree(root);
}

bool AVL_Tree::insertNode( const std::string &a_word ) {
	if (root== nullptr){ // Κενό δένδρο
		try {
			root = new AVL_Node( a_word ); // Προσθέτω ρίζα
			numOfNodes++;
		}
		catch(...){
			return false;
		}
	}
	else {
		AVL_Node** routeStack; // Στοίβα δεικτών μονοπατιού
		int top;
		try {
			routeStack = new AVL_Node *[height + 2]; // Πλήθος στοιχείων: πλήθος επιπέδων (ύψος δένδρου + 1) + 1 νέο στοιχείο
		}
		catch(...){
			return false;
		}
		AVL_Node **targetPtrPtr = internalSearchNode_WithStack( a_word, routeStack, top); // Ψάχνω αν υπάρχει - Που θα "ήταν" αν υπήρχε
		if ( *targetPtrPtr ) { // Υπάρχει
			(*targetPtrPtr)->timesAppeared++;
		} else { // Δεν υπάρχει - πρέπει να προσθέσω νέο κόμβο
			try {
				(*targetPtrPtr) = new AVL_Node( a_word ); // Προσθέτω νέο κόμβο στην θέση που "θα έπρεπε να είναι" άν υπήρχε
				numOfNodes++;
				routeStack[top]=(*targetPtrPtr); // Ενημερώνω την στοίβα
				updateTree_Insert(routeStack, top); // Καλώ ενημέρωση των υψών - Εξισορόπηση Δένδρου
				height = root->getHeight(); // Ενημερώνω το ύψος του δένδρου μετα την εισαγωγή
				}
			catch ( ... ) {
				delete [] routeStack;
				return false;
			}
		}
		delete [] routeStack;
	}
	return true;
}



bool AVL_Tree::deleteNode( const std::string &a_word ) {
	if (root){
		int top;
		AVL_Node **routeStack = new AVL_Node *[height + 2]; // Πλήθος στοιχείων: πλήθος επιπέδων (ύψος δένδρου + 1) + 1
		AVL_Node **targetPtrPtr = internalSearchNode_WithStack( a_word, routeStack, top );
		if (*targetPtrPtr){
			numOfNodes--;
			AVL_Node &target = (**targetPtrPtr); // Δίνω "ψευδώνυμο" στον κόμβο για πιο εύκολη και κατανοητή διαχείρηση
			//Περίπτωση που δεν έχει παιδιά
			if ( (target.leftChild == nullptr) && (target.rightChild == nullptr)){
				deleteNode_NoChildren(targetPtrPtr,routeStack, top); // Διαγράφω τον κόμβο που χρειάζεται
				updateTree_Delete(routeStack, top ); // Καλώ ενημέρωση των υψών - Εξισορόπηση Δένδρου
				delete [] routeStack;
				return true;
			}
			else{
				//Περίπτωση που έχει δύο παιδιά
				if ( target.leftChild && target.rightChild ) {
					deleteNode_TwoChildren( targetPtrPtr , routeStack, top); // Διαγράφω τον κόμβο που χρειάζεται
					updateTree_Delete(routeStack, top); //Καλώ ενημέρωση των υψών - Εξισορόπηση Δένδρου
					delete [] routeStack;
					return true;
				} else {
					//Περίπτωση που έχει μόνο ένα παιδί
					deleteNode_OneChild(targetPtrPtr, routeStack, top); // Διαγράφω τον κόμβο που χρειάζεται
					updateTree_Delete(routeStack, top ); //Καλώ ενημέρωση των υψών - Εξισορόπηση Δένδρου
					delete [] routeStack;
					return true;
				}
			}
		}
	}
	return false;
}

const AVL_Node* AVL_Tree::searchNode( const std::string &key ){
	AVL_Node* currentNode = root;
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


void AVL_Tree::inorder(std::ofstream &out) const{
	internalPrintInorder(root, out);
}

void AVL_Tree::preorder(std::ofstream &out) const{
	internalPrintPreorder(root,out);
}

void AVL_Tree::postorder(std::ofstream &out) const{
	internalPrintPostorder(root,out);
}

///////////////		Private Μέθοδοι		///////////////////////////////////////////////////////////////////////////////////////////////

void AVL_Tree::deleteTree( AVL_Node *pt ) // Ίδια υλοποίση με την postorder παρακάτω με την διαφορά ότι διαγράφει τα στοιχεία του δενδρου.
{
	if (pt->leftChild)
		deleteTree(pt->leftChild);

	if (pt->rightChild)
		deleteTree(pt->rightChild);

	delete pt;
}

void AVL_Tree::internalPrintInorder(AVL_Node *pt, std::ofstream &out) const{
	if (pt->leftChild)
		internalPrintInorder(pt->leftChild, out);

	out << "Word: " << pt->Data << ", appeared: " << pt->timesAppeared << " times" << std::endl;

	if (pt->rightChild)
		internalPrintInorder(pt->rightChild, out);
}

void AVL_Tree::internalPrintPreorder(AVL_Node *pt, std::ofstream &out) const{
	out << "Word: " << pt->Data << ", appeared: " << pt->timesAppeared << " times" << std::endl;

	if (pt->leftChild)
		internalPrintPreorder(pt->leftChild, out);

	if (pt->rightChild)
		internalPrintPreorder(pt->rightChild, out);
}

void AVL_Tree::internalPrintPostorder(AVL_Node *pt, std::ofstream &out) const{
	if (pt->leftChild)
		internalPrintPostorder(pt->leftChild, out);

	if (pt->rightChild)
		internalPrintPostorder(pt->rightChild, out);

	out << "Word: " << pt->Data << ", appeared: " << pt->timesAppeared << " times" << std::endl;
}

void AVL_Tree::updateTree_Insert( AVL_Node **routeStack, int top ) {
	int i;
	for ( i = top - 1; i >= 0; i-- ) { // top-1 γιατί στο top έχω το νέο στοιχείο που δεν χρειάζεται ενημέρωση
		//Ελέγχω για το ποιόν μετρητή ύψους να αυξήσω: αν το παιδί (επόμενο στοιχείο στην στοίβα) είναι το δεξί παιδί, τότε η μεταβολή στο ύψος είναι στα δεξιά.
		if ( routeStack[i]->rightChild == routeStack[i + 1] ) {
			// Ο τρέχον κόμβος της πορείας της αναζήτησης είναι αριστερό παιδί του προηγούμενου (πρέπει να κάνω ελέγχους και μεταβολές για αριστερό παιδί του γονέα)
			routeStack[i]->rightHeight++; //Αυξάνω τον μετρητή ύψους του δεξιού παιδιού
			if ( routeStack[i]->rightHeight - 1 > routeStack[i]->leftHeight ) { //Ελέγχω αν υπάρχει πρόβλημα
				if ( routeStack[i]->rightChild->rightHeight > routeStack[i]->rightChild->leftHeight ) {  // Περίπτωση Δεξιά-Δεξιά (right-right)
					if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα"
						leftRotation( routeStack[i], &root );
						return; // Μετά απο περιστροφή, το δένδρο είναι AVL.
					} else {
						AVL_Node** targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild);
						//Δίνω στο rotation τον δείκτη του γονέα προς τον κόμβο με πρόβλημα ("στόχος"): Αν ο "στόχος" είναι δεξί παιδί του γονέα τότε το targetsParent θα δείχνει στο μέλος του κόμβου που είναι δείκτης προς αριστερό παιδί. Ανάλογα αν ο "στόχος" είναι δεξί παιδι
						leftRotation( routeStack[i], targetPtrPtr);
						return; // Μετά απο περιστροφή, το δένδρο είναι AVL.
					}
				} else { // Περίπτωση Δεξιά-Αριστερά (right-left)
					if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα"
						rightRotation( routeStack[i]->rightChild, &(routeStack[i]->rightChild));
						leftRotation( routeStack[i], &root );
						return; // Μετά απο περιστροφές, το δένδρο είναι AVL.
					} else {
						AVL_Node** targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild);
						rightRotation( routeStack[i]->rightChild, &(routeStack[i]->rightChild));
						leftRotation( routeStack[i], targetPtrPtr);
						return; // Μετά απο περιστροφές, το δένδρο είναι AVL.
					}
				}
			}

			// Άν το ύψος του αριστερού παιδιού του ίδιου γονικού κόμβου έχει μεγαλύτερη ή ίση τιμή απο το δεξί (του οποίου ο μετρητής αυξήθηκε μόλις) τότε τα ύψη των προγόνων δεν εξαρτώνται απο τον συγκεκριμένο κόμβο, άρα τα υπόλοιπα ύψη δεν μεταβάλλονται.
			if ( routeStack[i]->leftHeight >= routeStack[i]->rightHeight ){
				return;
			}
		} else {
			// Ο τρέχον κόμβος της πορείας της αναζήτησης είναι αριστερό παιδί του προηγούμενου (πρέπει να κάνω ελέγχους και μεταβολές για αριστερό παιδί του γονέα)
			routeStack[i]->leftHeight++; //Αυξάνω τον μετρητή ύψους του αριστερού παιδιού
			if ( routeStack[i]->leftHeight - 1 > routeStack[i]->rightHeight ) { //Ελέγχω αν υπάρχει πρόβλημα
				if ( routeStack[i]->leftChild->leftHeight >
				     routeStack[i]->leftChild->rightHeight ) {  // Περίπτωση Αριστερά-Αριστερά (left-left)
					if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα"
						rightRotation( routeStack[i], &root );
						return; // Μετά απο περιστροφή, το δένδρο είναι AVL.
					} else {
						AVL_Node** targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild); // Ανάλογο με την γραμμή 161
						rightRotation( routeStack[i], targetPtrPtr);
						return; // Μετά απο περιστροφή, το δένδρο είναι AVL.
					}
				} else { // Περίπτωση Αριστερά-Δεξιά (left-right)
					if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα"
						leftRotation( routeStack[i]->leftChild, &(routeStack[i]->leftChild));
						rightRotation( routeStack[i], &root ); // Μετά απο περιστροφή, το δένδρο είναι AVL
						return; // Μετά απο περιστροφές, το δένδρο είναι AVL.
					} else {
						AVL_Node** targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild);
						leftRotation( routeStack[i]->leftChild, &(routeStack[i]->leftChild));
						rightRotation( routeStack[i], targetPtrPtr);
						return; // Μετά απο περιστροφές, το δένδρο είναι AVL.
					}
				}
			}

			// Άν το ύψος του αριστερού παιδιού του ίδιου γονικού κόμβου έχει μεγαλύτερη ή ίση τιμή απο το δεξί (του οποίου ο μετρητής αυξήθηκε μόλις) τότε τα ύψη των προγόνων δεν εξαρτώνται απο τον συγκεκριμένο κόμβο, άρα τα υπόλοιπα ύψη δεν μεταβάλλονται.
			if ( routeStack[i]->rightHeight >= routeStack[i]->leftHeight ){
				return;
			}
		}
	}
	return;
}

void AVL_Tree::updateTree_Delete( AVL_Node** routeStack, int top ){
	int i;
	for ( i = top - 1; i >= 0; i-- ) { // top-1 γιατί στο top έχω το στοιχείο που μόλις διέγραψα και για λόγους ομοιομορφίας με το updateTree_insert

		if (routeStack[i]->leftChild){
			routeStack[i]->leftHeight = routeStack[i]->leftChild->getHeight() + 1;
		} else {
			routeStack[i]->leftHeight = 0;
		}

		if (routeStack[i]->rightChild){
			routeStack[i]->rightHeight = routeStack[i]->rightChild->getHeight() + 1;
		} else{
			routeStack[i]->rightHeight = 0;
		}

		if ( routeStack[i]->rightHeight - routeStack[i]->leftHeight > 1 ) { //Ελέγχω αν υπάρχει πρόβλημα δεξιά.
			if ( routeStack[i]->rightChild->rightHeight >= routeStack[i]->rightChild->leftHeight ) {  // Περίπτωση Δεξιά-Δεξιά (right-right) ή περίπτωση που τα δένδρα έχουν ίδιο ύψος.
				if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα".
					leftRotation( routeStack[i], &root );
				} else {
					AVL_Node **targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild);
					//Δίνω στο rotation τον δείκτη του γονέα προς τον κόμβο με πρόβλημα ("στόχος"):
					// Αν ο "στόχος" είναι δεξί παιδί του γονέα τότε το targetsParent θα δείχνει στο μέλος του κόμβου που είναι δείκτης προς αριστερό παιδί. Ανάλογα αν ο "στόχος" είναι δεξί παιδι
					leftRotation( routeStack[i], targetPtrPtr );
					routeStack[i] = *targetPtrPtr; // Μετά την περιστροφή αλλάζουν οι σχέσεις γονιών-παιδιών, ενώ αυτή η διαφορά, δεν αντικατοπτρίζεται στην στοίβα.
												  // Δηλαδή, γίνεται διόρθωση αυτού του προβλήματος
				}
			} else { // Περίπτωση Δεξιά-Αριστερά (right-left)
				if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα"
					rightRotation( routeStack[i]->rightChild, &(routeStack[i]->rightChild));
					leftRotation( routeStack[i], &root );
				} else {
					AVL_Node **targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild); // Ανάλογο με την γραμμή 353-354
					rightRotation( routeStack[i]->rightChild, &(routeStack[i]->rightChild));
					leftRotation( routeStack[i], targetPtrPtr );
					routeStack[i] = *targetPtrPtr;// Μετά την περιστροφή αλλάζουν οι σχέσεις γονιών-παιδιών, ενώ αυτή η διαφορά, δεν αντικατοπτρίζεται στην στοίβα.
					// Δηλαδή, γίνεται διόρθωση αυτού του προβλήματος
				}
			}
		} else if ( routeStack[i]->leftHeight - routeStack[i]->rightHeight > 1 ) { //Ελέγχω αν υπάρχει πρόβλημα αριστερά.
			if ( routeStack[i]->leftChild->leftHeight >= routeStack[i]->leftChild->rightHeight ) {  // Περίπτωση Αριστερά-Αριστερά (left-left)
				if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα"
					rightRotation( routeStack[i], &root );
				} else {
					AVL_Node **targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild); // Ανάλογο με την γραμμή 353-354
					rightRotation( routeStack[i], targetPtrPtr );
					routeStack[i] = *targetPtrPtr;// Μετά την περιστροφή αλλάζουν οι σχέσεις γονιών-παιδιών, ενώ αυτή η διαφορά, δεν αντικατοπτρίζεται στην στοίβα.
												 // Δηλαδή, γίνεται διόρθωση αυτού του προβλήματος
				}
			} else { // Περίπτωση Αριστερά-Δεξιά (left-right)
				if ( !i ) {// Έλέγχω αν ο κόμβος με πρόβλημα είναι η ρίζα η οποία δεν έχει κόμβο-"γονέα"
					leftRotation( routeStack[i]->leftChild, &(routeStack[i]->leftChild));
					rightRotation( routeStack[i], &root );
				} else {
					AVL_Node **targetPtrPtr = routeStack[i - 1]->rightChild == routeStack[i] ? &(routeStack[i - 1]->rightChild) : &(routeStack[i - 1]->leftChild); // Ανάλογο με την γραμμή 353-354
					leftRotation( routeStack[i]->leftChild, &(routeStack[i]->leftChild));
					rightRotation( routeStack[i], targetPtrPtr );
					routeStack[i] = *targetPtrPtr;// Μετά την περιστροφή αλλάζουν οι σχέσεις γονιών-παιδιών, ενώ αυτή η διαφορά, δεν αντικατοπτρίζεται στην στοίβα.
												 // Δηλαδή, γίνεται διόρθωση αυτού του προβλήματος
				}
			}
		}

	}
	return;
}

void AVL_Tree::leftRotation( AVL_Node *targetNode, AVL_Node** targetPtrPtr ) {
	(*targetPtrPtr)=targetNode->rightChild; // Θέτω παιδί του γονέα το δεξί παιδί του targetNode
	AVL_Node* temp=targetNode->rightChild; // "Κρατάω" το δεξί παιδί του targetNode
	targetNode->rightChild = targetNode->rightChild->leftChild; // Θέτω δεξί παιδί του targetNode το αριστερό παιδί του δεξιού παιδιού του targetNode
	targetNode->rightHeight=temp->leftHeight; // Ενημερώνω το ύψος του νέου δεξιού παιδιού του targetNode απο το ύψος του παλιού γονέα του
	temp->leftChild=targetNode; // Θέτω αριστερό παιδί του temp το targetNode
	temp->leftHeight = temp->leftChild->getHeight() + 1; // Ενημερώνω το ύψος του temp
}

void AVL_Tree::rightRotation( AVL_Node *targetNode, AVL_Node** targetPtrPtr ) {
	(*targetPtrPtr)=targetNode->leftChild;// Θέτω παιδί του γονέα το αριστερό παιδί του *targetNode
	AVL_Node* temp=targetNode->leftChild; // "Κρατάω" το αριστερό παιδί του targetNode
	targetNode->leftChild = targetNode->leftChild->rightChild; // Θέτω αριστερό παιδί του targetNode το δεξί παιδί του αριστερού παιδιού του targetNode
	targetNode->leftHeight=temp->rightHeight;// Ενημερώνω το ύψος του νέου αριστερού παιδιού του targetNode απο το ύψος του παλιού γονέα του
	temp->rightChild=targetNode; // Θέτω δεξί παιδί του temp το targetNode
	temp->rightHeight = temp->rightChild->getHeight() + 1; // Ενημερώνω το ύψος του temp
}

AVL_Node** AVL_Tree::internalSearchNode_WithStack( const std::string &a_word, AVL_Node** &stackOfSerches, int &top ) {
	AVL_Node *currentNode;
	AVL_Node **pointTo;
	top=0;
	currentNode = root; // Αρχίζω την αναζήτηση απο την ρίζα
	pointTo = &root;
	while (currentNode){
		stackOfSerches[top++] = currentNode;
		if (a_word == currentNode->Data){
			return pointTo;
		}
		else if(a_word < currentNode->Data){
			pointTo = &currentNode->leftChild;
			currentNode = currentNode->leftChild;
		}
		else{
			pointTo = &currentNode->rightChild;
			currentNode = currentNode->rightChild;
		}
	}
	return pointTo;
}

void AVL_Tree::deleteNode_NoChildren(AVL_Node **targetPtrPtr, AVL_Node** &routeStack, int& top) {
	delete *targetPtrPtr;
	*targetPtrPtr= nullptr;
	routeStack[--top]= nullptr;
}

void AVL_Tree::deleteNode_OneChild( AVL_Node **targetPtrPtr, AVL_Node** &routeStack, int& top ) {
	if ((**targetPtrPtr).leftChild){ // Πρέπει να αντικατασταθεί απο το αριστερό παιδί
		AVL_Node *temp;
		temp = *targetPtrPtr;
		*targetPtrPtr = (**targetPtrPtr).leftChild; // Αντικατάσταση απο αριστερο παιδί
		routeStack[top-1] = *targetPtrPtr; // Ενημέρωση στοίβας
		delete temp; // Διαγράφω "παλιό" παιδί
	}
	else{ // Πρέπει να αντικατασταθεί απο το δεξί παιδί
		AVL_Node *temp;
		temp = *targetPtrPtr;
		*targetPtrPtr = (**targetPtrPtr).rightChild; //Αντικατάσταση απο δεξί παιδί
		routeStack[top-1] = *targetPtrPtr;// Ενημέρωση Στοίβας
		delete temp; // Διαγράφω "παλιό" παιδί
	}
	top--;
}

void AVL_Tree::deleteNode_TwoChildren( AVL_Node **targetPtrPtr, AVL_Node** &routeStack, int &top ) {

	//Αναζήτηση μεγαλύτερου κόμβου του αριστερού υποδένδρου
	AVL_Node **pointToRightMost;
	AVL_Node *currentNode,*buffer;
	pointToRightMost = &((*targetPtrPtr)->leftChild);
	buffer = (*targetPtrPtr)->leftChild;
	routeStack[top++]=buffer;
	currentNode = (*targetPtrPtr)->leftChild->rightChild;
	while (currentNode){
		routeStack[top++]=currentNode;
		pointToRightMost = &buffer->rightChild;
		buffer=buffer->rightChild;
		currentNode = currentNode->rightChild;
	}

	//Αντικατάσταση του κόμβου προς διαγραφή με τον κόμβο που βρέθηκε προηγουμένως
	(**targetPtrPtr).Data = (**pointToRightMost).Data;
	(**targetPtrPtr).timesAppeared = (**pointToRightMost).timesAppeared;

	//Διαγραφή του μεγαλύτερου κόμβου του αριστερού υποδένδρου
	if ((**pointToRightMost).leftChild ){
		deleteNode_OneChild(pointToRightMost, routeStack, top);
	}
	else{
		deleteNode_NoChildren(pointToRightMost , routeStack, top);
	}
}
