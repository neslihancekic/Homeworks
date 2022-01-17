#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <vector>
#include <map>
#include <iterator> 
#include <iomanip>
#include <algorithm> 


using namespace std;
/* QUICKSORT ALGORITHM (DESC) */
int partition(vector<pair<int, int>> *A, int p, int r) {
	int x = A->at(p).first; // pivot
	int i = p;
	int j = r;
	while (true) {
		//ignore all the numbers greater than X to left
		while (A->at(i).first > x) {
			i++;
		}
		//ignore all numbers lesser than X to right
		while (A->at(j).first < x) {
			j--;
		}

		//swap a number lesser than X on left with a number greater than X on right
		if (i < j) {
			swap(A->at(i), A->at(j));
			i++;
			j--;
		}
		else {
			//Now the array is so sorted, that all numbers lesser than X are on right of it and greater than X are to left of it. Hence return position of X
			return j;
		}
	}
}
void quicksort(vector<pair<int, int>> *A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quicksort(A, p, q);
		quicksort(A, q + 1, r);
	}
}

/*NOT USED (to see inplace descending sort)*/
void bubble_sort(vector<pair<int, int>>* a)//NOT USED
{
	int n = a->size() - 1;
	for (int i = n; i >= 0; i--)
		for (int j = n; j > n - i; j--)
			if (a->at(j).first > a->at(j - 1).first)
				swap(a->at(j), a->at(j - 1));
}

//FOR EDIT DISTANCE ALGO.
int min(int x, int y, int z) 
{
	return min(min(x, y), z);
}
//FOR KNAPSACK ALGO.
int max(int x, int y) { 
	return (x > y) ? x : y;
}

/*  KnapSack:
	->Selects Test Suites
	->Prints predicted bugs and running time
	->Returns selected Test Suites
	W=max weight limit
	w=items' weight
	v=items' values*/
vector<int> knapSack(int W, vector<int> w, vector<int> v) {
	int n = w.size(); //total number of items

	int i, j;

	//Create 2D matrix [totalnumberofitem+1][maxweightlimit+1]
	int** M = new int* [n + 1];
	for (int i = 0; i < n+1; i++)
		M[i] = new int[W+1];
		
	//Bottom-up -> Build a M[][] table
	//OPT(i, w) = max profit subset of items 1, …, i with weight limit w.
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= W; j++) {
			if (i == 0 || j == 0) { //0 -------------> if i = 0
				M[i][j] = 0;
			}
			else if (w[i - 1] > j) {//OPT(i -1, w) -----> if wi > w
				M[i][j] = M[i - 1][j];
			}
			else { //max OPT(i -1, w), vi + OPT(i -1, w- wi { )} -------> otherwise
				M[i][j] = max(v[i - 1] + M[i - 1][j - w[i - 1]], M[i - 1][j]);
				
			}
		}
	}

	cout <<"Total amount of bugs: "<< M[n][W] << endl; //optimal solution

	/*************************************************/
	// Find selected test suites
	
	vector<int> testsuites;
	int totaltime=0;

	i = n;
	j = W;
	while (i > 0 && j > 0) {// Iterate matrix bacward (this cell has optimal solution)
		if (M[i][j] != M[i - 1][j]) { //Compare it with the cell vertically upwardif they are not equal we know that it cell is selected
			testsuites.push_back(i-1); //selected testsuites
			totaltime += w[i-1];  //total amount of running time
			j = j - w[i-1]; //reduce the limit
		}
		i = i - 1; //move upward
	}

	cout << "Total amount of running time: " << totaltime << endl << endl;

	return testsuites; //return selected testsuites 
}

/*  editDist:
	->Finds distance between 2 vector of integers
	->Returns the distance between them
	tc1=testcase1
	tc2=testcase2*/
int editDist(vector<int> tc1, vector<int> tc2)
{
	int m = tc1.size(); //testcase1 size
	int n = tc2.size();  //testcase2 size
	int cost;
	// Create a table to store results of subproblems 
	int** dp = new int* [m + 1];
	for (int i = 0; i < m + 1; i++)
		dp[i] = new int[n + 1];

	for (int i = 0; i <= m; i++) 
		dp[i][0] =i; 

	for (int j = 0; j <= n; j++) 
		dp[0][j] = j; 

	//Bottom up
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			
			if (tc1[i - 1] == tc2[j - 1]) {
				cost = 0;
			}
			else {
				cost = 1;
			}
			dp[i][j] =min(dp[i][j - 1]+1, // Insert 
					dp[i - 1][j]+1, // Remove 
					dp[i - 1][j - 1] + cost); // Replace 
		}
	}

	return dp[m][n]; //return distance

}


/*  FindCoverage:
	->Finds coverage of a testcase
    ->Creates ordered Sequence of a testcase
	->Returns coverage of that testcase
	v=test case
	seq*= vector of ordered sequences
	c*= vector of all testcases coverage(for one test suite)*/
int FindCoverage(vector<int> v, vector<vector<int>>* seq, vector<int>* c) {
	multimap<int, int> ordered; //for easy sorting for ordered sequence
	vector<int> temp; 
	int count = 0; //coverege of test case

	for (unsigned int b = 0; b < v.size(); b++) {
		if (v[b] > 0) count++;
		ordered.insert(pair<int, int>(v[b], b + 1)); //mapping testcase to sort 
	}
	//create vector of ordered sequence for a testcase
	multimap<int, int>::iterator itr;
	for (itr = ordered.begin(); itr != ordered.end(); ++itr) {
		temp.push_back(itr->second);
	}
	seq->push_back(temp);//adds created ordered sequence to seq vector
	c->push_back(count);//adds coverage to c vector
	

	return count; //return coverage of that testcase
}


