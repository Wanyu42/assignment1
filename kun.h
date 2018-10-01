#ifndef KUN_H
#define KUN_H

#include <string>
#include <iostream>
#include "item.h"

using namespace std;

enum Move { WATER_SPRAY, HYDRO_PUMP, AQUA_RING };

class Kun {

public:
    Kun();                      // default constructor
    Kun(string name);           // conversion constructor
    Kun(const Kun& another);    // copy constructor, remember to deep copy moveList
    ~Kun();                     // destuctor, remember to deallocate any dynamically-allocated memory

    string getName() const;
    void setName(string name);          // methods for getting & setting name

    double getHP() const;
    void setHP(double hp);              // methods for getting & setting HP

    bool isAlive() const;               // if hp > 0, return true
    void heal();                        // set hp to be level * 10

    double getAttack() const;
    void setAttack(double attack);      // methods for getting & setting attack

    double getDefense() const;
    void setDefense(double defense);    // methods for getting & setting defense

    /*
     *  return level
     */
    int getLevel() const;
    /*
     *  set a new value to level
     *  if level > MAX_LEVEL, do nothing
     *  if level <= current level, do nothing
     *  otherwise, for each level increased, increase HP by 10, attack by 2, and defense by 2
     *  then set experience to 0
     */
    bool increaseLevelTo(int level);

    /*
     *  return experience
     */
    double getExperience() const;

    /*
     *  increase current experience by the new value
     *  if totalExp exceeds level*100, kun should level up
     *  you may use recursion
     *
     *  Example:
     *  initial -> level 1, Exp 0
     *  gainExp(350)
     *  final -> level 3, Exp 50
     */
    bool gainExperience(double experience);

    /*
     *  return moveList
     */
    Move* getMoveList();
    /*
     *  add a move to the current moveList
     *  remember to update moveCount
     */
    void addMove(Move move);
    /*
     *  remove all moves
     *  deallocate memory, and set moveList to NULL
     */
    void removeAllMoves();

    /*
     *  return moveCount
     */
    int getMoveCount() const;

    /*
     *  add the item's stats directy onto kun's stats
     *  do not delete the item
     */
    void eatItem(const Item* item);

    /*
     *  add the kun's stats onto self's stats
     *  do not delete the kun
     *  myHP += kun's HP * 0,1
     *  myATK += kun's ATK * 0.1
     *  myDEF += kun's DEF * 0.1
     *  myEXP += kun's LEVEL * 30
     */
    void eatKun(const Kun* kun);

    /*
     *  helper function to print kun's details
     */
    inline void printDetails() const {
        cout<<"\""<<name.c_str()<<"\": \n\t\tLevel "<<level<<" Exp "<<experience<<", hp "<<hp<<", atk "<<attack<<", def "<<defense<<"\n\t\tMove List: ";
        for (int i=0;i<moveCount;i++) {
            cout<<i<<" - ";
            switch (moveList[i]) {
                case WATER_SPRAY: cout<<"Water Spray; ";  break;
                case HYDRO_PUMP: cout<<"Hydro Pump; "; break;
                case AQUA_RING: cout<<"Aqua Ring; "; break;
            }
        }
        cout<<endl;
    };

private:

    string name;        // kun's name

    double hp;          // kun's hp
    double attack;      // kun's attack
    double defense;     // kun's defense

    int level;          // kun's level
    double experience;  // kun's experience

    Move* moveList;     // kun's move list
    int moveCount;      // kun's move count for move list

    const int MAX_LEVEL;   // the max level that the kun can reach
};

#endif /* KUN_H */
