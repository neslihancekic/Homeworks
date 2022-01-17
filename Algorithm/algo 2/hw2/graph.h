/********************************************
*               Neslihan Çekiç              *
*				  150160060			        *
*			     AoA2 - HW2                 *
*********************************************/

#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>

using namespace std;

class Edge { //Hold the edges info for creating graph
	int source;
	int dest;
	int weight;
public:
	Edge(int s, int d, int w) { //Edge Constructer
		source = s;
		dest = d;
		weight = w;
	}
	/*Getter Methods*/
	int getSrc() { return source; }
	int getDest() { return dest; }
	int getW() { return weight; }
};

class Graph {

	vector<vector<pair<int, int>>> adjList; //Creating vector of vectors of pair(for holdingdest and weight)
	int node; //total node count of graph

public:
	Graph(vector<Edge> e, int node_count) {
		node = node_count;
		adjList.resize(node_count); //Declare total node count of graph

		for (auto i = e.begin(); i != e.end(); ++i) { //Adding edge infos to nodes and add those node to adjList

			adjList[(*i).getSrc()].push_back(make_pair((*i).getDest(), (*i).getW()));
		}
	}
	

	vector<vector<pair<int, int>>> getAdj() { return adjList; } //Getter method for adj list
	int getNode() { return node; } //Getter method for node count
};

class Path { //To hold path info
public:
	int parent; //the node info 
	int time; // time to going that node

	Path(int p, int t) {
		parent = p;
		time = t;
	}
	void setParent(int p, int t) {
		parent = p;
		time = t;
	}
	
};
#endif