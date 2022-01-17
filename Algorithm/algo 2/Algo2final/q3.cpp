/*NESLÝHAN ÇEKÝÇ
 150160060
 FINAL PROJECT
 compile: g++ -std=c++11 -Wall -Werror q3.cpp -o q3
 run: ./q3 q3_test1.txt */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <climits>
#include <string>

using namespace std;

struct Edge {
	int sourceNode;
	int destinationNode;
	int weight;
};

class Graph {
	int numberOfNodes;
	int numberOfEdges;
	vector<Edge> edges;

public:
	void setNumberOfNodes(int n) {
		numberOfNodes = n;
	}
	int getNumberOfNodes() {
		return numberOfNodes;
	}
	void setNumberOfEdges(int n) {
		numberOfEdges = n;
	}
	int getNumberOfEdges() {
		return numberOfEdges;
	}

	void AddEdge(int sourceNode, int destinationNode, int weight) {
		Edge e = Edge();
		e.sourceNode = sourceNode;
		e.destinationNode = destinationNode;
		e.weight = weight;

		edges.push_back(e);
	}
	vector<Edge> getAllEdges() {
		return edges;
	}

	vector<Edge> getOutgoingEdges(int src) {
		vector<Edge> outgoingEdges;

		for (Edge e : edges) {
			if (e.sourceNode == src) {
				outgoingEdges.push_back(e);
			}
		}

		return outgoingEdges;
	}

	int getWeightOfEdge(int src, int dst) {
		int weight = 0;
		for (Edge e : edges) {
			if (e.sourceNode == src && e.destinationNode == dst) {
				cout << "weigth: " << e.weight << endl;
				weight = e.weight;
			}
		}

		return weight;
	}

	void printGraph() {
		cout << "************* Graph data *************" << endl;
		cout << "Number of total edges: " << numberOfEdges << endl;
		cout << "Number of total nodes: " << numberOfNodes << endl << endl;

		cout << "Source node --> Destination node : Edge weigth" << endl;
		for (std::vector<Edge>::const_iterator i = edges.begin(); i != edges.end(); ++i) {
			std::cout << i->sourceNode << " --> ";
			std::cout << i->destinationNode << " : ";
			std::cout << setw(2) << i->weight << endl;
		}
		cout << "**************************************" << endl << endl;
	}
};

class BellmanFord {
	Graph G;
	int sourceNode;
	int destinationNode;
	int** M;
	bool graphContainsNegativeWeightCycle;

public:
	void setGraph(Graph g) {
		G = g;
	}
	Graph getGraph() {
		return G;
	}
	void setSourceNode(int s) {
		sourceNode = s;
	}
	int getSourceNode() {
		return sourceNode;
	}
	void setDestinationNode(int t) {
		destinationNode = t;
	}
	int getDestinationNode() {
		return destinationNode;
	}
	bool buildDPTable() {

		int numberOfNodes = G.getNumberOfNodes();
		int numberOfEdges = G.getNumberOfEdges();
		vector<Edge> edges = G.getAllEdges();

		//allocate space for DP table
		M = new int* [numberOfNodes];
		for (int i = 0; i < numberOfNodes; ++i) {
			M[i] = new int[numberOfNodes];
		}
		
		//Initialize DP Table
		for (int i = 0; i < numberOfNodes; ++i) {
			M[0][i] = INT_MAX; 
		}

		M[0][destinationNode] = 0; //
		
		for (int a = 0; a < numberOfNodes; a++) {
			M[1][a] = M[0][a];
		}
		


		for (int i = 1; i < numberOfNodes; i++) {
			for (int j = 0; j < numberOfEdges; j++) {
				int v = edges[j].sourceNode;
				int u = edges[j].destinationNode;
				int weight = edges[j].weight;
				if (M[i - 1][u] != INT_MAX && M[i - 1][u] + weight < M[i - 1][v]) {
					M[i][v] = M[i - 1][u] + weight;
					
				}
			}
			

			if (i + 1 != numberOfNodes) {
				for (int a = 0; a < numberOfNodes; a++) {
					M[i + 1][a] = M[i][a];
				}
			}
		}

		
		for (int i = 0; i < numberOfEdges; i++) {
			int v = edges[i].sourceNode;
			int u = edges[i].destinationNode;
			int weight = edges[i].weight;
			if (M[numberOfNodes-1][u] != INT_MAX && M[numberOfNodes-1][u] + weight < M[numberOfNodes-1][v]) {
				cout<<"Graph contains negative weight cycle."<<endl;
				return false;
			}
		}
		return true;



	}

