#include "Heap.h"

using namespace std;

Event::Event(){
	event_name = " ";
}

Event::Event(string name, int ntime, bool nwhat, int nindex){
	event_name = name;
	time = ntime;
	what = nwhat;
	index = nindex;
}
Event::Event(const Event& a) {
	event_name = a.event_name;
	time = a.time;
	what = a.what;
	index = a.index;
}

void Event::operator=(const Event& a) {
	event_name = a.event_name;
	time = a.time;
	what = a.what;
	index = a.index;
}

string Event::getName() const{
	return event_name;
}

int Event::getTime() const{
	return time;
}

int Event::getIndex() const{
	return index;
}

bool Event::getWhat() const{
	return what;
}

void Event::setName(string name) {
	event_name = name;
}

void Event::setTime(int time1) {
	time = time1;
}
void Event::setWhat(bool what1) {
	what = what1;
}
void Event::setIndex(int index1) {
	index = index1;
}






