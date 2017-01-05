// ------------------------------------- graphl.cpp ---------------------------
// Programmer: Jasenko Cordalija. 
// Course Number: CS343A.
// Creation Date: 02/10/2016
// Date of Last Modification: 02/16/2016
// ----------------------------------------------------------------------------
// Purpose - GraphL Class is a graphing Depth-first project. This project reads 
// a data file that consists of many lines in order to display the graph 
// information and implement depth-first with the search always starts at node1
// In this project data32.txt was used as sample. The first line tells the 
// number of nodes followed by a text description of each of the nodes, 1 
// through n nodes. One description per line and each line consists of 2 
// integers that represent an edge. A zero for the first integer means the data
// for that graph has come to an end. In the file, all edges for the 1st node 
// are listed first after, all edges for the 2nd node, and so on. Each graph 
// has at most a max of 100 nodes. Lastly, the Edges in input are shown in a 
// reverse order in the output. Adjacency list used for graph implementation.
// Supporting data types are in GraphNode, edgeHead points to head of a list of
// EdgeNode. EdgeNode store the edge's info. visited marks whether node was
// visited, data is pointer to NodeData and has information on this GraphNode. 
// ----------------------------------------------------------------------------
// Special Notes and Assumptions - Assumed that all data will be accurate and 
// correct so that there is no need for special error handling. Assumed that
// the input data file has correctly formatted and valid data in it.
//-----------------------------------------------------------------------------

#include "graphl.h"
#include <iomanip>

// ------------------------  Default Constructor ------------------------------
// Default Constructor creates empty and sets size to 0. arr at i initializes 
// visited to false, edgeHead is set to NULL and the data is also set to NULL.
// ----------------------------------------------------------------------------
GraphL::GraphL()
{
	size = 0; // size set to 0

	for (int i = 1; i < MAXNODES_L; i++)
	{
		arr[i].visited = false; // marks not visited
		arr[i].edgeHead = NULL; // edgeHead set to NULL
		arr[i].data = NULL;	// data at i set to NULL
	}
}

// ------------------------  Deconstructor ------------------------------------
// Deconstructor uses a helper function, eraseGraphL to clear everything 
// delete the object, and set everything to default values, marking visited 
// to false and data to NULL.
// ----------------------------------------------------------------------------
GraphL::~GraphL()
{
	eraseGraphL(); // helper function
	size = 0;
}

// ------------------------ buildGraph ----------------------------------------
// buildGraph function builds builds up graph node information and adjacency
// list of edges between each node reading from a data file. Clearing first,
// then reading in the text file. While infile2, fromNode and toNode, if 
// fromNode and toNode are 0 then breaks else uses helper function
// insertEdgeL to insert data read from text file.
// ----------------------------------------------------------------------------
void GraphL::buildGraph(ifstream &infile2)
{
	eraseGraphL(); // helper function to clear first

	int fromNode = 0; // fromNode and toNode set to 0
	int toNode = 0;

	infile2 >> size; // reading

	if (infile2.eof()) // returns if infile is end of file
	{
		return;
	}

	string l;
	getline(infile2, l); // reads line from infile2 

	for (int i = 1; i <= size; i++)
	{
		getline(infile2, l); // gets line
		NodeData* tmp = new NodeData(l); // sets into NodeData tmp
		arr[i].data = tmp; // tmp set into array at i data
	}

	while (infile2 >> fromNode >> toNode) // for filling the linked list
	{ // if fromNode and toNode are 0 it breaks else inserts from file
		if (fromNode == 0 || toNode == 0)
		{
			break; // breaks
		}

		insertEdgeL(fromNode, toNode); // insert helper function
	}
}

// ------------------------ insertEdgeL ---------------------------------------
// insertEdgeL function inserts fromNode 'fNode' and toNode 'tNode' parameters 
// into the array of linked lists in correct position. Takes in two paramteres:
// and int and another int.
// ----------------------------------------------------------------------------
void GraphL::insertEdgeL(int fNode, int tNode)
{
	EdgeNode *newEN = new EdgeNode; // new node, edgenode made
	newEN->adjGraphNode = tNode; // adj node set 

	if (arr[fNode].edgeHead == NULL)
	{	// if the list is NULL or empty new edge is set by connecting with head
		arr[fNode].edgeHead = newEN; // head set to new node
		arr[fNode].edgeHead->nextEdge = NULL;
	}

	else // else if list is not empty
	{	// head is connected to new node edge and linked to orinal
		newEN->nextEdge = arr[fNode].edgeHead;
		arr[fNode].edgeHead = newEN;
	}
}

// --------------------- depthFirstSearch -------------------------------------
// depthFirstSearch function makes a depth-first search and displays each node
// in depth-first order. Uses dfs as a helper function to perform the search.
// ----------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";	// cout title

	for (int v = 1; v <= size; v++) // goes through entire size
	{
		if (arr[v].visited == false) // if visited is false node not visited
		{
			dfs(v); // helper function
		}
	}
	cout << endl << endl; // helps for spacing

	for (int v = 1; v <= size; v++)
	{
		arr[v].visited = false;	// resets to false so it can be re-used
	}
}

// --------------------- dfs --------------------------------------------------
// dfs function is a helper function for depthFirstSearch. Takes in one 
// parameter of int for the source node index.
// ----------------------------------------------------------------------------
void GraphL::dfs(int v)
{
	cout << v << " "; // prints the source node
	arr[v].visited = true; // sets to visited

	EdgeNode *tmpE = arr[v].edgeHead; // tmpE is head

	while (tmpE != NULL)
	{	// if adj graph node is not visited
		if (arr[tmpE->adjGraphNode].visited == false)
		{
			dfs(tmpE->adjGraphNode); // helper fuction to go to adj node
		}

		tmpE = tmpE->nextEdge; // moves pointer to next node
	}
}

// --------------------- displayGraph -----------------------------------------
// displayGraph function displays each node information (name of Node) and edge 
// source as well as the adj graph node in the graph.
// ----------------------------------------------------------------------------
void GraphL::displayGraph()
{
	cout << "Graph: " << endl; // printe title graph

	for (int i = 1; i <= size; i++) // goes through entire size
	{
		// prints out the node and its data
		cout << "Node" << i << "       " << *arr[i].data << endl;

		EdgeNode *edgeNodeCurr = arr[i].edgeHead; // new node to start at head

		while (edgeNodeCurr != NULL) // while it isnt NULL
		{	
			// prints out the edge and its adj graph node
		cout << "  edge " << i << " " << edgeNodeCurr->adjGraphNode << endl;
		edgeNodeCurr = edgeNodeCurr->nextEdge; // moves onto next node
		}
	}

	cout << endl; // for spacing
}

// --------------------- eraseGraphL ------------------------------------------
// eraseGraphL functions is a helper function for the Destructor that deletes
// the object.
// ----------------------------------------------------------------------------
void GraphL::eraseGraphL()
{
	for (int i = 1; i <= size; i++) // goes through entire size
	{
		while (arr[i].edgeHead != NULL) // while not NULL
		{
			EdgeNode* newHead = arr[i].edgeHead->nextEdge;
			delete arr[i].edgeHead; // deletes arr at i
			arr[i].edgeHead = newHead;
		}

		delete arr[i].data; // deletes arr at i edge name
		arr[i].data = NULL; // sets to NULL
		arr[i].visited = false; // sets as unvisited
	}
}

