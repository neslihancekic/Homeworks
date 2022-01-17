/*NESLÝHAN ÇEKÝÇ
 150160060
 FINAL PROJECT
 compile: g++ -std=c++11 -Wall -Werror q2.cpp -o q2
 run: ./q2 test.txt */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int min(int a, int b) {
	if (b < a) {
		return b;
	}
	else {
		return a;
	}

}
class Graph {
	vector <vector<int>> capacity;
	vector <vector<int>> flow;
	int nodeCount;
	vector <int> excess;
	vector <int> height;
public:
	void addCapacity(int, int, int);
	void push(int, int);
	void relabel(int);
	void initializePreflow(int);
	int overflowingVertex();
	int findMaxFlow();
	Graph(int);
	~Graph();
};

Graph::Graph(int n) {
	nodeCount = n;
	capacity.assign(nodeCount, vector<int>(nodeCount, 0));
}

void Graph::addCapacity(int from, int to, int cap) {
	capacity[from][to] = cap;
}


int Graph::overflowingVertex() {

	for (unsigned int i = 0; i < excess.size() - 1; i++) {
		if (excess[i] > 0) {
			return i;
		}
	}
	// -1 if no overflowing Vertex 
	return -1;

}

void Graph::initializePreflow(int source) {
	for (int i = source; i < nodeCount; i++) {
		height.push_back(0);
		excess.push_back(0);
	}


	flow.assign(nodeCount, vector<int>(nodeCount, 0));

	height[source] = nodeCount;

	for (unsigned int i = 0; i < capacity[source].size(); i++) {
		flow[source][i] = capacity[source][i];
		flow[i][source] = -capacity[source][i];
		excess[i] = capacity[source][i];
		excess[source] -= capacity[source][i];
	}



}

void Graph::push(int u, int v) {
	//u overflowing vertex,when cf>0 and u.h > v.h : do push
	int delta = min(excess[u], capacity[u][v] - flow[u][v]);
	flow[u][v] += delta;
	flow[v][u] -= delta;
	excess[u] -= delta;
	excess[v] += delta;


}

void Graph::relabel(int u) {
	//u overflowing vertex,when cf>0 and u.h <= v.h : do relabel
	int minimum = height[0];

	for (unsigned int i = 0; i < capacity[u].size(); i++) {
		if (capacity[u][i] - flow[u][i] > 0) {

			minimum = min(minimum, height[i]);

		}
	}

	height[u] = minimum + 1;

}

int Graph::findMaxFlow() {
	vector<int> seen; //for keeping the nodes are traverse all other nodes and there is no aplicable op. left
	
	seen.assign(nodeCount, 0);

	while (overflowingVertex() != -1) //do this loop until no overflowingvertex left
	{
		int u = overflowingVertex();
		if (seen[u] == nodeCount) u++; //if seen is equal to nodecount than do operations in next node

		for (int v = 0; v < nodeCount; v++) {
			
			if (height[u] > height[v] && capacity[u][v] - flow[u][v] >= 0) {
				push(u, v);
			}
			else if (height[u] <= height[v]) {
				relabel(u);
				seen[u]++; //increase seen value for each traveling to other nodes
				if (seen[u] == nodeCount) seen[u - 1] = 0; //if current node done with its op. turn back to previous node
			}
			

		}



	}

	return excess.back(); //last element in excess is max flow 
}

Graph::~Graph() {

}


int main(int argumentNumber, char *arguments[]){
    int nodeCount;
    string filename = arguments[1];
    string tempString;
    int from, to, flow;
    
    ifstream file;
    file.open(filename);
    file >> nodeCount;
    Graph graph(nodeCount);
    file >> tempString >> tempString >> tempString;
    while(file.good()){
        file >> from >> to >> flow;
        graph.addCapacity(from, to, flow);
    }
    graph.initializePreflow(0); // 0th node is source
    cout << "Maximum flow: " << graph.findMaxFlow() << endl; 
    return 0;
}
