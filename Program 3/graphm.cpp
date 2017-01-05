// ------------------------------------- graphm.cpp --------------------------
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

#include "graphm.h"
#include <iomanip>

// ------------------------  Default Constructor ------------------------------
// Default Constructor creates empty table size 0, data T is initialized to
// visited set to false, distance to infinity and path to 0.
// ----------------------------------------------------------------------------
GraphM::GraphM()
{
	size = 0;	// size set to 0
	for (int i = 1; i < MAXNODES_M; i++)
	{
		for (int j = 1; j < MAXNODES_M; j++)
		{
			C[i][j] = INF; // infinity
			T[i][j].visited = false; // set to not visited
			T[i][j].dist = INF; // distance to infinity
			T[i][j].path = 0;	// path set to 0
		}
	}
}

// ------------------------ buildGraph ----------------------------------------
// buildGraph function builds up graph node information and adjacency matrix of 
// edges between each node reading from a data file, in this example data31.txt
// was used. This keeps going until fNode,tNode, and dist are equal to 0 in
// which then it breaks. Once they are read insertEdge function is called to 
// to insert the read data from text file.
// ----------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile1)
{
	//eraseGraphM();
	int fNode = 0; // from Node
	int tNode = 0; // to Node
	int dist = 0; // distance

	infile1 >> size; 

	string m;
	getline(infile1, m); // gets line from text

	for (int i = 1; i <= size; i++)
	{
		data[i].setData(infile1); // reads and set data in array
	}

	while (infile1 >> fNode >> tNode >> dist)
	{	// if from node, to node, and distance are 0 then breaks
		if (fNode == 0 && tNode == 0 && dist == 0)
		{
			break; // breaks since fNode,tNode,dist are 0
		}

		insertEdge(fNode, tNode, dist); // insert function for building
	}
}

// ------------------------ insertEdge ----------------------------------------
// insertEdge function inserts an edge into graph between two given nodes. 
// Taking in three parameters: from Node, to Node and dist
// ----------------------------------------------------------------------------
void GraphM::insertEdge(int fromN, int toN, int dist)
{
	C[fromN][toN] = dist; // cost array, the adj matrix
}

// ------------------------ removeEdge ----------------------------------------
// removeEdge function removes an edge between two given nodes. Taking in
// two parameters: from Node and to Node. Setting to INF which is infinite
// in order to remove edge
// ----------------------------------------------------------------------------
void GraphM::removeEdge(const int fromN, const int toN)
{
	C[fromN][toN] = INF; // cost array (adj matrix) set to infinite to remove
}

// ------------------------ findShortestPath ----------------------------------
// findShortestPath function finds shortest path between every node to every
// other node in the graph. Also TableType T is updated with the shortest path
// information by deciding the minnimum of the visited ones.
// ----------------------------------------------------------------------------
void GraphM::findShortestPath()
{
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0; // sets the dist to 0

		// shortest distance from source to all other nodes
		for (int i = 1; i <= size; i++) 
		{
			int v = findV(T[source], 1, size); // uses find function to find

			T[source][v].visited = true; // once found visited is true
			
			for (int w = 1; w <= size; w++)
			{	// if it is not visited and cost array is not equal to infinity
				if (T[source][w].visited == false && C[v][w] != INF)
				{ // check for the minimum
					if (!(T[source][w].dist < (T[source][v].dist + C[v][w])))
					{ // if minimum the assigns the new lowest
						T[source][w].dist = (T[source][v].dist + C[v][w]);
						T[source][w].path = v; // assigns v to path
					}
				}
			}
		}
	}
}

// ------------------------ findV ---------------------------------------------
// findV function check if not visited and shortest distance at this point, if
// so then assigns, else it doesn't assign the if it is not shortest. Takes in
// three parameters: TableType array, and two ints
// ----------------------------------------------------------------------------
int GraphM::findV(TableType data[], int l, int h)
{
	int v = 0; // start at 0
	int lVPath = INF; // set to infinity

	for (int i = 1; i <= size; i++)
	{	// for everything, if data isnt visited and lowest path is greater
		if (data[i].dist < lVPath && data[i].visited == false)
		{
			lVPath = data[i].dist; // new data at i is lowest path
			v = i; // assings i to v
		}
	}
	return v; // returns find
}

