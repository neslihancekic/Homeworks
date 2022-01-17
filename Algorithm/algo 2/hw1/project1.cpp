#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <chrono> 
#include "pokemons.h"

using namespace std;

list<Attack> pikachu_attacks;
list<Attack> blastoise_attacks;
list<BattleNode*>* samelevel = new list<BattleNode*>; //For hold the same level nodes for part1


void readFiles() {
	ifstream file1;
	ifstream file2;
	string line;
	string delimiter = ",";
	string attack_name;
	int pp = 0, accu = 0, dam = 0, first = 0;
	
	/* PIKACHU ATTACKS*/
	file1.open("pikachu.txt");

	if (!file1.is_open()) {
		cout << "File is not opened." << endl;
	}

	getline(file1, line);

	while (!file1.eof()) {
		int count = 0;
		getline(file1, line);
		size_t pos = 0;
		if ((pos = line.find(delimiter)) != string::npos) {
			attack_name = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());

		}
		while ((pos = line.find(delimiter)) != string::npos) {
			if (count == 0) {
				pp = stoi(line.substr(0, pos));
				count++;
			}
			else if (count == 1) {
				accu = stoi(line.substr(0, pos));
				count++;
			}
			else if (count == 2) {
				dam = stoi(line.substr(0, pos));
				count++;
			}

			line.erase(0, pos + delimiter.length());

		}
		first = stoi(line.substr(0, pos));

		Attack attack(attack_name, pp, accu, dam, first);
		pikachu_attacks.push_back(attack);
	}
	file1.close();

	/* BLASTOISE ATTACKS*/
	file2.open("blastoise.txt");

	if (!file2.is_open()) {
		cout << "File is not opened." << endl;
	}

	getline(file2, line);

	while (!file2.eof()) {
		int count = 0;
		getline(file2, line);
		size_t pos = 0;
		if ((pos = line.find(delimiter)) != string::npos) {
			attack_name = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());

		}
		while ((pos = line.find(delimiter)) != string::npos) {
			if (count == 0) {
				pp = stoi(line.substr(0, pos));
				count++;
			}
			else if (count == 1) {
				accu = stoi(line.substr(0, pos));
				count++;
			}
			else if (count == 2) {
				dam = stoi(line.substr(0, pos));
				count++;
			}

			line.erase(0, pos + delimiter.length());

		}
		first = stoi(line.substr(0, pos));

		Attack attack(attack_name, pp, accu, dam, first);
		blastoise_attacks.push_back(attack);

	}
}