	void printDPTable() {
		if (!graphContainsNegativeWeightCycle) {
			cout << endl << "Dynamic programming table: (shortest paths from each node to destination node): " << endl << endl;

			int numberOfNodes = G.getNumberOfNodes();

			for (int i = 0; i <= numberOfNodes; i++) {
				for (int j = 0; j <= numberOfNodes; j++) {
					if (i == 0 && j == 0)
						cout << "\t";
					else if (i != 0 && j == 0)
						cout << setw(10) << "Iteration-" << i - 1;
					else if (i == 0 && j != 0)
						cout << "\t" << "Node-" << j - 1 << " ";
					else {
						if (M[i - 1][j - 1] == INT_MAX)
							cout << "\t " << "\u221E";
						else
							cout << "\t" << setw(2) << M[i - 1][j - 1];
					}
				}
				cout << endl;
			}
			cout << endl;
		}
	}

	void printShortestPathBetweenSourceAndDestination() {
		int numberOfNodes = G.getNumberOfNodes();
		int numberOfEdges = G.getNumberOfEdges();
		vector<Edge> edges = G.getAllEdges();

		vector<pair<int,int>> *path =new vector<pair<int, int>>;

		int currentNode = sourceNode;

		cout << "Shortest path value from " << sourceNode << " to " << destinationNode << " : " << M[numberOfNodes - 1][sourceNode] << endl;
		cout << "Shortest path from " << sourceNode << " to " << destinationNode << " : ";
		for (int i = numberOfNodes-1; i >= 1; i--) {
			for (int j = numberOfEdges-1; j >= 0; j--) {
				int v = edges[j].sourceNode;
				int u = edges[j].destinationNode;
				int weight = edges[j].weight;
				if (M[i][u] + weight == M[i][v]) {
					M[i-1][v] = M[i][u] - weight;
					path->push_back(make_pair(v,u));
				}
			}

		}
		for (int i = 0; i < numberOfEdges; i++) {
			if (currentNode == path->at(i).first) {
				cout << path->at(i).first << " -> ";
				currentNode = path->at(i).second;
				i = 0;
			}
		}

		cout << destinationNode<<endl;

	}
};

int main(int argc, char* argv[])
{
    if(argc > 1){
        Graph graph;
        
        //read graph data from file
        string inputFileName = argv[1];
        string line;
        ifstream infile(inputFileName);
        
        getline(infile, line);
        graph.setNumberOfNodes(stoi(line));
        getline(infile, line);
        graph.setNumberOfEdges(stoi(line));

        int src, dst, w;
        while (infile >> src >> dst >> w) {
           graph.AddEdge(src, dst, w);
        }
        
        graph.printGraph();
        
        BellmanFord bf;
        bf.setGraph(graph);
        
        int dstNode;
        int srcNode;
        
        cout << "Enter the destination node: ";
        cin >> dstNode;
        
        bf.setDestinationNode(dstNode);
    
        if(bf.buildDPTable()){
            bf.printDPTable();
            
            cout << "Enter a source node: ";
            cin >> srcNode;
            bf.setSourceNode(srcNode);
            
            bf.printShortestPathBetweenSourceAndDestination();
        }
    }
    else{
        cout << "Error: please provide a test file!" << endl;
    }
    
    return 0;
}
