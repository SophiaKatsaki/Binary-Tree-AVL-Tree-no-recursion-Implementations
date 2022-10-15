//
// Created by Ioannis Baraklilis and Sophia Katsaki on 6/7/2020.
// Δοκιμή των επιδόσεων των δέντρων στο αρχείο input.txt βάσει προδιαγραφών.
//


#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cctype>

#include "BinarySearchTree.h" // Δομή απλού δυαδικού δένδρου αναζήτησης
#include "AVL_Tree.h" // Δομή δυαδικού δένδρου αναζήτησης τύπου AVL

#define Q_SIZE 1000 // Μέγεθος πίνακα απο όπου κάνω αναζήτηση
#define NStoMS 0.000001 // Πολλαπλασιάζω με το NStoMS για να μετατρέψω τα nanoseconds σε milliseconds

#include <iostream>

bool processChar(char &c); // Άν ο χαρακτήρας είναι αποδεκτός επιστρέφει true και τον μετατρέπει σε πεζό, διαφορετικά επιστρέφει false και δεν τον αλλάζει
void randomInsert(const std::string &word, std::string *Q, long &currQ); // Εισάγει με κάποια πιθανότητα την λέξη word σε τυχαία θέση του συνόλου (array) Q

int main(){
	std::ifstream in;

	in.open("input.txt",std::ios::in); // Ανοίγω το αρχείο με όνομα input.txt για εισαγωγή κειμένου
	if ( !in.is_open() ) return 1; // Άν το αρχείο δεν άνοιξε, τερματίζω το πρόγραμμα
	//Θεωρώ ότι το αρχείο είναι ανοικτό

	// Μεταβλητές για διαχείρηση πίνακα αναζήτησης Q
	std::string *Q = new std::string[Q_SIZE]; // Δημιουργώ τον πίνακα αναζήτησης Q
	long currQ = 0; // Δείκτης (μετρητής) θέσης που εισάγω στοιχεία με τυχαίο τρόπο
	std::srand( std::time( nullptr) );


	// Μεταβλητές διαχείρησης του κειμένου
	std::string temp,line; // Μία μεταβλητή που αποθηκεύει μία λέξη πρίν την εισαγωγή (temp) και μία που αποθηκεύει την γραμμή που επεξεργάζομαι (line)
	char c; // Μία μεταβλητή που αποθηκεύει τον χαρακτήρα που επεξεργάζομαι

	//Δημιουργώ τις δομές
	BinarySearchTree bst;
	AVL_Tree avl;


	//Διαβάζω το αρχείο γραμμή-γραμμή
	while ( std::getline(in,line) ){ // Διαβάζω γραμμές μέχρι να μην υπάρχουν άλλες γραμμές προς ανάγνωση
		unsigned int it; // Μετρητής επανάληψης
		temp = "";
		for (it=0;it<line.length();it++){
			c = line[it];

			if (!processChar(c)){ // Άν δεν έχω αλφαβητικό χαρακτήρα (λατινικό) τότε έχω ολόκληρη λέξη που πρέπει να εισάγω
				if (temp!=""){ // Η λέξη δεν είναι κενή
					randomInsert(temp, Q, currQ); // Εισαγωγή σε Q αν χρειαστεί

					bst.insertNode(temp); // Κάνω εισαγωγές
					avl.insertNode(temp);
					temp=""; // Αρχικοποιώ το temp για να εισάγω στην συνέχεια νέα λέξη
				}
			}
			else{ // Συνεχίζω την "δημιουργία" της λέξης
				// Άν είναι αποδεκτός χαρακτήρας τον προσθέτω στην λέξη. Διαφορετικά, προχωράω στην επεξεργασία του επόμενου χαρακτήρα
					temp+=c;
			}

		}
		if (temp!=""){ // Στο τέλος της επανάληψης (εξάντληση χαρακτήρων γραμμής), κάνω εισαγωγή την λέξη που δημιουργήθηκε στο τέλος όπου δεν υπαρχει μή αλφαβητικός χαρακτήρας (άν δεν είναι κενή)
			randomInsert(temp, Q, currQ); // Εισαγωγή σε Q αν χρειαστεί

			bst.insertNode(temp);
			avl.insertNode(temp);
		}

	}

	//Έξοδος αποτελεσμάτων δοκιμών δομής
	// Έξοδος χρονομετρήσεων
	std::ofstream tOut;
	tOut.open("Time_Count_output.txt",std::ios::out);
	if ( !tOut.is_open() ) return 1; // Άν το αρχείο δεν άνοιξε, τερματίζω το πρόγραμμα

	// Έξοδος αποτελεσμάτων ερωτημάτων
	std::ofstream bstOut, avlOut;
	bstOut.open("BinarySearchTree_output.txt",std::ios::out);
	avlOut.open("AVL_Search_Tree_output.txt",std::ios::out);
	if ( !bstOut.is_open() ) return 1; // Άν το αρχείο δεν άνοιξε, τερματίζω το πρόγραμμα
	if ( !avlOut.is_open() ) return 1; // Άν το αρχείο δεν άνοιξε, τερματίζω το πρόγραμμα


	//Μετρήσεις
	long iterator, end = currQ; // Δηλώνω μετρητές επαναλήψεων

	bstOut << "Binary Search Tree Queries:\n" << std::endl;
	auto start = std::chrono::steady_clock::now(); // Αρχίζω το χρονόμετρο
	for ( iterator = 0; iterator < end; iterator++ ) {
		bstOut << *bst.searchNode( Q[iterator] ) << std::endl ; // Ψάχνω την λέξη στο δένδρο
	}
	auto bstTime = (std::chrono::steady_clock::now() - start); // Αποθηκεύω τον συνολικό χρόνο αναζήτησης

	avlOut << "AVL Search Tree Queries:\n" << std::endl;
	start = std::chrono::steady_clock::now(); // Αρχίζω το χρονόμετρο
	for ( iterator = 0; iterator < end; iterator++ ) {
		avlOut << *avl.searchNode( Q[iterator] ) << std::endl ; // Ψάχνω την λέξη στο δένδρο
	}
	auto avlTime = (std::chrono::steady_clock::now() - start); // Αποθηκεύω τον συνολικό χρόνο αναζήτησης


	tOut << "Results for searching set Q with " << currQ << " elements (including printing to files):" << std::endl;
	tOut << "Simple Binary Search Tree Time for Q: " << std::chrono::duration_cast<std::chrono::nanoseconds>(bstTime).count() * NStoMS << " milliseconds" << std::endl;
	tOut << "AVL Search Tree Time for Q: " << std::chrono::duration_cast<std::chrono::nanoseconds>(avlTime).count() * NStoMS << " milliseconds" << std::endl;

	//Κλείσιμο αρχείων
	in.close();
	tOut.close();
	bstOut.close();
	avlOut.close();

	//Αποδέσμευση Q
	delete[] Q;
	return 0;
}

bool processChar(char &c){
	if ( (c>='a' && c<='z') || (c>='A' && c<='Z') ){  // Αποδεκτοί χαρακτήρες θεωρούνται οι πεζοί και κεφαλαίοι λατινικοί
		c = (char)std::tolower(c);
		return true;
	} else
		return false;
}

void randomInsert(const std::string &word, std::string *Q, long &currQ){
	if (currQ < Q_SIZE) Q[ currQ++ ] = word; // Πρώτα "γεμίζω" τον πίνακα με Q_SIZE λέξεις για να είμαστε σίγουροι ότι έχει Q_SIZE λέξεις συνολικά
	else{ // Όταν συγκεντρωθούν Q_SIZE λέξεις, εισάγω σε τυχαία θέση την λέξη word με πιθανότητα 15%
		if ( rand() % 100 < 15 ){ // Πιθανότητα 15%
			Q[ rand() % Q_SIZE ] = word;
		}
	}
}