/* TestCasePrioritization
	->Finds and prints prioritized vector of test cases
	t=test suite's test cases vector*/
void TestCasePrioritization(vector<vector<int>> t) {
	vector<int>* coverage =new vector<int>; //holds coverage of test cases
	vector<vector<int>>* orderedseq = new vector<vector<int>>; //holds ordered seq of testcases

	vector<pair<int,int>> finalsort; //Final sort result <distance,testcase'snumber>

	int max=0;

	for (unsigned int a = 0; a < t.size(); a++) {
		int count = FindCoverage(t[a], orderedseq, coverage); //finds all test cases coverage
		if (count > max) max = count;   //find max coverage of a test suite
	}

	for (unsigned int i = 0; i < coverage->size(); i++) {
		if(max== coverage->at(i)) finalsort.push_back(pair<int,int>(0, i + 1)); //adds testcases that has max coverage to finalsort vector(distance=0)
	}

	if (t.size() != 1 || t.size()!=finalsort.size()) { //if number of testcases > 1 and not all test cases have not max coverage

		int distance;
		vector<pair<int,int>> *places=new vector<pair<int, int>>; //holds distance and test case number of test cases

		for (unsigned int j = 0; j < t.size(); j++) {
			int alreadysortedcheck = 0; //check if that testcase in finalsort or not
			for (unsigned int i = 0; i < finalsort.size(); i++) {
				if (j + 1 < (unsigned int)finalsort[i].second) { break; } //if test case number smaller than final sort elements break
				else if (j + 1 == (unsigned int)finalsort[i].second) { //if the test case already in final sort 
					alreadysortedcheck++; //increment check
					break;
				}
			}
			if (alreadysortedcheck == 0) { ////if the test case not in the final sort 
				distance = editDist(orderedseq->at(j), orderedseq->at(finalsort[0].second - 1)); //finds distance between testcase that has max coverage & other test case 
				places->push_back(pair<int,int>(distance,j+1)); // adds distance and number of distance calculated test case
			}
		}
		/*FOR INPLACE SORT (O(N^2)) */
		//bubble_sort(places); 

		/*READY SORT ALGORITHM (O(NLGN))*/
		//std::sort(places->begin(),places->end(),greater <> ());

		/*QUICKSORT O(NLGN) (WORSTCASE O(N^2))*/
		quicksort(places, 0, places->size() - 1);

		finalsort.insert(finalsort.end(), places->begin(), places->end()); //adds test cases which their distances calculated and sorted to final sort
	}

	/*Prints order of testcases*/
	for (unsigned int i = 0; i < finalsort.size(); i++)
	{
		cout << setfill(' ') << setw(2) << finalsort[i].second;
		if (i + 1 != finalsort.size()) cout << "  - ";
	}
	/*Prints found distances of test cases */
	cout << endl<<"Distances: ";
	for (unsigned int i = 0; i < finalsort.size(); i++)
	{
		cout << setfill(' ') << setw(2) << finalsort[i].first;
		if (i + 1 != finalsort.size()) cout << "  - ";
	}
}

int main(int argc, char** argv) {

	ifstream file;
	file.open(argv[1]); //read file

	if (!file.is_open()) {
		cout << "File is not opened." << endl;
	}

	vector<string> test; //holds test suites name
	vector<int> bugs, time;
	vector<vector<vector<int>>> testcases;
	
	string empty;
	int max_running_time;

	/*FILE READ*/
	file >> empty >> empty >> empty >> empty >> max_running_time>>empty;
	getline(file,empty);

	string line;
	string delimiter = " ";
	string delimiter2 = "-";
	size_t pos = 0, pos2=0;
	string token,token2;
	
	while (getline(file, line))
	{
		int counter = 0;
		vector<int> temp;
		vector<vector<int>> temp2;

		while ((pos = line.find(delimiter)) != string::npos) {
			token = line.substr(0, pos);
			if (counter == 0) {   //TEST SUITE ID READ
				test.push_back(token);
				counter++;
			}
			else if (counter == 1) { //BUG
				bugs.push_back(stoi(token));
				counter++;
			}
			else if (counter == 2) { //RUNNING TIME
				time.push_back(stoi(token));
				counter++;
			}
			else {
				while ((pos2 = token.find(delimiter2)) != string::npos) { //READS TEST CASES 
					token2= token.substr(0, pos2);
					temp.push_back(stoi(token2));
					token.erase(0, pos2 + delimiter2.length());
				}
				temp.push_back(stoi(token));
				temp2.push_back(temp);
			}
			
			temp.clear();
			line.erase(0, pos + delimiter.length());
		}

		while ((pos2 = line.find(delimiter2)) != string::npos) {
			token2 = line.substr(0, pos2);
			temp.push_back(stoi(token2));
			line.erase(0, pos2 + delimiter2.length());
		}

		temp.push_back(stoi(line));

		temp2.push_back(temp);
		testcases.push_back(temp2);

	}
	/*FILE READ END*/

	vector<int> selectedtests = knapSack(max_running_time, time, bugs);  //Select optimal tests

	cout << "Selected Test Suites\n********************" << endl;
	cout << "testSuiteId\tbugsDetected\trunningTime"  << endl;
	for (int i = selectedtests.size()-1; i >= 0; i--) {
		cout<< test[selectedtests[i]] <<"\t\t"<< bugs[selectedtests[i]]<<"\t\t"<< time[selectedtests[i]] << endl;
	}

	cout << endl << "Order of Test Cases\n*******************" << endl;
	for (int j = selectedtests.size() - 1; j >= 0; j--) {
		cout << test[selectedtests[j]] << " Order: ";
		TestCasePrioritization(testcases[selectedtests[j]]); //Prioritize test cases of selectected tests
		cout << endl << endl;
	}

	return 0;

}


