/****************************************************
*					NESLIHAN CEKIC					*
*	                  150160060                     *
*						 HW2                        *
*****************************************************/

#include <iostream>
#include <fstream>
#include "minheap.h"

using namespace std;


int main(int argc, char** argv)
{
	string e_name;
	int s_time, e_time;
	vector <event> event_list;

	//Reading file from text file, create objects of events and add to event type vector.
	ifstream file;
	file.open(argv[1]);
	while (!file.eof()) {
		file >> e_name >> s_time >> e_time;
		event e1(e_name, s_time, true);
		event e2(e_name, e_time, false);
		event_list.push_back(e1);
		event_list.push_back(e2);
	}
	
	MinHeap heap(event_list); //Create Min Heap for event_list elements
	int time=1; //Counts time
	event temp; //Temp event object for loop 
	
	temp = heap.RemoveRoot(); //Remove root from min heap
	
	while(heap.getHeap_size()>-1){ //Check if the heap empty
	
		if (temp.time != time) { //if removed node's time is not equal the time there is no event on that time interval
			cout << "TIME " << time << ": "<< "NO EVENT" << endl;
		}
		else { 
			while (temp.time == time) { //if removed node's time is not equal the time there is event on that time interval
				if (temp.start == true) { //if event object is start time 
					cout << "TIME " << time << ": " << temp.event_name << " STARTED" << endl;
				}
				if (temp.start == false) { //if event object is end time
					cout << "TIME " << time << ": " << temp.event_name << " ENDED" << endl;
				}
				if (heap.getHeap_size()==0) { //checck if heap is empty or not. If empty finish the program
					cout << "TIME " << time << ": " << "NO MORE EVENTS, SCHEDULER EXITS" << endl; 
					file.close();
					return 0;
				}
				temp = heap.RemoveRoot(); //Remove root node again.
			}
		}

		time++;//increase time
		
		
		
	}
	
	
}

