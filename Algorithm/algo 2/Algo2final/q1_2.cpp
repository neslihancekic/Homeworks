/*NESLÝHAN ÇEKÝÇ
 150160060
 FINAL PROJECT
 compile: g++ -std=c++11 -Wall -Werror q1_2.cpp -o q1_2
 run: ./q1_2 array1.txt */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void print_arr(vector<int>& arr, int first, int last)
{
	for (int i = first; i <= last; i++)
	{
		string if_eol = (i == last) ? "\n" : ", ";

		cout << arr[i] << if_eol;
	}
}
void func(vector<int>& arr, int first, int last)
{
	int m = 0;
	int k = first;
	vector<int> *A =new vector<int>;

	while (k < last) {
		if (arr[k] > arr[k + 1]) {
			int temp = arr[k];
			arr[k] = arr[k + 1];
			arr[k + 1] = temp;
		}
		k = k + 2;
	}
	k = first + 1;
	while (k <= last) {
		A->push_back(arr[k]);
		m = m + 1;
		k = k + 2;
	}
	int x = first;
	k = first;
	while (k <= last) {
		arr[x] = arr[k];
		x = x + 1;
		k = k + 2;
	}
	
	k = 0;
	
	while (k < m) {
		arr[x] = A->at(k);
		x = x + 1;
		k = k + 1;
	}

}
void merge(vector<int>& arr, int first, int mid, int mid2, int last)
{

	int i = first, j = mid2, k = 0;
	vector<int> *temp=new vector<int>;
	while (i <= mid && j <= last) {
		if (arr[i] < arr[j]) {
			temp->push_back(arr[i]);
			k = k + 1;
			i = i + 1;
		}
		else {
			temp->push_back(arr[j]);
			k = k + 1;
			j = j + 1;
		}
	}
	while (i <= mid) {
		temp->push_back(arr[i]);
		k = k + 1;
		i = i + 1;
	}

	while (j <= last) {
		temp->push_back(arr[j]);
		k = k + 1;
		j = j + 1;
	}
	i = first;
	j = 0;
	while (i <= last) {
		arr[i] = temp->at(j);
		i++;
		j++;
	}

}

int maximum(vector<int>& arr,int a, int b) {
	if (arr[b] > arr[a]) {
		return b;
	}
	else {
		return a;
	}

}

int minimum(vector<int>& arr, int a, int b) {
	if (arr[b] < arr[a]) {
		return b;
	}
	else {
		return a;
	}

}

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void mmsort(vector<int>&, int, int);

pair<int,int> minmax(vector<int>& arr, int first, int last) { //returns (max,min)
	int n = last - first + 1;
	int mid = (first + last) / 2;
	pair<int, int> m1, m2, temp;
	if (n > 1){ //if array has at least 2 elements
		m1 = minmax(arr, first, mid); //divide first half
		m2 = minmax(arr, mid + 1, last); //divide second half
		swap(&arr[first], &arr[minimum(arr, m1.second, m2.second)]); //swap min value with first element
		swap(&arr[last], &arr[maximum(arr, m1.first, m2.first)]);//swap max value with last element
	}
	else {
		return make_pair(maximum(arr, first, last), minimum(arr, first, last)); //if array single element return max min
	}
	
	return make_pair(maximum(arr,m1.first, m2.first), minimum(arr,m1.second, m2.second));//return max,min 
}

void mmsort(vector<int>& arr, int first, int last) {
	minmax(arr, first, last); //find array's min and max values and swap with first and last element
	if (last - first + 1 > 1) { //if array has at least 2 element
		cout << "Min: " << arr[first] << " Max: " << arr[last] << endl; //print min and max values(previously swap in minmax)
		mmsort(arr, first + 1, last - 1); //call mmsort for inner array(without first and last element)
	}
}

void sort(vector<int>& arr, int first, int last)
{

	int n = last - first + 1;
	int mid = (first + last) / 2;
	if (n <= 1) {
		
	}
	if (first < last) {
		func(arr, first, last);
		mid = (first + last) / 2;
		cout << "Min_max unsorted: ";
		print_arr(arr, first, mid);
		mmsort(arr, first, mid); //Calling minmax sort algorithm for left subtrees
		cout << "Min_max sorted: ";
		print_arr(arr, first, mid);
		if (mid+1 != last )print_arr(arr, mid+1, last);
		sort(arr, mid + 1, last);
		merge(arr, first, mid, mid + 1, last);
	}

}

int main(int argc, char *argv[])
{

	vector<int> all_values;


	try {
		
		string filename = argv[1];

		ifstream myfile(filename);

		
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				int number = stoi(line);
				all_values.push_back(number);
			}

			sort(all_values, 0, all_values.size() - 1);

			print_arr(all_values, 0, all_values.size() - 1);
		}
		else
		{
			cout << "File is not available." << endl;
			throw;
		}

	}
	catch (const ifstream::failure& e)
	{
		cerr << "Exception opening the file!" << endl;
		return -1;
	}
	catch (...)
	{
		cerr << "Something's wrong!" << endl;
		return -1;
	}



	return 0;
}