list<BattleNode*> *createLevel(BattleNode *mother,int level, int count) {
	if (level == 0) {
		samelevel->push_back(mother);
	}
	

	if (mother->getBlasHP() == 0 || mother->getPikacHP() == 0) {
		mother->setChildren(NULL);
		return NULL;
	}
	
	
	int newpp, newhp;
	double newprob;
	int attack_number=0;

	list<BattleNode*>* children = new list<BattleNode*>;
	if (count > 0) {
		/*PIKACHU'S TURN*/
		if (mother->getTurn() == 'P') {
			for (list<Attack>::iterator it = pikachu_attacks.begin(); it != pikachu_attacks.end(); ++it) { //Counts available attack
				if ((*it).getFirst() <= mother->getLevel()+1 && mother->getPikacPP() + (*it).getPp() > 0) {
					attack_number++;
				}
			}
			for (list<Attack>::iterator it = pikachu_attacks.begin(); it != pikachu_attacks.end(); ++it) { //Apply attacks
				if ((*it).getFirst() <= mother->getLevel()+1 && mother->getPikacPP() + (*it).getPp() > 0) {
					if ((*it).getAccu() == 100) { //If accuracy is 100
						/*Calculating new HP/PP/Probability*/
						newpp = mother->getPikacPP() + (*it).getPp();
						newhp = mother->getBlasHP() - (*it).getDam();
						if (newhp < 0) { newhp = 0; }
						newprob = mother->getProb() / attack_number;
						/*Creating new node*/
						BattleNode* temp = new BattleNode(mother->getPikacHP(),newpp,newhp, mother->getBlasPP(),'B',newprob, mother->getLevel()+1,1);
						/*Setting variables*/
						temp->setAttack((*it).getAtt());
						temp->setEffect(true);
						temp->setMother(mother);
						children->push_back(temp);
					}
					else { //If accuracy is not 100
						/*for effective node*/
						newpp = mother->getPikacPP() + (*it).getPp();
						newhp = mother->getBlasHP() - (*it).getDam();
						if (newhp < 0) { newhp = 0; }
						newprob = mother->getProb() / attack_number * ((*it).getAccu()) / 100.0;
						BattleNode* tempeff = new BattleNode(mother->getPikacHP(), newpp, newhp, mother->getBlasPP(), 'B', newprob, mother->getLevel() + 1, 1);
						tempeff->setAttack((*it).getAtt());
						tempeff->setEffect(true);
						tempeff->setMother(mother);
						children->push_back(tempeff);
						/*for non-effective node*/
						newprob = mother->getProb() / attack_number * (100.0 - (*it).getAccu()) / 100;
						BattleNode* tempneff = new BattleNode(mother->getPikacHP(), newpp, mother->getBlasHP(), mother->getBlasPP(), 'B', newprob, mother->getLevel() + 1, 1);
						tempneff->setAttack((*it).getAtt());
						tempneff->setEffect(false);
						tempneff->setMother(mother);
						children->push_back(tempneff);
					}
				}
			}
		}

		/*BLASTOISE'S TURN*/
		if (mother->getTurn() == 'B') {
			for (list<Attack>::iterator it = blastoise_attacks.begin(); it != blastoise_attacks.end(); ++it) {
				if ((*it).getFirst() <= mother->getLevel() + 1 && mother->getBlasPP() + (*it).getPp() > 0){
					attack_number++;
				}
			}
			for (list<Attack>::iterator it = blastoise_attacks.begin(); it != blastoise_attacks.end(); ++it) {
				if ((*it).getFirst() <= mother->getLevel() + 1 && mother->getBlasPP() + (*it).getPp() > 0){
					if ((*it).getAccu() == 100) {
						newpp = mother->getBlasPP() + (*it).getPp();
						newhp = mother->getPikacHP() - (*it).getDam();
						if (newhp < 0) { newhp = 0; }
						newprob = mother->getProb() / attack_number;
						BattleNode* temp = new BattleNode(newhp, mother->getPikacPP(), mother->getBlasHP(), newpp, 'P', newprob, mother->getLevel() + 1, 1);
						temp->setAttack((*it).getAtt());
						temp->setEffect(true);
						temp->setMother(mother);
						children->push_back(temp);
					}
					else {
						newpp = mother->getBlasPP() + (*it).getPp();
						newhp = mother->getPikacHP() - (*it).getDam();
						if (newhp < 0) { newhp = 0; }
						newprob = mother->getProb() / attack_number * ((*it).getAccu()) / 100.0;
						BattleNode* tempeff = new BattleNode(newhp, mother->getPikacPP(), mother->getBlasHP(), newpp, 'P', newprob, mother->getLevel() + 1, 1);
						tempeff->setAttack((*it).getAtt());
						tempeff->setEffect(true);
						tempeff->setMother(mother);
						children->push_back(tempeff);

						newprob = mother->getProb() / attack_number * (100.0 - (*it).getAccu()) / 100;
						BattleNode* tempneff = new BattleNode(mother->getPikacHP(), mother->getPikacPP(), mother->getBlasHP(), newpp, 'P', newprob, mother->getLevel() + 1, 1);
						tempneff->setAttack((*it).getAtt());
						tempneff->setEffect(false);
						tempneff->setMother(mother);
						children->push_back(tempneff);
					}
				}
			}
		}
		/*change mothers leaf status and add their children to itself*/
		mother->setIsleaf(0);
		if(children != NULL) mother->setChildren(children);
	}
	/*If last level nodes created add that nodes to samelevel list*/
	if (count == 1) {
		for (list<BattleNode*>::iterator it = children->begin(); it != children->end(); ++it) {
			samelevel->push_back(*it);
		}
	}
	/*Recursive node creating*/
	count--;
	if (children!=NULL) {
		for (list<BattleNode*>::iterator it = children->begin(); it != children->end(); ++it) {
			list<BattleNode*>* l = createLevel((*it), level, count);
		}

	}

	return samelevel;
}
list<BattleNode*> *visited =new list<BattleNode*>;
list<BattleNode*> *stack = new list<BattleNode*>;

