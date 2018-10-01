#ifndef KUNGROUP_H
#define KUNGROUP_H

#include <iostream>
#include "kun.h"

class KunGroup {

public:

    /*
     *  constructor, initializes kuns to be NULL and kunCount to be 0
     */
    KunGroup();

    /*
     *  destructor, remember to deallocate any dynamically-allocated memory
     */
    ~KunGroup();

    /*
     *  returns the kuns stored
     */
    Kun** getKuns() const;
    /*
     *  find a kun by its name
     *  returns the first found kun with the same name
     *  if not found, return NULL
     */
    Kun* getKun(string name) const;
    /*
     *  check whether the kun exists in the curret kuns list
     */
    bool hasKun(Kun* kun) const;

    /*
     *  add a kun to kuns
     *  first check whether the kun has already been added
     *  if not, add the kun to the last place, and update kunCount
     */
    void addKun(Kun* kun);
    /*
     *  remove a kun from kuns
     *  modify the current kuns list, delete the kun, and update kunCount
     */
    void removeKun(Kun* kun);

    /*
     *  return kunCount
     */
    int getKunCount() const;

    /*
     *  helper function to print KunGroup's details
     */
    inline void printDetails() const {
        cout<<"\nKunGroup Details:\n";
        for (int i=0;i<kunCount;i++) {
            cout<<"\tKun "<<i<<": ";
            kuns[i]->printDetails();
        }
    };

private:

    Kun** kuns;     // list for stored kuns

    int kunCount;   // current number of kuns stored
};

#endif /* KUNGROUP_H */
