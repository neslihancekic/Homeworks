/*NESLÝHAN ÇEKÝÇ
 150160060
 FINAL PROJECT
 compile: g++ -std=c++11 -Wall -Werror q4.cpp -o q4
 run: ./q4 q4_test.txt */

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Node {
public:
	int element;
	Node* next;
	Node* prev;
};

int main(int argc, char** argv) {
	ifstream testfile;
	testfile.open(argv[1]); //read the inputs from test file
	
	int capacity; //capacity is the maximum number of elements in the cache, defined as k in pdf
	int element_number; //number of different elements that can possibly requested, equals to k+1 in our case
	int request_number; //number of requests, defined as n in pdf

	testfile >> capacity;
	element_number = capacity + 1;

	int cache_size = 0; //cache size keeps number of elements in the cache, initially zero
	vector<int> cache(element_number, 0); //cache is created as empty as all indexes are 0

	testfile >> request_number;
	cout << request_number;
	vector<int> requests(request_number);
	for (int i = 0; i < request_number; i++)
		testfile >> requests[i];

	vector<int> fif(requests.size()); //to keep the farthest element for each request

	vector<int> elements(element_number); //elements array {0, 1, ... , k}
	for (int i = 0; i < element_number; i++)
		elements[i] = i;

	vector<Node*> addresses; //array for keeping the address of double linked list nodes of elements
	
	//addresses[i] keeps the node address for elements[i]
	
	Node* list; //head
	Node* back;

	Node* temp = new Node;
	temp->prev = NULL;
	temp->next = NULL;
	list = temp;
	temp->element=elements[0];
	addresses.push_back(temp);

	for (unsigned int i = 1; i < elements.size(); i++){
		Node* temp2 = new Node;
		temp->next = temp2;
		temp2->prev = temp;
		temp2->element = elements[i];
		temp = temp2;
		addresses.push_back(temp);
	}
	back = temp;
	
	for (int i = request_number - 1; i >= 0; i--) {
		Node *node = addresses[requests[i]];
		if (node == back) {
			back = back->prev;
			back->next = NULL;
		}
		list->prev = node;
		node->next = list;
		list =node;
		fif[i] = back->element;	
	}
	for (unsigned int i = 0; i < requests.size(); i++) {
		cout << fif[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < request_number; i++) {
		if (cache[requests[i]] != 1) {
			cout << "cache miss" << endl;
			if (cache_size==capacity) {
				cache[fif[i]] = 0;
				cache[requests[i]] = 1;
				cout << "cache is full, element " << fif[i] << " is evicted\nelement " <<requests[i]<<" is added into the cache"<< endl;
			}
			else {
				cache_size++;
				cout << "element " << requests[i] << " is added into the cache" << endl;
				cache[requests[i]] = 1;
			}
		}
		else {
			cout << "cache hit" << endl;
		}

	}
	

	return 0;


}
