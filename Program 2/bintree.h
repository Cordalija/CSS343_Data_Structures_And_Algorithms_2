// ------------------------------------- bintree.h ----------------------------
// Programmer: Jasenko Cordalija. 
// Course Number: CS343A
// Creation Date: 01/21/2016
// Date of Last Modification: 01/30/2016
// ----------------------------------------------------------------------------
// Purpose - BinTree Class is a binary search tree project. This project reads
// a data file that consists of many lines in order to build a binary search 
// tree, in this project data2.txt was used as sample. Each line will be used 
// to build a tree, with each line consisitng of many strings terminating with 
// the string '$$'. This class also implements a NodeData class (using 
// nodedata.h and nodedata.cpp files). This BinTree class displays prints using
// inorder traversal, and has functions to retrieve and get height in the 
// tree. BinTree class can also fill an array of NodeData* using inorder 
// traversal of the tree leaving the tree empty, and it can build a balanced
// BinTree from a sorted array of NodeData* leaving the original array filled 
// with NULLs.
// ----------------------------------------------------------------------------
// Special Notes and Assumptions - Assumed that all data will be accurate and 
// correct so that there is no need for special error handling. Assumed no
// size error checking for bstreeToArray. Assumed allocated array of 100 NULL
// elements for this project.
//-----------------------------------------------------------------------------

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include "nodedata.h"

using namespace std;

class BinTree 
{

	// ------------------------ Operator Overload << --------------------------
	// Operator Overload (<<), prints out the true using inorder traversal. 
	// NodeData class will be responsible for the display of its own data.
	// ------------------------------------------------------------------------
	friend::ostream& operator<<(ostream &, const BinTree&);

public:

	// ------------------------ Default Constructor ---------------------------
	// Default Constructor creates an empty tree
	// ------------------------------------------------------------------------
	BinTree(); 

	// ------------------------ Copy Constructor ------------------------------
	// Deep Copy Constructor function, makes an exact deep copy of a tree into
	// assinged parameter, one tree to another.
	// ------------------------------------------------------------------------
	BinTree(const BinTree &); 

	// ------------------------ Destructor ------------------------------------
	// Destructor deletes tree and sets its root to NULL.
	// ------------------------------------------------------------------------
	~BinTree(); 

	// ------------------------ isEmpty ---------------------------------------
	// isEmpty boolean check wether a tree is empty or not, and returns true
	// if tree is empty else returns false.
	// ------------------------------------------------------------------------
	bool isEmpty() const; 	

	// ------------------------ makeEmpty -------------------------------------
	// makeEmpty goes through a tree and deletes all children, sets them to 
	// NULL, and root to NULL as well. Deletes entire tree.
	// ------------------------------------------------------------------------
	void makeEmpty(); 

	// ------------------------ insert ----------------------------------------
	// insert checks if a value that is passed into tree already exists, and if
	// it does not, traverses through the tree depending on the value passed in
	// to locate correct loaction for insertion. 
	// ------------------------------------------------------------------------
	bool insert(NodeData* &); 

	// ------------------------- displaySideways ------------------------------
	// Displays a binary tree as though you are viewing it from the side;
	// hard coded displaying to standard output.
	// ------------------------------------------------------------------------
	void displaySideways() const;

	// ------------------------ Operator Overload = ---------------------------
	// Operator Overload =, assigns one tree to another tree.
	// ------------------------------------------------------------------------
	BinTree& operator=(const BinTree &);

	// ------------------------ Operator Overload == --------------------------
	// Operator Overload =, examines two trees and returns true if they
	// have the same data and structure, and a false if they are not the same.
	// ------------------------------------------------------------------------
	bool operator==(const BinTree &) const;

	// ------------------------ Operator Overload != --------------------------
	// Operator Overload =, examines two trees and returns true if the do not
	// have the same data and structure, and a true if they are the same.
	// ------------------------------------------------------------------------
	bool operator!=(const BinTree &) const;

	// ------------------------ retrieve --------------------------------------
	// retrieve function gets the NodeData* of a given object in tree via
	// pass by reference, and reports back wether the object is found. If the
	// object is found, 2nd parameter in function will point to object in tree.
	// ------------------------------------------------------------------------
	bool retrieve(const NodeData &, NodeData* &);

