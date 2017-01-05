// ------------------------------------- graphm.h -----------------------------
// Programmer: Jasenko Cordalija. 
// Course Number: CS343A.
// Creation Date: 02/10/2016
// Date of Last Modification: 02/16/2016
// ----------------------------------------------------------------------------
// Purpose - GraphM Class is a graphing Dijkstra project, finding the shortest
// path. This project reads a data file that consists of many lines in order to
// find the shortest path between locations in the text file, in this project 
// data31.txt was used as sample. GraphM will be able to find the lowest paths
// cost using findShortestPath function and display the cost and path from 
// node to every other node using the displayAll function. Another display 
// function titled display, will output one path in detail. TableType is a 
// struct in the project to keep the current shortest distance
// known at any point in algorithm.
// ----------------------------------------------------------------------------
// Special Notes and Assumptions - Assumed that all data will be accurate and 
// correct so that there is no need for special error handling. Assumed that
// the input data file has correctly formatted and valid data in it.
//-----------------------------------------------------------------------------
#ifndef GRAPHM_H 
#define GRAPHM_H
#define INF 2147483647

#include <fstream>
#include <iostream>
#include "nodedata.h"

using namespace std;

int const MAXNODES_M = 101; // max node set

class GraphM
{

public:

// ------------------------  Default Constructor ------------------------------
// Default Constructor creates empty table size 0, data T is initialized to
// visited set to false, distance to infinity and path to 0.
// ----------------------------------------------------------------------------
	GraphM();

// ------------------------ buildGraph ----------------------------------------
// buildGraph function builds up graph node information and adjacency matrix of 
// edges between each node reading from a data file, in this example data31.txt
// was used. This keeps going until fNode,tNode, and dist are equal to 0 in
// which then it breaks. Once they are read insertEdge function is called to 
// to insert the read data from text file.
// ----------------------------------------------------------------------------
	void buildGraph(ifstream&);

// ------------------------ insertEdge ----------------------------------------
// insertEdge function inserts an edge into graph between two given nodes. 
// Taking in three parameters: from Node, to Node and dist
// ----------------------------------------------------------------------------
	void insertEdge(int, int, int);

// ------------------------ removeEdge ----------------------------------------
// removeEdge function removes an edge between two given nodes. Taking in
// two parameters: from Node and to Node. Setting to INF which is infinite
// in order to remove edge
// ----------------------------------------------------------------------------
	void removeEdge(int, int); 

// ------------------------ findShortestPath ----------------------------------
// findShortestPath function finds shortest path between every node to every
// other node in the graph. Also TableType T is updated with the shortest path
// information by deciding the minnimum of the visited ones.
// ----------------------------------------------------------------------------
	void findShortestPath();

// ------------------------ display -------------------------------------------
// display function uses couts to display the shortest distance with the path 
// info of that distance between the fromNode 'from' to toNode 'to'. Unlike the
// displayALL which displays entire graph. Takes in two parameters: int and int
// uses two other functions as helpers, pathFinder and pathFinderData.
// ----------------------------------------------------------------------------
	void display(int, int);

// ------------------------ displayAll ----------------------------------------
// displayAll function helps by using couts demonstrate that created algorithm
// is work properly. Prints out all the data unlike the display function.
// ----------------------------------------------------------------------------
	void displayAll();

private:

	struct TableType
	{
		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist
	};

	NodeData data[MAXNODES_M];              // data for graph nodes 
	int C[MAXNODES_M][MAXNODES_M];            // Cost array, adjacency matrix
	int size;                             // number of nodes in the graph
	TableType T[MAXNODES_M][MAXNODES_M];     // stores visited, distance, path


// ------------------------ pathFinder ----------------------------------------
// pathFinder function is used to find path for edge. Takes
// in two parameters: int and int
// ----------------------------------------------------------------------------
	void pathFinder(int, int);

// ------------------------ pathFinderData ------------------------------------
// ipathFinderData function is used to find data for a edge distance. Takes
// in two parameters: int and int
// ----------------------------------------------------------------------------
	void pathFinderData(int, int);

// ------------------------ findV ---------------------------------------------
// findV function check if not visited and shortest distance at this point, if
// so then assigns, else it doesn't assign the if it is not shortest. Takes in
// three parameters: TableType array, and two ints
// ----------------------------------------------------------------------------
	int findV(TableType[], int, int);

// ------------------------ eraseGraphM ---------------------------------------
// eraseGraph function resets table to help again construct an empty table with
// size set to 0 and TableType t visited set to false, dist to infinity, and
// path to 0.
// ----------------------------------------------------------------------------
	void eraseGraphM();

};
#endif
