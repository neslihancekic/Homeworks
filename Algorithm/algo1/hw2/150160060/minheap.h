/****************************************************
*					NESLIHAN CEKIC					*
*	                  150160060                     *
*						 HW2                        *
*****************************************************/
#ifndef MINHEAP_H // include guard
#define MINHEAP_H
#include <iostream>
#include <vector> 

using namespace std;

//EVENT CLASS 
class event {
public:
	string event_name;
	int time;
	bool start; //Holds if this object is start time or and time 

	//Constructor:
	event(string e = "0", int t = 0, bool s = true) { 
		event_name = e;
		time = t;
		start = s;
	}
	//Copy Constructor:
	event(const event &ev){
		event_name = ev.event_name;
		time = ev.time;
		start = ev.start;
	}
	//Operator overloads:
	void operator=(const event& ev) {
		event_name = ev.event_name;
		time = ev.time;
		start = ev.start;
	}

	bool operator > (event const& obj) {
		if (obj.time >= time) {
			return false;
		}
		else {
			return true;
		}
	}
	bool operator < (event const& obj) {
		if (obj.time < time) {
			return false;
		}
		else {
			return true;
		}
	}
	
};


//Swap function for heap operations
void swap(event* x, event* y)
{
	event temp = *x;
	*x = *y;
	*y = temp;
}

// A class for Min Heap 
class MinHeap
{
	vector<event> harr; // vector of event(all events) in heap 
	int heap_size; // Current number of elements in min heap 

public:
	// Constructor :
	MinHeap(vector<event>);

	//Getter method of Heap size:
	int getHeap_size() { return heap_size; }

	// to heapify a subtree with the root at given index 
	void MinHeapify(int);

	// to get index of parent and left, right child index
	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }

	// to remove the root which is the minimum element 
	event RemoveRoot();

};


MinHeap::MinHeap(vector<event> a)
{
	heap_size = 0;
	harr = a;
	vector <event>::iterator it;
		for (it = harr.begin(); it != harr.end(); ++it) {
			// First insert the new key at the end 
			heap_size++;
			int i = heap_size - 1;
			harr[i] = *it;

			// Fix the min heap property if it is violated 
			while (i != 0 && harr[parent(i)] > harr[i])
			{
				swap(&harr[i], &harr[parent(i)]);
				i = parent(i);
			}
	}

}

// Method to remove minimum element (or root) from min heap 
event MinHeap::RemoveRoot()
{
		if (heap_size == 1)
		{
			heap_size--;
			return harr[0];
		}

		// Store the minimum value, and remove it from heap 
		event root = harr[0];
		harr[0] = harr[heap_size - 1];
		heap_size--;
		MinHeapify(0);

		return root;
	
}

void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}
#endif
