#include <iostream>
#include <string>
#include <fstream>
#include "minheap.cpp"

using namespace std;

void fillvector(vector<Event>&); // fill vector - fill in event information       //@param vector<Event>& - event in class
//void printvector(const vector<Event>&); //print the information of all events.

int main(){
    vector<Event> myClass;
	fillvector(myClass);
	Minheap minheap(myClass);
	for (unsigned int i = 0; i < myClass.size(); i++) {
		minheap.insert(myClass[i]);
	}
	int T=0;
	Event begin = minheap.drop();
	cout << begin.getName() << endl;
	while (minheap.getHeapsize() > -1) {
		if (T != begin.getTime()) {
			cout << "Time "<<T<<": NO EVENT"<<endl;
		}
		else {
			while (T == begin.getTime()) {
				
				if (begin.getWhat() == true) {
					cout << "Time " << T << ": " << begin.getName() << " STARTED" << endl;
				}
				else {
					cout << "Time " << T << ": " << begin.getName() << " ENDED" << endl;

				}

				
				if (minheap.getHeapsize() == 0) {
					cout << "Time " << T << ": " << "NO MORE EVENTS, SCHEDULER EXISTS" << endl;
					return 0;
				}
				begin = minheap.drop();
			}
		}
		T++;
	}
	
	return 0;

	
}

void fillvector(vector<Event>& newMyClass){
	int i = 0;
	ifstream file;
	string event_name1;
	int stime, etime;
	file.open("veri.txt");
	if(!file.is_open()){
		cout << "File is not opened." << endl;
	}
	while(!file.eof()){
		file >> event_name1 >> stime >> etime;
		Event newEvent(event_name1, stime, true , i);
		i++;
		Event newEvent1(event_name1, etime, false , i);
		i++;
		newMyClass.push_back(newEvent);
		newMyClass.push_back(newEvent1);
	}

	
}

