#include "backpack.h"
//default constructor
Backpack::Backpack():itemCount(0),items(NULL){}
//default destructor deleting the items list
Backpack::~Backpack(){
	int i;
	//destroy the items
	for(i = 0; i < this->itemCount; i++){
		delete *(this->items + i);
	}
	//destroy the item pointers
	if(this->items != NULL)
		delete [] this->items;
	this->items = NULL;
}

Item** Backpack::getItems() const{
	return this->items;
}

Item* Backpack::getItem(string name)const {
	int i; Item** ptemback = NULL;
	for(i = 0; i < this->itemCount; i++){
		ptemback = this->items + i;
		if((*ptemback)->getName() == name)
			return *ptemback;
	}
	return NULL;
}

bool Backpack::hasItem(const Item* item) const{
	for(int i = 0; i < this->itemCount; i++){
		if(*(this->items + i) == item)
			return true;
	}
	return false;
}

void Backpack::addItem(Item* item){
	bool existed = this->hasItem(item);
	if(existed == false){
		this->itemCount++;
		Item** newItemlist = new Item* [this->itemCount];
		//copy the whole list into a new temporary list
		for(int i = 0; i < (this->itemCount - 1); i++){
			*(newItemlist + i) = *(this->items + i);
		}
		//ADD the new item
		newItemlist[this->itemCount - 1] = item;

		if(this->items != NULL)
			delete [] this->items;

		this->items = newItemlist;
	}
}

void Backpack::removeItem(Item * item){
	if(this->hasItem(item)){
		if(this->getItemCount() > 1){
			Item** newitemlist = new Item* [this->itemCount - 1];
			//bool findexist = false;
			int i ,j;//i for original, j for new one
			for(i = 0,j = 0; i < this->itemCount ; i++){
				if(this->items[i] == item){
					delete this->items[i];
					//findexist = true;
				}
				else{
					newitemlist[j] = this->items[i];
					j++;
				}
			}
			delete [] this->items;
			this->items = newitemlist;
			this->itemCount--;
		}
		else if(this->getItemCount() == 1){
			delete this->items[0];
			delete [] this->items;
			this->items = NULL;
		}

	}
}

int Backpack::getItemCount() const{
	return this->itemCount;
}