// ------------------------ display -------------------------------------------
// display function uses couts to display the shortest distance with the path 
// info of that distance between the fromNode 'from' to toNode 'to'. Unlike the
// displayALL which displays entire graph. Takes in two parameters: int and int
// uses two other functions as helpers, pathFinder and pathFinderData.
// ----------------------------------------------------------------------------
void GraphM::display(int from, int to)
{
	cout << from; // prints from first
	cout << "\t" << to << "\t"; // spacing using tabs and prints to

	if (T[from][to].dist == INF)
	{
		cout << "----"; // if the dist is infinite display ----
	}

	else // dist is not infinite
	{
		if (T[from][to].dist == 0)
		{
			cout << "----"; // if it is 0 then also display ----
		}

		else
		{
			cout << T[from][to].dist; // if dist isnt 0, displays it then
		}
	}

	if (T[from][to].path != 0)	// if path is not 0, meaning there is a path
	{
		cout << "\t" << from << " ";	// tabs for spacing and display from
		// uses path finder function to find the path from Node to another Node
		pathFinder(from, to);	
	}

	else
	{
		cout << "\t"; // tab for spacing
	}

	cout << endl; // for spacing lines

	if (T[from][to].path != 0)
	{	// if path is not 0 uses pathFinderData function to find data 
		pathFinderData(from, to);
	}

	cout << endl; // spacing
}

// ------------------------ pathFinder ----------------------------------------
// pathFinder function is used to find path for edge. Takes
// in two parameters: int and int
// ----------------------------------------------------------------------------
void GraphM::pathFinder(int fromNode, int toNode)
{

	if (T[fromNode][toNode].path != fromNode) // if path isnt equal to fromNode
	{
		pathFinder(fromNode, T[fromNode][toNode].path); // recursive call
	}
	cout << toNode << " "; // display toNode data
}

// ------------------------ pathFinderData ------------------------------------
// ipathFinderData function is used to find data for a edge distance. Takes
// in two parameters: int and int
// ----------------------------------------------------------------------------
void GraphM::pathFinderData(int fromNode, int toNode)
{
	if (fromNode == toNode) // if from node and to node are equal
	{
		cout << data[toNode] << endl; // prints array data 
		return;
	}

	if (T[fromNode][toNode].dist == INF) // if distance is infinite
	{
		return; // no path
	}

	pathFinderData(fromNode, T[fromNode][toNode].path); // recusive call

	cout << data[toNode] << endl; // prints arra[toNode] data
}

// ------------------------ displayAll ----------------------------------------
// displayAll function helps by using couts demonstrate that created algorithm
// is work properly. Prints out all the data unlike the display function.
// ----------------------------------------------------------------------------
void GraphM::displayAll()
{	// prints title of display
	cout << "Description\t\tFrom Node\tTo Node\t\tDijkstra's\tPath" << endl;

	for (int i = 1; i <= size; i++)
	{
		cout << data[i] << endl; // prints out data at all i the FromNode

		for (int j = 1; j <= size; j++)
		{
			if (i == j) // if i and j are same continues
				continue;

			cout << "\t\t\t" << i; // multi-tabs for correct spacing, prints i

			cout << "\t\t" << j << "\t\t"; // prints j, the toNode

			if (T[i][j].dist == 0)
			{
				cout << "----"; // prints ---- if distance is 0
			}

			else
			{	// if distance is not 0 prints the distance
				cout << T[i][j].dist;
			}

			if (T[i][j].dist != 0)
			{	// if dist is not 0 uses pathFinder helper function
				cout << "\t\t" << i << " "; // printe i, fromNode
				pathFinder(i, j);
			}

			else
			{
				cout << "\t\t"; // tabs for spacing help
			}

			cout << endl; // line spacing help
		}
	}

	cout << endl << endl;
}

// ------------------------ eraseGraphM ---------------------------------------
// eraseGraph function resets table to help again construct an empty table with
// size set to 0 and TableType t visited set to false, dist to infinity, and
// path to 0.
// ----------------------------------------------------------------------------
void GraphM::eraseGraphM()
{
	for (int i = 1; i < MAXNODES_M; i++)
	{
		for (int j = 1; j < MAXNODES_M; j++)
		{
			C[i][j] = INF;
			T[i][j].visited = false; // sets to not visited
			T[i][j].dist = INF; // to infinity
			T[i][j].path = 0; // path set to 0
		}
	}
	size = 0;	// size set
}
