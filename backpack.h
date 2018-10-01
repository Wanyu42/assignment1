#ifndef BACKPACK_H
#define BACKPACK_H

#include <string>
#include <iostream>
#include "item.h"

using namespace std;

class Backpack {

public:

    /*
     *  constructor, initialize items to be NULL and itemCount to be 0
     */
    Backpack();

    /*
     *  destructor, remember to deallocate any dynamically-allocated memory
     */
    ~Backpack();

    /*
     *  return the items stored
     */
    Item** getItems() const;

    /*
     *  find an item by its name
     *  returns the first found item with the same name
     *  if not found, return NULL
     */
    Item* getItem(string name) const;

    /*
     *  check whether the item exists in the curret items list
     */
    bool hasItem(const Item* item) const;

    /*
     *  add an item to items
     *  first check whether the item has already been added
     *  if not, add the item to the last place, and update itemCount
     */
    void addItem(Item* item);

    /*
     *  remove an item from items
     *  modify the current items list, delete the item, and update itemCount
     */
    void removeItem(Item* item);

    /*
     *  return itemCount
     */
    int getItemCount() const;

    /*
     *  helper function to print Backpack's details
     */
    inline void printDetails() const {
        cout<<"\nBackpack Details:\n";
        for (int i=0;i<itemCount;i++) {
            cout<<"\tItem "<<i<<": ";
            items[i]->printDetails();
        }
    };

private:

    Item** items;   // list for storing items

    int itemCount;  // current number of items stored
};

#endif /* BACKPACK_H */
