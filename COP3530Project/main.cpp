//Kyle Preston
//COP3530 Spring 2022
//Project part 1
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
#include "map.h"
#include <string>


using namespace std;


int main() {
	ifstream readFile;
	string fileName;
	string input;
	readFile.open("map1.txt");
	Map islandMap(readFile);
	
	graph g;
	graph g2;
	graph g3;
	stack<int> moves;
	queue<int> move;
	stack<int> bestMoves;
	vector<int> bestMove;
	
	
//make the graph from the map1 textfile
	islandMap.mapToGraph(g);
	//moves.push(0);
	g.clearVisit();

	//::cout << "Recursive path \n";
	//islandMap.findPathRecursive(g, moves);
	//g.clearVisit();
	//::cout << "Non recursive\n";
	//islandMap.findPathNonRecursive1(g,moves);
	//g.clearVisit();
	//::cout << "Non Recursive 2\n";
	//islandMap.findPathNonRecursive2(g,move);
	//::cout << "Shortest Path Dijkstra's\n";
	//islandMap.findShortestPath1(g, bestMoves);
	//g.clearVisit();
	::cout << "Shortest Path Bellman \n";
	islandMap.findShortestPath2(g, bestMove);
	
	
	readFile.close();
	
	//Open map 2
	readFile.open("map2.txt");
	Map islandMap2(readFile);
	//Graph map 2
	islandMap2.mapToGraph(g2);
	moves = stack<int>();
	//moves.push(0);
	g.clearVisit();

	//::cout << "Recursive path \n";
	//islandMap2.findPathRecursive(g, moves);
	//g.clearVisit();
	//::cout << "Non recursive\n";
	// Failed to run
	//islandMap2.findPathNonRecursive1(g, moves);
	//g.clearVisit();
	//::cout << "Non Recursive 2\n";
	// Failed to run
	//islandMap2.findPathNonRecursive2(g, move);
	//::cout << "Shortest Path Dijkstra's\n";
	//islandMap2.findShortestPath1(g, bestMoves);
	//g.clearVisit();
	::cout << "Shortest Path Bellman \n";
	islandMap2.findShortestPath2(g2, bestMove);

	readFile.close();
	

	readFile.open("map3.txt");
	Map islandMap3(readFile);
	islandMap3.mapToGraph(g3);
	moves = stack<int>();
	//moves.push(0);
	//g.clearVisit();
	//islandMap3.findPathRecursive(g, moves);
	//failed to run
	//islandMap3.findPathNonrecursive1(g,moves);
	//g.clearVisit();
	//failed to run
	//islandMap3.findPathNonrecursive2(g,move);
	//::cout << "Shortest Path Dijkstra's\n";
	//islandMap3.findShortestPath1(g, bestMoves);
	//g.clearVisit();
	//::cout << "Shortest Path Bellman \n";
	//islandMap3.findShortestPath2(g, bestMove);
	
	readFile.close();
	
	
}