	// ------------------------ getHeight -------------------------------------
	// getHeight finds the height of a given value in the tree. Solves problem
	// for general binary tree where data could be stored anywhere. Height of
	// a node at a leaf is 1, height of a value not found is 0.
	// ------------------------------------------------------------------------
	int getHeight(const NodeData &) const;

	// ------------------------ bstreeToArray ---------------------------------
	// bstreeToArray fills an array of Nodedata* using inorder traversal of 
	// tree, afterwards leaves tree empty and Array filled with the values
	// after bstreeToArray call. Assumed statically allocated array of 100 NULL
	// elements with no necessary checking for size error beyond <= 100 & NULL.
	// ------------------------------------------------------------------------
	void bstreeToArray(NodeData*[]);

	// ------------------------ arrayToBSTree ---------------------------------
	// arrayToBSTree build a balanced BinTree from a Array that is sorted 
	// NodeData* afterwards the array is filled with NULLs. The root is
	// the middle (low+high)/2 with lowest subscript of array's range labeled
	// low and highest labeled high.
	// ------------------------------------------------------------------------
	void arrayToBSTree(NodeData*[]);

private:

	struct Node {
		NodeData* data;		// pointer to data object
		Node* left;			// left subtree pointer
		Node* right;		// right subtree pointer
	};
	Node* root ;			// node root for tree

	// -------------------- Helper Functions ----------------------------------
	// Helper functions will used to assist in recursive programming of code.
	// ------------------------------------------------------------------------

	// ------------------------ newNode ---------------------------------------
	// newNode, takes in NodeData* as parameter and creates new node for value.
	// ------------------------------------------------------------------------
	Node* newNode(NodeData*);

	// ------------------------ makeEmptyHelper -------------------------------
	// makeEmptyHelper is a make empty helper method. Takes in one parameter
	// of Node.
	// ------------------------------------------------------------------------
	void makeEmptyHelper(Node*&);

	// ------------------------ inorderHelper ---------------------------------
	// inorderHelper is a helper method for traversing tree, used for display 
	// 'cout'. Takes in one parameter of Node.
	// ------------------------------------------------------------------------
	void inorderHelper(Node*) const;

	// ------------------------ sideways --------------------------------------
	// Helper method for displaySideways. Takes in two parameters of Node and 
	// an int.
	// ------------------------------------------------------------------------
	void sideways(Node*, int) const;

	// ------------------------ inserter --------------------------------------
	// inserter is a helper method for inserting a value into tree. Takes in 
	// two paramters of Node and NodeData.
	// ------------------------------------------------------------------------
	bool inserter(Node *, NodeData*); 

	// ------------------------ assigner --------------------------------------
	// assigner is a deep copy helper for copy constructor and also for the
	// assingment operatore. Takes in two paramete of Node, copying and
	// referencing one node to another being copied.
	// ------------------------------------------------------------------------
	void assigner(Node*, Node* &);

	// ------------------------ equalizer -------------------------------------
	// equalizer is a operator overload == helper method used for comparing 
	// two tree to see if they have same structure and data. Takes in two
	// parameters of Node and Node.
	// ------------------------------------------------------------------------
	bool equalizer(Node*, Node*) const;

	// ------------------------ retriever -------------------------------------
	// retriever is a retrieve helper method. Takes in three parameter of Node,
	// and two NodeDatas.
	// ------------------------------------------------------------------------
	bool retriever(Node* &, const NodeData &, NodeData* &) const;

	// ------------------------ heightHelp ------------------------------------
	// heightHelp is a getHeight helper method. Takes in two parameter of Node 
	// and NodeData.
	// ------------------------------------------------------------------------
	int heightHelp(Node*, const NodeData&) const; 

	// ------------------------ secondHeightHelp ------------------------------
	// secondHeightHelp is a heightHelp helper method. If current data found is
	// equal to value looked for. Takes in one parameter of Node.
	// ------------------------------------------------------------------------
	int secondHeightHelp(Node*) const;

	// ------------------------ toArray ---------------------------------------
	// toArray is bstreeToArray helper method. Takes in two parameters of
	// Node and NodeData array.
	// ------------------------------------------------------------------------
	int toArray(Node*, NodeData* []);

	// ------------------------ toBSTree --------------------------------------
	// toBSTree is a arrayToBSTree helper method. Takes in four parameters of
	// Node, NodeData array, and two additional parameter of int. 
	// ------------------------------------------------------------------------
	void toBSTree(Node*, NodeData* [], int, int);
}; // end of BinTree Class

#endif

