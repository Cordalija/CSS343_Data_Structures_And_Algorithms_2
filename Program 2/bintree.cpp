// ------------------------------------- bintree.cpp --------------------------
// Programmer: Jasenko Cordalija. 
// Course Number: CS343A
// Creation Date: 01/21/2016
// Date of Last Modification: 01/30/2016
// ----------------------------------------------------------------------------
// Purpose - BinTree Class is a binary search tree project. This project reads
// a data file that consists of many lines in order to build a binary search 
// tree, in this project data2.txt was used as sample. Each line will be used 
// to build a tree, with each line consisting of many strings terminating with 
// the string '$$'. This class also implements a NodeData class (using 
// nodedata.h and nodedata.cpp files). This BinTree class displays prints using
// inorder traversal, and has functions to retrieve and get height in the 
// tree. BinTree class can also fill an array of NodeData* using inorder 
// traversal of the tree leaving the tree empty, and it can build a balanced
// BinTree from a sorted array of NodeData* leaving the original array filled 
// with NULLs.
// ----------------------------------------------------------------------------
// Special Notes and Assumptions - Assumed that all data will be accurate and 
// correct so that there is no need for special error handling. Assumed no need
// for size error checking for bstreeToArray. Assumed allocated array of 100 
// NULL elements for this project.
//-----------------------------------------------------------------------------

#include "bintree.h"

// ------------------------ Default Constructor -------------------------------
// Default Constructor creates an empty tree with root equal to NULL.
// ----------------------------------------------------------------------------
BinTree::BinTree()
{
	root = NULL;		// default of root is NULL 
}

// ------------------------ Copy Constructor ----------------------------------
// Deep Copy Constructor function, makes an exact deep copy of a tree into
// assinged parameter, one tree to another is copied exactly here.
// ----------------------------------------------------------------------------
BinTree::BinTree(const BinTree &btc)
{
	root = NULL;
	*this = btc;		// copies tree btc to new object
}	// end of function

// ------------------------ Destructor ----------------------------------------
// Destructor deletes tree and sets its root to NULL using makeEmpty function.
// ----------------------------------------------------------------------------
BinTree::~BinTree()
{
	makeEmpty();		// destructor calls makeEmpty fuction
}	// end of function

// ------------------------ isEmpty -------------------------------------------
// isEmpty boolean checks if a tree is empty or not, and returns true
// if tree is empty with its root being NULL, returns false if root isn't NULL.
// ----------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
	if (root == NULL)		// checks first if root is NULL to determine
	{
		return true;
	}

	else
	{
		return false;		// returns false if root is not NULL, is not empty.
	}
}	// end of function

// ------------------------ makeEmpty -----------------------------------------
// makeEmpty function goes through a tree and deletes all it's children, and 
// sets them to NULL, and root set to NULL as well and deleted. 
// ----------------------------------------------------------------------------
void BinTree::makeEmpty()
{
	makeEmptyHelper(root);		// calls helper function to empty tree
	root = NULL;				// after emptying tree sets root to NULL
}	// end of function

// ------------------------ makeEmptyHelper -----------------------------------
// makeEmptyHelper is a make empty helper method. It takes in one parameter
// of Node, recursively traverses through the tree deleting data and root.
// ----------------------------------------------------------------------------
void BinTree::makeEmptyHelper(Node* &curr)
{
	if (curr != NULL)    // if current root is not NULL does traversal
	{
		makeEmptyHelper(curr->left); // left side recursion call
		makeEmptyHelper(curr->right);    // right side recursion call

		delete (curr->data);		// deletes current root data
		(curr->data) = NULL;		// sets current root data to NULL
		delete curr;				// deletes current root and sets it to NULL
		curr = NULL;				// memory leaks are now taken care of
	}
}	// end of function

// ------------------------ Operator Overload = -------------------------------
// Operator Overload =, assigns one tree to another tree using helper function
// for recursive traversing of tree, step by step going through entire tree.
// ----------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &rhsTree)
{
	if (*this == rhsTree)	// check to see if rhs tree is equal to lhs first
	{
		return *this;
	}

	makeEmpty();		// if rhs and lhs not equal, empties out lhs first

	assigner(rhsTree.root, root);	// helper function to assign rhs to lhs
	return *this;		// once done assigning, returns tree
}	// end of function

