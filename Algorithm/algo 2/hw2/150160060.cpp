/********************************************
*               Neslihan Çekiç              *
*				  150160060			        *								
*			     AoA2 - HW2                 *
*********************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <limits.h>
#include "graph.h"

using namespace std;

//Printing Path (Node,Time)
void printPath(vector<Path> e) { 
	for (auto i = e.begin(); i != e.end(); ++i) {
		cout << "Node: " << (*i).parent << " Time: " << (*i).time << endl;
	}
} 
//Printing Final Result (J's and L's paths)
void PrintResult(vector<Path> JGo, vector<Path> JReturn, vector<Path> LGo, vector<Path> LReturn) { //Print all paths 

	cout << "Joseph's Path, duration: " << JReturn.back().time << endl;
	printPath(JGo);
	cout << "-- return --" << endl;
	printPath(JReturn);
	cout << endl << "Lucy's Path, duration: " << LReturn.back().time << endl;
	printPath(LGo);
	cout << "-- return --" << endl;
	printPath(LReturn);

}

//Creating paths compatible of homework
void createPath(vector<Path> parent, int j, vector<Path>& path) //Creating Smallest Path
{
	// Base Case : If j is source 
	if (parent[j].parent == -1) {
		Path* p = new Path(j, parent[j].time);
		path.push_back(*p);
		return;
	}

	createPath(parent, parent[j].parent, path); //Recursive Function call
	Path* p = new Path(j, parent[j].time);  //Creating Path that has its node and its cost
	path.push_back(*p); //push path to vector that we created in dijkstra function

}

//Dijkstra algorithm 
//src->source node
//dst->destination node
//cost->starting cost
//forbidden->forbidden node for collision(forbidden==-1->no forbidden node)
vector<Path> dijkstra(Graph graph, int src, int dst, int cost, int forbidden)//find all smallest paths
{
	vector<int> dist;     //Holds distance between source-destination
	vector<bool> visited;  //Holds if the node visited or not
	vector<Path> parent;   //Holds node's parent infos(node and weight)

	vector<vector<pair<int, int>>> List = graph.getAdj();  //Graph

	int V = graph.getNode();//Graph's total node count

	

	Path *t=new Path(-1, cost); //Creating initial parent info (-1 means node hasn't got a parent, and cost represent the starting cost of the path

	//Marking all nodes' distance infinite, visited status false, and initial parent info
	for (int i = 0; i < V; i++)
		dist.push_back(INT_MAX), visited.push_back(false), parent.push_back(*t);

	//forbit the collision node (if -1 there is no forbidden node)
	if(forbidden != -1) visited[forbidden]=true;

	//setting Source node's cost
	dist[src] = cost;


	// The loop that calculates distance
	for (int j = 0; j < V - 1; j++)
	{
		// Henüz ziyaret edilmemiþ, en az maliyetli düðümü buluyoruz.

		int min = INT_MAX, min_index = 0;

		for (int v = 0; v < V; v++) { //Finding node that we didn't visit and has least cost
			if (visited[v] == false && dist[v] < min) {
				min = dist[v];
				min_index = v;
			}
		}

		visited[min_index] = true;//Mark that node is visited

		// Scans the avaible paths
		for (pair<int, int> x : List[min_index]) {
			// !visited[v] => if we didnt visit the node
			// dist[min_index] != INT_MAX ==> If the cost isnt infinite
			// dist[min_index] + x.second < dist[x.first] => if the distance smaller than already existing distance
			if (!visited[x.first] && dist[min_index] != INT_MAX
				&& dist[min_index] + x.second < dist[x.first]) {
				//Update distance
				dist[x.first] = dist[min_index] + x.second;
				//Set parent of that node
				parent[x.first].setParent(min_index, dist[x.first]);
				
			}

		}
	}

	vector<Path>* tempList = new vector<Path>; //For returning path
	vector<Path>* emptyList = new vector<Path>; //For returning path(if there is no avaible path)

	createPath(parent, dst, *tempList);// Create path for printing

	if ((tempList->back().parent != dst || tempList->front().parent != src)) { //if there is no avaible path return emptyList
		return *emptyList; 
	}else {
		return *tempList;
	}
}

//Detecting Node-base collision
int CollisionDetect(vector<Path> &J, vector<Path> &L) { //Detect if there any collision between nodes

	//compare all nodes for collision
	for (auto i = J.begin(); i != J.end(); ++i) {
		for (auto j = L.begin(); j != L.end(); ++j) {
			if ((*i).parent != (*j).parent || (*i).time != (*j).time) { //if collision does not occurs
				continue;
			}else { //if there are collision return the forbidden node
				return (*i).parent;
			}
		}
	}
	return -1;//if there are no collision
}
//Detecting Stop-base collision + change the path causing collision
void CollisionDetect2(Graph graph, vector<Path>& J, vector<Path>& L) { //COllision detect for stop points
		//Checking collision in duration time

	if (J.front().time > 0) { //If paths are returning paths(D->H)
		for (auto i = L.begin(); i != L.end(); ++i) { //Check every node in Lucy's path if its nodes are in the Joseph's stop time
			if ((*i).time <= J.front().time && (*i).time >= J.front().time - 30 && (*i).parent == J.front().parent) { //Collision occurs  
				vector<Path>* temp = new vector<Path>(dijkstra(graph, L.front().parent, L.back().parent, L.front().time, (*i).parent));//Create altpath for Lucy(ongoing path)
				L = *temp;//Update Lucy's path
				break;
			}
		}
		for (auto i = J.begin(); i != J.end(); ++i) {//Check every node in Joseph's path if its nodes are in the Lucy's stop time
			if ((*i).time <= L.front().time && (*i).time >= L.front().time - 30 && (*i).parent == L.front().parent) {
				vector<Path>* temp = new vector<Path>(dijkstra(graph, J.front().parent, J.back().parent, J.front().time, (*i).parent));
				J = *temp;
				break;
			}
		}
	}
	else {  //If paths are going paths(H->D
		for (auto i = L.begin(); i != L.end(); ++i) {
			if ((*i).time >= J.back().time && (*i).time <= J.back().time + 30 && (*i).parent == J.back().parent) {
				vector<Path>* temp = new vector<Path>(dijkstra(graph, L.front().parent, L.back().parent, L.front().time, (*i).parent));
				L = *temp;
				break;
			}
		}
		for (auto i = J.begin(); i != J.end(); ++i) {
			if ((*i).time >= L.back().time && (*i).time <= L.back().time + 30 && (*i).parent == L.back().parent) {
				vector<Path>* temp = new vector<Path>(dijkstra(graph, J.front().parent, J.back().parent, J.front().time, (*i).parent));
				J = *temp;
				break;
			}
		}
	}
}

//Changing paths for node-base collision(4-cases)
void changePath(vector<Path>& J, vector<Path>& L, vector<Path>& JTemp, vector<Path>& LTemp) {
	int P;
	if (JTemp.size() == 0 && LTemp.size() == 0) { //There is no alternative path for both of them (CASE1)
		cout << "NO SOLUTION!" << endl;
		exit(0);
	}
	else if (JTemp.size() == 0) { //There exists alternative path for Lucy, but no alt path for Joseph
		P = CollisionDetect(J, LTemp); //Collision control
		if (P == -1) L = LTemp; //If there is no collision change Lucy's path (CASE2)
	}
	else if (LTemp.size() == 0) { //There exists alternative path for Joseph, but no alt path for Lucy
		P = CollisionDetect(JTemp, L);
		if (P == -1) J = JTemp; //(CASE2)
	}
	else { //There exists alt. paths for both of them
		int returnP1 = CollisionDetect(J, LTemp);
		int returnP2 = CollisionDetect(JTemp, L);
		if (returnP1 == -1 && returnP2 == -1) { //No collision for both paths (CASE4) MOST effective J+H
			//Calculate costs
			int cost1 = J.back().time + LTemp.back().time;
			int cost2 = JTemp.back().time + L.back().time;

			if (cost1 < cost2) {
				L = LTemp;
			}
			else {
				J = JTemp;
			}

		}
		else if (returnP1 == -1) { //Only Lucy's new path haven't got collision (CASE3)
			L = LTemp;
		}
		else if (returnP2 == -1) {//Only Joseph's new path haven't got collision (CASE3)
			J = JTemp;
		}
		else { //Collision occurs In Both paths 
			cout << "NO SOLUTION!" << endl;
			exit(0);
		}

	}
}

int main(int argc, char** argv)
{
	ifstream file1;
	file1.open(argv[1]); //read file

	if (!file1.is_open()) {
		cout << "File is not opened." << endl;
	}

	int node, JH, JD, LH, LD, src,dest,weight;

	vector<Edge> *EdgeList = new vector<Edge>; //Declare list of edges

	file1 >> node>> JH >> JD >> LH >> LD;
	while(!file1.eof()) {
		file1 >> src >> dest >> weight;
		Edge *e = new Edge(src, dest, weight); //creating new edge
		EdgeList->push_back(*e); //adding new edge info to list
	}

	Graph graph(*EdgeList, node); //Creating Graph
	//Creating going paths
	vector<Path> *JGo = new vector<Path>(dijkstra(graph, JH, JD,0,-1));    
	vector<Path> *LGo = new vector<Path>(dijkstra(graph, LH, LD, 0,-1));

	int GoP = CollisionDetect(*JGo, *LGo);

	if (GoP != -1) {   //If there is a collision
		vector<Path>* JTemp = new vector<Path>(dijkstra(graph, JH, JD, 0, GoP));
		vector<Path>* LTemp = new vector<Path>(dijkstra(graph, LH, LD, 0, GoP));
		changePath(*JGo, *LGo, *JTemp, *LTemp);
	}

	CollisionDetect2(graph,*JGo, *LGo);//Check collision on stops and change the path
	GoP = CollisionDetect(*JGo, *LGo);//Check the new path for collision
	if (GoP != -1) {//If collision occurs
		cout << "NO SOLUTION!" << endl;
		exit(0);
	}
	//Adding duration time for return path
	int jtime = JGo->back().time + 30;
	int ltime = LGo->back().time + 30;

	//Creating return paths
	vector<Path> *JReturn = new vector<Path>(dijkstra(graph, JD, JH, jtime,-1));
	vector<Path> *LReturn = new vector<Path>(dijkstra(graph, LD, LH, ltime,-1));

	//Check if there any collision
	int returnP = CollisionDetect(*JReturn, *LReturn);

	//Same collision operation in Going path

	if (returnP != -1) { //If there is a collision on returning path
		vector<Path>* JTemp = new vector<Path>(dijkstra(graph, JD, JH, jtime, returnP));
		vector<Path>* LTemp = new vector<Path>(dijkstra(graph, LD, LH, ltime, returnP));
		changePath(*JReturn, *LReturn, *JTemp, *LTemp);
		
	}
	CollisionDetect2(graph,*JReturn, *LReturn);//Check collision on stops and change the path if there any
	returnP = CollisionDetect(*JReturn, *LReturn);//Check the new path for collision

	if (returnP != -1) {//If collision occurs after the changing path(for collision on stops)
		cout << "NO SOLUTION!" << endl;
		exit(0);
	}

	PrintResult(*JGo, *JReturn, *LGo, *LReturn); //Print Final Result

}
