//Header of heap
#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Event{
	public:
		//default constructor
		Event();
		//overload constructor 
		Event(string, int, bool, int);
		Event(const Event&);
	    //accessor functions
	    string getName() const;
	    int getTime() const;
	    bool getWhat() const;
	    int getIndex() const;
		void setName(string);
		void setTime(int);
		void setWhat(bool);
		void setIndex(int);
		void operator=(const Event&);

	private:
		string event_name;
		int time;
		bool what;
		int index;
};

class Minheap{
		
		int heapsize;
	public:
		vector<Event> heaparr;
		Minheap(vector<Event>);
		int getHeapsize(){ return heapsize;}
		int leftchild(int i);
		int rightchild(int i);
		int parent(int i);
		bool insert(Event);
		Event drop();
		
		void HeapifyUp(int i);
		void HeapifyDown(int i);
		//void print(int maxsize);
};


#endif