// ------------------------ assigner ------------------------------------------
// assigner is a deep copy helper method for copy constructor and also for the
// assingment operator use too. Takes in two parameters of Node, copying and
// referencing one Node to another being copied starting from root.
// ----------------------------------------------------------------------------
void BinTree::assigner(Node* rhsTree, Node* &lhsTree)
{
	if (rhsTree != NULL)	// only if the rhs tree is not empty/NULL root
	{
		lhsTree = new Node;		// creates new node, a lhsTree
		NodeData *newT = new NodeData(*rhsTree->data);
		lhsTree->data = newT;	// gives lhs tree the data of the lhsTree

		assigner(rhsTree->left, lhsTree->left);		// recursive helper for lhs
		assigner(rhsTree->right, lhsTree->right);	// recursive helper for rhs
	}

	else if (rhsTree == NULL)
	{
		lhsTree = NULL;		// if rhsTree is NULL then lhs tree is NULL
	}
}	// end of function

// ------------------------ Operator Overload == ------------------------------
// Operator Overload == function examines two trees and returns true if they
// have the same data and structure, and a false if they are not the same. Uses
// helper method to traverse and compare trees.
// ----------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &rhsTree) const
{
	// simple check to return true if both lhs and rhs tree both NULL
	if (root == NULL && rhsTree.root == NULL) 
	{
		return true;
	}

	else
	{
		return equalizer(root, rhsTree.root);	// helper function recusive call
	}
}	// end of function

// ------------------------ equalizer -----------------------------------------
// equalizer is a operator overload == helper method used for comparing 
// two tree to see if they have same structure and data. Takes in two
// parameters of Node and Node.
// ----------------------------------------------------------------------------
bool BinTree::equalizer(Node* leftN, Node* rightN) const
{
	if (leftN == NULL || rightN == NULL)
	{
		return false;	// returns false if one or the other is NULL
	}

	if (leftN == NULL && rightN == NULL) 
	{
		return true;	// check again if right and both are equal to NULL
	}

	if (*leftN->data == *rightN->data)	// examines data from left and right
	{
		return true;	// returns true if the data of both left and right same
	}

	// if left and right data same while calling recursively to traverse tree
	// true is returned at end and helper function recursively continued until
	else if ((*leftN->data == *rightN->data)
		&& equalizer(leftN->left, rightN->left)
		&& equalizer(leftN->right, rightN->right))
	{
		return true;	// returns true if both trees have same structure/data
	}
}	// end of function

// ------------------------ Operator Overload != ------------------------------
// Operator Overload !=, examines two trees and returns true if the do not
// have the same data and structure, and a true if they are the same.
// ----------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree &rhsTree) const
{
	if (!(*this == rhsTree))	// examines if two tree are identical 
	{
		return true;
	}

	else
	{
		return false;	// returns a false if lhsTree and rhsTree not identical
	}
}	// end of function

// ------------------------ retrieve ------------------------------------------
// retrieve function gets the NodeData* of a given object in tree via
// pass by reference, and reports back if the object is found. If the
// object is found, 2nd parameter in function will point to object in tree. If
// object not found second parameter stays garbage(NULL).
// ----------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &found, NodeData* &returned)
{
	returned = NULL;	// initially on grabage for now
	retriever(root, found, returned);	// calls helper functions to search

	if (returned != NULL)	// true if object is found and pointer is assigned
	{
		return true;
	}

	else 
	{
		return false;	// false returned if no object was found and retrieved
	}
}	// end of function

// ------------------------ retriever -----------------------------------------
// retriever is a retrieve helper method. Takes in three parameter of Node,
// and two NodeDatas. Traverses through tree in search of given object, 
// assigns NULL to returned if not found, else returned will point to actual
// object in the tree.
// ----------------------------------------------------------------------------
bool BinTree::retriever(Node* &curr, const NodeData &found, NodeData* &returned) const
{
	if (curr == NULL)	// check if current is NULL, if so returned still NULL
	{
		returned = NULL;	// stays garbage pointer
		return false;	// false returned
	}

	if (*curr->data == found)	// object val found from parameter
	{
		returned = curr->data;	// NodeData assigned to given object in tree
		return true;	// true is returned, retrieve was successfull
	}

	else if (*curr->data < found)	// traverses right if current is smaller
	{
		retriever(curr->right, found, returned);	// helper function rhs
	}

	else if (*curr->data > found)	// traverses left if current is larger
	{
		retriever(curr->left, found, returned);		// helper function lhs
	}
}	// end of function