void DFS(BattleNode* first_node) {

	if (first_node != NULL) {


		visited->push_back(first_node);

		if (stack->size() != 0) stack->pop_back();


		if (first_node->getChildren() != NULL) {
			for (list<BattleNode*>::iterator it = first_node->getChildren()->begin(); it != first_node->getChildren()->end(); ++it) {
				stack->push_back((*it));
			}
		}

		if (stack->size() == 0) {
			cout << "NODE COUNT: " << visited->size() << endl;
		}
		else {
			DFS(stack->back());
		}

	}
}

void BFS(BattleNode* first_node) {

	visited->push_back(first_node);
	if (stack->size() != 0) stack->pop_front();
	
	
	if (first_node->getChildren()) {
		for (list<BattleNode*>::iterator it = (*first_node).getChildren()->begin(); it != (*first_node).getChildren()->end(); ++it) {
			stack->push_back((*it));
		}
	}
	if (stack->size() == 0) {
		cout << "NODE COUNT: " << visited->size() << endl;
	}
	else {

		BFS(stack->front());
	}

}



BattleNode* PathPrint(BattleNode* child) {

	if (child == NULL) return NULL;
	PathPrint(child->getMother());
	if (child->getAttack() != "") {

	
		if (child->getTurn()== 'P') {
			cout << "Blastoise used " << child->getAttack() << ". ";
		}
		else {
			cout << "Pikachu used " << child->getAttack() << ". ";
		}
		if (child->getEffect() == "effective") {
			cout << "It's effective." << endl;
		}
		else {
			cout << "It's noneffective." << endl;
		}
	}
	return NULL;
}

BattleNode* BFSFind(BattleNode* first_node, char pokemon) {
	visited->push_back(first_node);
	if (stack->size() != 0) stack->pop_front();

	if (pokemon == 'P' && first_node->getBlasHP() == 0) {
		PathPrint(first_node);
		
		cout << endl << "Level count: "<<first_node->getLevel() << endl << "Probability: "<<first_node->getProb() << endl;
		return first_node;
	}
	if (pokemon == 'B' && first_node->getPikacHP() == 0) {
		PathPrint(first_node);

		cout << endl << "Level count: " << first_node->getLevel() << endl << "Probability: " << first_node->getProb() << endl;
		return first_node;
	}

	if (first_node == NULL) return NULL;
	
	if (first_node->getChildren() != NULL) {
		for (list<BattleNode*>::iterator it = (*first_node).getChildren()->begin(); it != (*first_node).getChildren()->end(); ++it) {
			stack->push_back((*it));
		}
	}
	if (stack->size() == 0) {
		return first_node;
	}
	BattleNode* x = BFSFind(stack->front(),pokemon);

	return NULL;

}

int main(int argc, char** argv)//int argc, char** argv
{

	readFiles();
	BattleNode first_node(200, 100, 200, 100, 'P', 1, 0, 1);//p_hp,p_pp,b_hp,b_pp,turn,prob,level,isleaf
	
	if (argv[1][4] == '1') {
		list<BattleNode*>* l = new list<BattleNode*>;
		l = createLevel(&first_node, stoi(argv[2]), stoi(argv[2]));

		for (list<BattleNode*>::iterator it = l->begin(); it != l->end(); ++it) {
			cout << *(*it) << endl;
		}
	}
	if (argv[1][4] == '2') {
		list<BattleNode*>* graph = new list<BattleNode*>;
		graph = createLevel(&first_node, stoi(argv[2]), stoi(argv[2]));

		if (argv[3][0] == 'd') {
			auto start = chrono::high_resolution_clock::now();
			DFS(&first_node);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			cout << "RUNNING TIME: "
				<< duration.count() << " microseconds" << endl;
		}
		else if (argv[3][0] == 'b') {
			auto start = chrono::high_resolution_clock::now();
			BFS(&first_node);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			cout << "RUNNING TIME: "
				<< duration.count() << " microseconds" << endl;
		}
	}
	if (argv[1][4] == '3') {
		if (argv[2][0] == 'p') {
			list<BattleNode*>* l = new list<BattleNode*>;
			l = createLevel(&first_node, 10, 10);
			BFSFind(&first_node, 'P');
		}
		else if (argv[2][0] == 'b') {
			list<BattleNode*>* l = new list<BattleNode*>;
			l = createLevel(&first_node, 10, 10);
			BFSFind(&first_node, 'B');
		}
	}
	

	return 0;

    
}


