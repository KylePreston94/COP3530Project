#pragma once
#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include <queue>
#include <vector>
#include "graph.h"
#include <stack>;
#include <map>
#include<unordered_map>


class Map
{
public:
	Map(ifstream& fin);
	
	void print(int, int);
	bool isLegal(int i, int j);
	void setMap(int i, int j, int n);
	int getMap(int i, int j) const;
	//int getReverseMapI(int n) const;
	//int getReverseMapJ(int n) const;
	void mapToGraph(graph& g);
	bool findPathRecursive(graph& g, stack<int>& moves);
	bool findPathNonRecursive1(graph& g, stack<int>& moves);
	bool findPathNonRecursive2(graph& g, queue<int>& moves);
	bool findShortestPath1(graph& g, stack<int>& bestMoves);
	bool findShortestPath2(graph& g, vector<int>& bestMoves);
	void printPath(stack<int>& s);
	int numRows() { return rows; };
	int numCols() { return cols; };
private:
	int rows; // number of latitudes/rows in the map
	int cols; // number of longitudes/columns in the map
	 
	matrix<bool> value;
	matrix<int> mapping; // Mapping from latitude and longitude co-ordinates (i,j) values to node index values
	vector<int> reverseMapI; // Mapping from node index values to map latitude i value
	vector<int> reverseMapJ; // Mapping from node index values to map longitude j value
};

Map::Map(ifstream& fin) {
	fin >> rows;
	fin >> cols;
	mapping = matrix<int>(rows, cols, 0);
	value = matrix<bool>(rows, cols, false);
	char mapValue;

	for (int x = 0; x < rows; x++) {

		for (int y = 0; y < cols; y++) {
			fin >> mapValue;
			value[x][y] = mapValue == 'X' ? 1 : 0;
		}
	}
};
void Map::print(int carRow, int carColumn) {
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			if (x == carRow && y == carColumn)
				::cout << "M";
			else if (value[x][y] == 0)
				::cout << "O";
			else
				::cout << "X";

		}
		::cout << "\n";

	}

}
bool Map::isLegal(int i, int j){
	
		if (i >= rows || j >= cols) {
			return false;
		}
		if (i < 0 || j < 0) {
			return false;
		}
		bool legal = value[i][j] == 0;
		return legal;
	}


void Map::mapToGraph(graph& g){

	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++){
		
			g.addNode();
		}
	}

	for (int x = 0; x < rows; x++){
	
		for (int y = 0; y < cols; y++){		
			if (value[x][y] == 0 && isLegal(x - 1, y)){			
				g.addEdge((x - 1) * cols + y, x * cols + y);
				g.addEdge(x * cols + y, (x - 1) * cols + y);
			}
			if (value[x][y] == 0 && isLegal(x, y - 1)){
				g.addEdge(x * cols + y - 1, x * cols + y);
				g.addEdge(x * cols + y, x * cols + y - 1);
			}
			if (value[x][y] == 0 && isLegal(x + 1, y)){			
				g.addEdge((x + 1) * cols + y, x * cols + y);
				g.addEdge(x * cols + y, (x + 1) * cols + y);
			}
			if (value[x][y] == 0 && isLegal(x, y + 1)){			
				g.addEdge(x * cols + y + 1, x * cols + y);
				g.addEdge(x * cols + y, x * cols + y + 1);
			}

		}
	}
}

void Map::printPath(stack<int>& s) {
	int size = s.size();
	vector<int> path;	
	int i = 0;
	
	while(!s.empty()){
		path.push_back(s.top());
		s.pop();
		i++;

	}
	for (int i = size -1; i >= 1; i--) {
		int first = path[i];		
		int second = path[i - 1];		
		if (i == 1) {
			print(first / cols, (first % cols));
			print(second / cols, (second % cols));
		}
		else {
			print(first / cols, (first % cols));
		}
		::cout << "\n";
		if (second == first +1) {
			::cout<<"Go Right\n";

		}
		else if (second == first-1) {
			::cout<<"Go Left\n";

		}
		else if (second==first +cols) {
			::cout<<"Go Down\n";

		}
		else {
			::cout<<"Go Up\n";
		}

	}
	
}

bool Map::findPathRecursive(graph& g, stack<int>& moves) {
	
	
	int vertex = moves.top();
	g.visit(vertex);
	int size = moves.size();
	if (vertex == rows * cols - 1) {
		printPath(moves);
		::cout << endl;
		return true;

	}
			
	for (int j = 0; j < g.numNodes(); j++) {		
		if (g.isEdge(vertex, j)) {						
			if (g.isVisited(j)!=1) {
				moves.push(j);
				if (findPathRecursive(g, moves)) {
					return true;
				}
				else {
					moves.pop();
				}
			}
			
		}
	}
	//cout << "No possible path";
	return false;
}