// ------------------------ getHeight -----------------------------------------
// getHeight finds the height of a given value in the tree. Solves problem
// for general binary tree where data could be stored anywhere. Height of
// a node at a leaf is 1, height of a value not found is 0.
// ----------------------------------------------------------------------------
int BinTree::getHeight(const NodeData &val) const
{
	return heightHelp(root, val);	// calls helper method for traversing tree
}	// end of function

// ------------------------ heightHelp ----------------------------------------
// heightHelp is a getHeight helper method. Takes in two parameter of Node 
// and NodeData. Recursively traverses tree choosing larger of the two sides
// using max on helper function. If found uses second helper function.
// ----------------------------------------------------------------------------
int BinTree::heightHelp(Node* curr, const NodeData &val) const 
{
	if (curr == NULL)
	{
		return 0;	// returns value 0 if root current is NULL
	}

	else if (*curr->data == val)	// current is value searched for
	{
		return secondHeightHelp(curr);	// second helper function for height
	}

	else
	{	// returns recursion helper of larger between left or right using max 
		return max(heightHelp(curr->left, val), heightHelp(curr->right, val));
	}
}	// end of function

// ------------------------ secondHeightHelp ----------------------------------
// secondHeightHelp is a heightHelp helper method. If current data found is
// equal to value looked for. Takes in one parameter of Node. Adds + 1 since
// node at a leaf start at 1.
// ----------------------------------------------------------------------------
int BinTree::secondHeightHelp(Node* curr) const
{
	if (curr != NULL) // 2nd helper function when current value found
	{	
		// adds + 1 since height of node leaf starts at 1; <- height definition
		return 1 + (max(secondHeightHelp(curr->left),
			secondHeightHelp(curr->right)));
	}

	else if (curr == NULL)
	{
		return 0; // if current is NULL again returns 0
	}
}	// end of function

// ------------------------ insert --------------------------------------------
// insert checks if a value that is passed into tree already exists, and if
// it does not, traverses through the tree depending on the value passed in
// to locate correct loaction for insertion. 
// ----------------------------------------------------------------------------
bool BinTree::insert(NodeData* &x) 
{
	if (x == NULL)	// returns false value in parameter is NULL, no success
	{
		return false;
	}

	// if root of tree is NULL makes a new node and assigns it insert value
	if (root == NULL) 
	{
		root = newNode(x);	// new node created
		return true;	// returns true, insert was success 
	}

	return inserter(root, x);	// helper function finds location for value
}	// end of function

// ------------------------ inserter ------------------------------------------
// inserter is a helper method for inserting a value into tree. Takes in 
// two paramters of Node and NodeData.
// ----------------------------------------------------------------------------
bool BinTree::inserter(Node *curr, NodeData* x) 
{
	if (*x < *(curr->data))		// check first if value < current root data
	{

		if (curr->left == NULL)
		{
			curr->left = newNode(x); // if now current root NULL makes new node
			return true;	// returns true, insert was success
		}

		return inserter(curr->left, x); // insert not success call helper again
	}

	if (*x > *(curr->data))	// check if value > current root data
	{
		if (curr->right == NULL)
		{
			curr->right = newNode(x);
			return true;	// return true, insert was success
		}

		// insert not sucess calls for helper function again to traverse
		return inserter(curr->right, x);	
	}

	return false;	// else returns false
}	// end of function

// ------------------------ newNode -------------------------------------------
// newNode, takes in NodeData* as parameter and creates new node for the value.
// ----------------------------------------------------------------------------
BinTree::Node* BinTree::newNode(NodeData *in)
{
	Node *nd = new BinTree::Node;	// creates new node
	nd->data = in;		// assings node data passed in from parameter
	nd->left = NULL;	// set both children to NULL to create root
	nd->right = NULL;

	return nd;	// returns node
}	// end of function

// ------------------------ Operator Overload << ------------------------------
// Operator Overload (<<), prints out the true using inorder traversal. 
// NodeData class will be responsible for the display of its own data.
// ----------------------------------------------------------------------------
ostream& operator<<(ostream &output, const BinTree &printBST)
{
	// calls helper function to traverse tree inorder to print out tree display
	printBST.inorderHelper(printBST.root);	
	output << endl;	
	return output;	// output is returned inorder traverse
}	// end of function

