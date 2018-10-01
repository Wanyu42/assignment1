#include "kun.h"

//Default constructor
Kun::Kun() : name("KUN"), hp(10), attack(1), defense(1),
level(1), experience(0), moveList(NULL), moveCount(0), MAX_LEVEL(100) {}
//Conversion constructor
Kun::Kun(string name) : name(name), hp(10), attack(1), defense(1),
level(1), experience(0), moveList(NULL), moveCount(0), MAX_LEVEL(100) {}
//Copy constructor
Kun::Kun(const Kun& another) : name(another.name), hp(another.hp),attack(another.attack),
		defense(another.defense), level(another.level), experience(another.experience),
		moveCount(another.moveCount), MAX_LEVEL(another.MAX_LEVEL) {
	//NEED CHANGE
	if(this->moveCount > 0){
		this->moveList = new Move [this->moveCount];
		for(int i = 0; i < this->moveCount; i++){
			this->moveList[i] = another.moveList[i];
		}
	}
	else
		this->moveList = NULL;
}

//Destructor
Kun::~Kun(){
	if(this->moveList != NULL){
		delete [] this->moveList;
	}
}

//-----------------------------------------------------------------------------------------
string Kun::getName() const{
	return this->name;
}
void Kun::setName(string name) // methods for getting & setting name
{this->name = name;}

// methods for getting & setting HP
double Kun::getHP() const{return this->hp;}
void Kun::setHP(double hp){this->hp = hp;}

bool Kun::isAlive() const // if hp > 0, return true
{
	if(this->hp > 0)
		return true;
	return false;
}
void Kun::heal()// set hp to be level * 10
{
	this->setHP(10*this->level);
}

// methods for getting & setting attack
double Kun::getAttack() const{return this->attack;}
void Kun::setAttack(double attack){this->attack = attack;}

 // methods for getting & setting defense
double Kun::getDefense() const{return this->defense;}
void Kun::setDefense(double defense){this->defense = defense;}

int Kun::getLevel() const{
	return this->level;
}

bool Kun::increaseLevelTo(int level){
	if(level <= this->MAX_LEVEL && level > this->level){
		int difference = level - this->level;
		this->hp += 10*difference;
		this->attack += 2*difference;
		this->defense += 2*difference;
		this->level = level;
		this->experience = 0;
		return true;
	}
	return false;
}

double Kun::getExperience() const{
	return this->experience;
}

bool Kun::gainExperience(double experience){
	int difference = this->experience + experience - 100*this->getLevel();
	if(difference < 0){
		this->experience += experience;
		return false;
	}
	else{
		this->increaseLevelTo(this->getLevel()+1);
		this->gainExperience(difference);
		return true;
	}
}

Move* Kun::getMoveList(){
	return this->moveList;
}

void Kun::addMove(Move move){
	this->moveCount++;
	Move* newMovelist = new Move [moveCount];
	for(int i = 0; i < this->moveCount - 1; i++){
		newMovelist[i] = this->moveList[i];
	}
	newMovelist[moveCount - 1] = move;
	if(this->moveList != NULL){
		delete [] this->moveList;
	}
	this->moveList = newMovelist;
}

void Kun::removeAllMoves(){
	delete [] this->moveList;
	this->moveList = NULL;
	this->moveCount = 0;
}

int Kun::getMoveCount() const{
	return this->moveCount;
}

void Kun::eatItem(const Item * item){
	this->hp += item->getHP();
	this->attack += item->getAttack();
	this->defense += item->getDefense();
}

void Kun::eatKun(const Kun* kun){
	this->hp += kun->getHP() * 0.1;
	this->attack += kun->getAttack() * 0.1;
	this->defense += kun->getDefense() * 0.1;
	this->experience += kun->getLevel() * 30;
}
