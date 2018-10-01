#include "trainer.h"

Trainer::Trainer(string name) : name(name){}

string Trainer::getName() const{
	return this->name;
}

Backpack& Trainer::getBackpack(){
	return this->backpack;
}

KunGroup& Trainer::getKunGroup(){
	return this->kunGroup;
}

void Trainer::feedItemToKun(Item* item, Kun* kun){
	bool kunbelongs = this->kunGroup.hasKun(kun);
	bool itembelongs = this->backpack.hasItem(item);
	if(kunbelongs && itembelongs){
		kun->eatItem(item);
		this->backpack.removeItem(item);
	}
}

void Trainer::receiveNewbornKunFromProf(){
	Kun* newKun = new Kun;
	this->kunGroup.addKun(newKun);
}

void trainKunInTheWild(Kun* kun, int times = 1){
	kun->gainExperience(100*times);
}

