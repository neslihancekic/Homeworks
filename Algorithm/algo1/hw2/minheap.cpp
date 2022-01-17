#include "event.cpp"

using namespace std;

Minheap::Minheap(vector<Event> heaparr1){
	heapsize = 0;
	heaparr = heaparr1;

}
int Minheap::leftchild(int i){
	return 2*i + 1;
}
int Minheap::rightchild(int i){
	return 2*i + 2;
}
int Minheap::parent(int i){
	return (i-1) / 2;
}

void swap(Event* x, Event* y) {
    Event temp = *x; 
    *x = *y; 
    *y = temp; 
} 

bool Minheap::insert(Event key){

	heapsize = heapsize + 1;
	heaparr[heapsize - 1]=key;
	HeapifyUp(heapsize -1);
	return true;
}

void Minheap::HeapifyUp(int i){
	//cout << "123" << endl;
	if(i == 0){
		return;
	}
	int p = parent(i);
	if(heaparr[p].getTime() > heaparr[i].getTime()){
		swap(&heaparr[i], &heaparr[p]);
		//cout << "njxvb" << endl;
		HeapifyUp(p);
	}
}
Event Minheap::drop(){
	Event root= heaparr[0];
	heaparr[0]=heaparr[heapsize-1];
	heapsize= heapsize - 1;
	
	HeapifyDown(0);
	return root;
}
void Minheap::HeapifyDown(int i){
	int l = leftchild(i);
	int r = rightchild(i);
	int min; //hangi düğümdeyim

	if(r >= heapsize){
		if(l >= heapsize) return;
		else min = l;
	}

	else{
		if(heaparr[l].getTime() <= heaparr[r].getTime()){
			min = l;
		}
		else{
			min = r;
		} 
	}
	if(heaparr[min].getTime() < heaparr[i].getTime()){
		swap(&heaparr[i], &heaparr[min]);
		HeapifyDown(min);
	}
}


