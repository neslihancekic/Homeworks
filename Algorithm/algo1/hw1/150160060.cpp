/****************************************************
*					NESLIHAN CEKIC					*
*	                  150160060                     *
*						 HW1                        *
*****************************************************/

#include <iostream>
#include <stdlib.h>    
#include <time.h> 

using namespace std;

int duplicate(int** a, int n) {
	int count = 0; //declaring count for encountered number of duplicants
	for (int i = 1; i <= n-1; i++) {   //i=1------n-1 (n-1 because last element has no duplicant
		for (int j = i+1 ; j <= n; j++) { //j=i+1----n (check elements after i (i<j))
			if (a[i][0] == a[j][0]) { // if it's duplicant (A[i]=A[j])
				cout << '(' << i << ',' << j << ')' << "\t"; 
				count++; //increment encountered number of duplicants
				if (count % 10 == 0) { 
					cout << endl;
				}
			}
		}
	}
	return count;
}

int main()
{
	int number,n; //number for random elements, n for array size
	cin >> n; //get array size

	while (n < 2) { // if input smaller than 2 we cannot find the pairs
		cerr << "Wrong input please enter bigger number:" << endl;;
		cin >> n; //take correct array size again
	}

	srand(time(NULL)); //time func

	int** a = NULL;    // declaring double pointer for send the array to function
	a = new int* [n+1];    //create A[1.....n] array
	for (int i = 1; i <= n; i++)
		a[i] = new int[2]; //2 dimensional array for keeping the location of number

	for (int i = 1; i <= n; i++) {  //assigning random numbers and their location to array
		number = rand() % n + 1; //1----n random numbers
		a[i][0] = number; //random number assignining
		a[i][1] = i; //location
	}
	
	cout << "ARRAY:" << endl; 
	//printing array
	for (int i = 1; i <= n; i++) {
		cout << a[i][0] << "\t" ;
		if (i % 10 == 0) {
			cout << endl;
		}
	}
	cout << endl;
	//printing expected number of duplicants(explained in report)
	cout << "EXPECTED NUMBER OF DUPLICATIONS: " << (n-1)/2 << endl;

	cout << endl;

	int count = duplicate(a, n); //send array and its size to algorithm

	cout << endl<<endl;

	cout << "ENCOUNTERED NUMBER OF DUPLICATIONS: " << count << endl; //print encountered number of duplicants with duplicate functions
	

}
