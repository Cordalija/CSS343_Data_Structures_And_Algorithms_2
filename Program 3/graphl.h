// ------------------------------------- graphl.h -----------------------------
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
#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;

int const MAXNODES_L = 101; // max nodes

class GraphL
{

public:
// ------------------------  Default Constructor ------------------------------
// Default Constructor creates empty and sets size to 0. arr at i initializes 
// visited to false, edgeHead is set to NULL and the data is also set to NULL.
// ----------------------------------------------------------------------------
	GraphL();

// ------------------------  Deconstructor ------------------------------------
// Deconstructor uses a helper function, eraseGraphL to clear everything 
// delete the object, and set everything to default values, marking visited 
// to false and data to NULL.
// ----------------------------------------------------------------------------
	~GraphL();

// ------------------------ buildGraph ----------------------------------------
// buildGraph function builds builds up graph node information and adjacency
// list of edges between each node reading from a data file. Clearing first,
// then reading in the text file. While infile2, fromNode and toNode, if 
// fromNode and toNode are 0 then breaks else uses helper function
// insertEdgeL to insert data read from text file.
// ----------------------------------------------------------------------------
	void buildGraph(ifstream&);

// --------------------- depthFirstSearch -------------------------------------
// depthFirstSearch function makes a depth-first search and displays each node
// in depth-first order. Uses dfs as a helper function to perform the search.
// ----------------------------------------------------------------------------
	void depthFirstSearch();

// --------------------- displayGraph -----------------------------------------
// displayGraph function displays each node information (name of Node) and edge 
// source as well as the adj graph node in the graph.
// ----------------------------------------------------------------------------
	void displayGraph();


private:

	int size;

	struct EdgeNode;      // forward reference for the compiler

	struct GraphNode
	{    // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // data information about each node
		bool visited;
	};

	GraphNode arr[MAXNODES_L];

	struct EdgeNode
	{
		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};

// --------------------- eraseGraphL ------------------------------------------
// eraseGraphL functions is a helper function for the Destructor that deletes
// the object.
// ----------------------------------------------------------------------------
	void eraseGraphL();

// --------------------- dfs --------------------------------------------------
// dfs function is a helper function for depthFirstSearch. Takes in one 
// parameter of int for the source node index.
// ----------------------------------------------------------------------------
	void dfs(int);

// ------------------------ insertEdgeL ---------------------------------------
// insertEdgeL function inserts fromNode 'fNode' and toNode 'tNode' parameters 
// into the array of linked lists in correct position. Takes in two paramteres:
// and int and another int.
// ----------------------------------------------------------------------------
	void insertEdgeL(int, int);

};
#endif
