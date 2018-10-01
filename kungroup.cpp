#include "kungroup.h"

KunGroup::KunGroup() : kuns(NULL),kunCount(0) {}
KunGroup::~KunGroup() {
	for(int i = 0; i < this->kunCount; i++){
		delete this->kuns[i];
	}
	if(this->kuns != NULL)
		delete [] this->kuns;
}

Kun** KunGroup::getKuns() const{ return this->kuns;}

Kun* KunGroup::getKun(string name) const{
	for(int i = 0; i < this->kunCount; i++){
		if(this->kuns[i]->getName() == name)
			return this->kuns[i];
	}
	return NULL;
}

bool KunGroup::hasKun(Kun* kun) const{
	for(int i = 0; i < this->kunCount; i++){
		if(this->kuns[i] == kun)
			return true;
	}
	return false;
}

void KunGroup::addKun(Kun* kun){
	bool existed = this->hasKun(kun);
	if(existed == false){
		Kun** newKuns = new Kun* [this->kunCount + 1];
		for(int i = 0; i < this->kunCount ; i++){
			newKuns[i] = this->kuns[i];
		}
		newKuns[this->kunCount] = kun;
		delete [] this->kuns;
		this->kuns = newKuns;
		this->kunCount++;
	}
}

void KunGroup::removeKun(Kun* kun){
	if(this->hasKun(kun)){
		if(this->kunCount > 1){
			int i , j;
			Kun ** Modi = new Kun* [this->kunCount - 1];
			for(i = 0, j = 0; i < this->kunCount; i++){
				if(kun == this->kuns[i]){
					delete kun;
				}
				else{
					Modi[j] = this->kuns[i];
					j++;
				}
			}
			delete [] this->kuns;
			this->kuns = Modi;
			this->kunCount--;
		}
		else if(this->kunCount == 1){
			delete kun;
			delete [] this->kuns;
			this->kuns = NULL;
		}
	}
}

int KunGroup::getKunCount() const{
	return this->kunCount;
}