//USE DEPTH FIRST SEARCH
bool Map::findPathNonRecursive1(graph& g, stack<int>& moves)
{
	int size = moves.size();
	moves.push(0);
	int vertex = moves.top();
	unordered_map<int, int> pairs;

	while (!moves.empty())
	{
		vertex = moves.top();
		g.visit(vertex);
		if (vertex == rows * cols - 1)
		{
			stack<int> path;
			stack<int> path2;
			int current = vertex;
			while (current != 0)
			{
				path.push(current);
				current = pairs[current];
			}
			while (!path.empty()) {
				path2.push(path.top());
				path.pop();
			}


			printPath(path2);
			return true;
		}
		for (int j = 0; j < g.numNodes(); j++)
		{
			if (g.isEdge(vertex, j))
			{
				if (g.isVisited(j) != 1)
				{
					moves.push(j);
					pairs[j] = vertex;
				}
				else
				{
					moves.pop();
				}
			}
		}
	}
	cout << "No path exists.\n";
	return false;
}
//USE BREADTH FIRST SEARCH


bool Map::findPathNonRecursive2(graph & g, queue<int>&moves) {
	int size = moves.size();
	moves.push(0);
	int vertex = moves.front();
	unordered_map<int, int> pairs;

	while (!moves.empty())
	{
		vertex = moves.front();
		g.visit(vertex);
		moves.pop();
		if (vertex == rows * cols - 1)
		{
			stack<int> path;
			stack<int> path2;
			int current = vertex;
			while (current != 0)
			{
				path.push(current);
				current = pairs[current];
			}
			while (!path.empty()) {
				path2.push(path.top());
				path.pop();
			}


			printPath(path2);
			return true;
		}
		for (int j = 0; j < g.numNodes(); j++)
		{
			if (g.isEdge(vertex, j))
			{
				if (g.isVisited(j) != 1)
				{
					moves.push(j);
					pairs[j] = vertex;

				}
				
			}
		}
	}
	cout << "No path exists.\n";
	return false;
}

int indexOfLowest(vector<int>& options, vector<int>& distances) {
	int min_distance = INT_MAX;
	int min_dist_index = -1;
	for (int i = 0; i < options.size(); i++) {
		int option = options[i];
		if (distances[option] < min_distance) {
			min_distance = distances[option];
			min_dist_index = option;
		}
	}
	return min_dist_index;
}

//DIJKSTRA'S ALGORITHM
bool Map::findShortestPath1(graph& g, stack<int>& bestMoves){
	vector<int> Sp, Parent, Q;
	Sp.resize(g.numNodes());
	Parent.resize(g.numNodes());
	for (int i = 0; i < g.numNodes(); i++) {
		Sp[i] = 9999;
		Parent[i] = -1;
		Q.push_back(i);

	}
	//assume starting point is 0
	Sp[0] = 0;

	while (!Q.empty()) {
		int current = indexOfLowest(Q, Sp);

		if (current == rows * cols - 1) {
			stack<int> reversePath;
			reversePath.push(current);
			while (Parent[current] != -1) {
				current = Parent[current];
				reversePath.push(current);
			}
			//reverse stack
			while (!reversePath.empty()) {
				int item = reversePath.top();
				reversePath.pop();
				bestMoves.push(item);

			}
			printPath(bestMoves);

			return true;
			


		}
		//remove current from Q
		for (int i = 0; i < Q.size(); i++) {
			if (Q[i] == current) {
				Q.erase(Q.begin() + i);
				break;

			}
		}
		for (int i = 0; i < g.numNodes(); i++) {
			if (g.isEdge(current, i) && find(Q.begin(), Q.end(), i) != Q.end()) {
				//assume edges have a weight of 1
				int alt = Sp[current] + 1;
				if (alt < Sp[i]) {
					Sp[i] = alt;
					Parent[i] = current;

				}
			}
		}
	}


	return false;

}

//BELLMAN-FORD
bool Map::findShortestPath2(graph& g, vector<int>& bestMoves) {
	vector<int> Sp, Parent, Q;
	Sp.resize(g.numNodes());
	Parent.resize(g.numNodes());
	for (int i = 0; i < g.numNodes(); i++) {
		Sp[i] = INT_MAX;
		Parent[i] = -1;
		Q.push_back(i);

	}
	//assume starting point is 0
	Sp[0] = 0;
	for (int i = 0; i < g.numNodes(); i++) {
		for (int j = 0; j < g.numNodes(); j++) {
			if (g.isEdge(i, j)) {
				if (Sp[j] > Sp[i] + 1 && Sp[i]!= INT_MAX) {
					Sp[j] = Sp[i] + 1;
					Parent[j] = i;
				}
			}
		}
	}
	stack<int> printStack;
	stack<int> reverseAgain;
	int current = rows * cols - 1;
	::cout << g.numNodes();
	while (Parent[current] != -1) {
		reverseAgain.push(Parent[current]);
		current = Parent[current];
	}
	while (!reverseAgain.empty()) {
		int item = reverseAgain.top();
		reverseAgain.pop();
		printStack.push(item);

	}
	printPath(printStack);
	return true;


}