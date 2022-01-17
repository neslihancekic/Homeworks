#ifndef POKEMONS
#define POKEMONS

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Attack {
	string attack;
	int pp;
	int accu;
	int damage;
	int firstusage;
public:
	Attack(string a ="0", int p = 0, int ac = 0, int d = 0, int f = 0) {
		attack = a;
		pp = p;
		accu = ac;
		damage = d;
		firstusage = f;
	}
	string getAtt() { return attack; }
	int getPp() { return pp; }
	int getAccu() { return accu; }
	int getDam() { return damage; }
	int getFirst() { return firstusage; }
	friend ostream& operator << (ostream&, Attack&);
};

ostream& operator << (ostream& os, Attack& a)
{
	os << a.attack<<" "<<a.pp<< " " << a.accu <<" " << a.damage<< " " << a.firstusage<<endl;
	return os;
}

class BattleNode {
	int p_hp;
	int p_pp;
	int b_hp;
	int b_pp;
	
	char turn;
	double prob;
	int level;
	bool isleaf;

	string att;
	bool effective;

	BattleNode *mom;

	list<BattleNode*> *children;

public:
	bool visited;
	/*Constructor*/
	BattleNode(int pikh=0, int pikp=0, int blah=0, int blap=0, char t=0, double pro=0, int l=0, bool i=0) {
		p_hp = pikh;
		p_pp = pikp;
		b_hp = blah;
		b_pp = blap;
		turn = t;
		prob = pro;
		level = l;
		isleaf = i;
		effective = false;
		att = "";
		children = NULL;
		mom = NULL;
		visited = false;
	}

	int getPikacPP() { return p_pp; }
	int getBlasPP() { return b_pp; }
	int getPikacHP() { return p_hp; }
	int getBlasHP() { return b_hp; }
	char getTurn() { return turn; }
	double getProb() { return prob; }
	int getLevel() { return level; }
	int getIsleaf() { return isleaf; }

	void setTurn(int t) { turn=t; }
	void setProb(double p) { prob=p; }
	void setIsleaf(int i) { isleaf=i; }

	string getAttack() { return att; }
	string getEffect() {
		if (effective == true) { 
			return "effective"; 
		}else { 
			return "nonefective"; }
	}
	BattleNode* getMother() { return mom; }

	void setAttack(string a) { att = a; }
	void setEffect(bool e) { effective=e; }
	void setMother(BattleNode  *m) {mom = m; }

	void setChildren(list<BattleNode*> *c) { children = c; }
	list<BattleNode*> *getChildren() { return children; }
	friend ostream& operator << (ostream&, BattleNode&);
	
};

ostream& operator << (ostream& os, BattleNode& b)
{

	os << "P_HP:" << b.p_hp << " P_PP:" << b.p_pp << " B_HP:" << b.b_hp << " B_PP:" << b.b_pp << " PROB:" << b.prob;

	/*os << "PIKACHU:" << endl << "HP: " << b.p_hp << endl << "PP: " << b.p_pp << endl;
	os << "BLASTOISE:" << endl << "HP: " << b.b_hp << endl << "PP: " << b.b_pp << endl;
	os << "TURN: " << b.turn << endl;
	os << "PROB: " << b.prob << endl;
	os << "LEVEL: " << b.level << endl;
	os << "ISLEAF: " << b.isleaf << endl;
	if (b.turn == 'P') {
		os << "Blastoise used " << b.att << ". ";
	}
	else {
		os << "Pikachu used " << b.att << ".";
	}
	if (b.effective == true) {
		os << "It's effective." << endl;
	}
	else {
		os << "It's noneffective." << endl;
	}*/
	
	
	return os;

}

#endif