// ------------------------ inorderHelper -------------------------------------
// inorderHelper is a helper method for traversing tree, used for display 
// 'cout'. Takes in one parameter of Node. If root is not NULL traverses
// the tree inorder sequence.
// ----------------------------------------------------------------------------
void BinTree::inorderHelper(Node *curr) const
{
	if (curr != NULL)	// current cant be NULL for left and right sides
	{
		inorderHelper(curr->left);	// recursive function for left side
		cout << *curr->data << " ";	// prints inorder with these three lines	
		inorderHelper(curr->right);	// recursive function for right side
	}
}	// end of function

// ------------------------ bstreeToArray -------------------------------------
// bstreeToArray fills an array of Nodedata* using inorder traversal of 
// tree, afterwards leaves tree empty and Array filled with the values
// after bstreeToArray call. Assumed statically allocated array of 100 NULL
// elements with no necessary checking for size error beyond <= 100 & NULL.
// ----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* bsTree[])
{
	toArray(root, bsTree);	// calls recursive heler function
	makeEmpty();	// empties the tree once array is filled with tree's values
}	// end of function

// ------------------------ toArray -------------------------------------------
// toArray is bstreeToArray helper method. Takes in two parameters of
// Node and NodeData array.
// ----------------------------------------------------------------------------
int BinTree::toArray(Node* curr, NodeData *bsTree[])
{
	if (curr == NULL)
	{
		return 0;	// if BSTree root is NULL returns a 0 for array.
	}

	else
	{
		// left side of tree is recursivelly stored into leftSide
		int leftSide = toArray(curr->left, bsTree);	

		NodeData* toArrayTemp;	// temporary NodeData to store the current data
		toArrayTemp = curr->data;

		curr->data = NULL;	// resets current data back to NULL
		*(bsTree + leftSide) = toArrayTemp;

		toArrayTemp = NULL;	// resets temporary NodeData back to NULL

		// right side of tree is recursivelly stored into rightSide
		// with new position starting from leftSides last/biggest value plus 1
		// to account for array's indexing
		int rightSide = toArray(curr->right, (bsTree + leftSide) + 1);

		return (1 + (leftSide + rightSide));	// returns completed array
	}
}	// end of function

// ------------------------ arrayToBSTree -------------------------------------
// arrayToBSTree build a balanced BinTree from a Array that is sorted 
// NodeData* afterwards the array is filled with NULLs. The root is
// the middle (low+high)/2 with lowest subscript of array's range labeled
// low and highest labeled high.
// ----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[])
{
	int h = 0;	// set to 0, will be used for array traversing and for loop

	for (int i = 0; i < 100; i++) // max array size assumed 100
	{
		if (arr[i] == NULL)
		{
			arr[i] = NULL;	// encounters NULL in array, array has reached end
		}

		else if (arr[i] != NULL)
		{
			h++;	// continues to increment h while there is no NULL in array
		}
	}

	makeEmpty();	// helper function to ensure empty tree

	// recursive function to transfer array into balanced tree, 0 represents
	// the low, h represents the high, h - 1 due to first increment in start
	toBSTree(root, arr, 0, h - 1); 
}	// end of function

// ------------------------ toBSTree ------------------------------------------
// toBSTree is a arrayToBSTree helper method. Takes in four parameters of
// Node, NodeData array, and two additional parameter of int. Asigns correct
// location in Tree by comparing values to the middle, smaller going left and
// starting from lowest to middle -1, while larger starting from middle + 1
// going right until end.
// ----------------------------------------------------------------------------
void BinTree::toBSTree(Node *curr, NodeData* arr[], int lowest, int highest)
{
	if (lowest > highest)
	{
		delete curr;	// compares if low is > high deletes current root 
		curr == NULL;	// sets curr to NULL these two fix memory leak 
	}

	if (lowest <= highest)	// if low is smaller then highest in from array
	{
		int middle = (lowest + highest) / 2;	// middle is created

		NodeData *tmp = arr[middle];	// temporary NodeData to store middle
		arr[middle] = NULL;		// resets to NULL for next round

		insert(tmp);	// inserts NodeData using insert function

		tmp = NULL;
		// recursive helper method for 1st half of balanced BinTree
		toBSTree(curr, arr, lowest, middle - 1); 

		// recursive helper method for 2nd half of balanced BinTree
		toBSTree(curr, arr, middle + 1, highest);
	}
}	// end of function

//------------------------- displaySideways -----------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}	// end of function

//---------------------------- Sideways ---------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;							// level incremented for location
		sideways(current->right, level);	// recursive helper for right side

		// indent for readability, 4 spaces per depth level, starting backwards
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);		   // recursive helper function lhs
	}
}	// end of function
