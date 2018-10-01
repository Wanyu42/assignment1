#include <iostream>
#include <iomanip>
#include <cmath>
#include "trainer.h"
#include "arena.h"

using namespace std;

Trainer** trainers = NULL;
int trainerCount = 0;

Kun* attacker = NULL;
Kun* defender = NULL;

void manageTrainers();
void manageArena();

int main() {
    std::cout<<std::setprecision(4);
    //Trainer* a = new Trainer("hu");
    //a->printDetails();

    bool exit = false;

    while (!exit) {
        int selection = -1;

        cout<<"\n******* Pokunmon Go! *******"<<endl;
        cout<<"Please enter your choice:"<<endl;
        cout<<"1. Manage Trainers"<<endl;
        cout<<"2. Go To Arena!"<<endl;
        cout<<"0. Leave Pokunmon Go"<<endl;

        cin>>selection;

        switch (selection) {
            case 0:
                exit = true;
                break;
            case 1:
                manageTrainers();
                break;
            case 2:
                manageArena();
                break;
            default:
                cout<<"Invalid Choice!"<<endl;
                break;
        }
    }

    cout<<"******* Goodbye! *******"<<endl;

    if (trainers) {
        for (int i=0;i<trainerCount;i++) delete trainers[i];
        delete [] trainers;
    }
    if (attacker) delete attacker;
    if (defender) delete defender;
    return 0;
}

void addItem(Trainer* trainer) {
    string name;
    double hp, atk, def;
    cout<<"Enter Item's Name: "<<endl;
    cin>>name;
    cout<<"Enter Item's hp, attack & defense values: "<<endl;
    cin>>hp>>atk>>def;
    Item* item = new Item(name, hp, atk, def);
    trainer->getBackpack().addItem(item);

    cout<<"New Item \""<<item->getName()<<"\" Added To Trainer \""<<trainer->getName()<<"\"!"<<endl;
    item->printDetails();
}

void removeItem(Trainer* trainer) {
    Item** items = trainer->getBackpack().getItems();
    int itemCount = trainer->getBackpack().getItemCount();

    if (!items) cout<<"There're no items in backpack at this moment."<<endl;
    else {
        int selection = -1;
        for (int i=0;i<itemCount;i++) cout<<"Item "<<i<<": "<<items[i]->getName()<<endl;
        cout<<"Which item do you want to remove?"<<endl;
        cin>>selection;
        if (selection >= 0 && selection < itemCount) {
            trainer->getBackpack().removeItem(items[selection]);
            cout<<"Item removed from trainer!"<<endl;
        } else cout<<"Invalid Choice!"<<endl;
    }
}

void addKun(Trainer* trainer) {
    string name;
    cout<<"Enter Kun's Name: "<<endl;
    cin>>name;

    Kun* kun = new Kun(name);
    trainer->getKunGroup().addKun(kun);

    cout<<"New Kun \""<<kun->getName()<<"\" Added To Trainer \""<<trainer->getName()<<"\"!"<<endl;
    kun->printDetails();
}

void removeKun(Trainer* trainer) {
    Kun** kuns = trainer->getKunGroup().getKuns();
    int kunCount = trainer->getKunGroup().getKunCount();

    if (!kuns) cout<<"There're no kuns in kungroup at this moment."<<endl;
    else {
        int selection = -1;
        for (int i=0;i<kunCount;i++) cout<<"Kun "<<i<<": "<<kuns[i]->getName()<<endl;
        cout<<"Which kun do you want to remove?"<<endl;
        cin>>selection;
        if (selection >= 0 && selection < kunCount) {
            trainer->getKunGroup().removeKun(kuns[selection]);
            cout<<"Kun removed from trainer!"<<endl;
        } else cout<<"Invalid Choice!"<<endl;
    }
}

void manageKun(Kun* kun) {
    bool exit = false;

    while (!exit) {
        int selection = -1;

        cout<<"\n******* Kun \""<<kun->getName()<<"\"! *******"<<endl<<endl;
        cout<<"Please enter your choice"<<endl;
        cout<<"1. View Kun Detail"<<endl;
        cout<<"2. Set Kun Stats (HP, ATTACK & DEFENSE)"<<endl;
        cout<<"3. Gain Experience"<<endl;
        cout<<"4. Add Move"<<endl;
        cout<<"5. Restore HP"<<endl;
        cout<<"0. Go Back"<<endl;

        cin>>selection;

        switch (selection) {
            case 0:
                exit = true;
                break;
            case 1:
                kun->printDetails();
                break;
            case 2: {
                double hp, atk, def;
                cout<<"Enter new HP, ATTACK and DEFENSE values: "<<endl;
                cin>>hp>>atk>>def;
                kun->setHP(hp);
                kun->setAttack(atk);
                kun->setDefense(def);
                cout<<kun->getName()<<"'s stats successfully updated! New stats: "<<endl;
                kun->printDetails();
                break;
            }
            case 3: {
                double exp;
                cout<<"Enter newly gained experience: "<<endl;
                cin>>exp;
                kun->gainExperience(exp);
                cout<<kun->getName()<<"successfully gained experience! New stats: "<<endl;
                kun->printDetails();
                break;
            }
            case 4: {
                int move;
                cout<<"What skill would you like to add?"<<endl;
                cout<<"(0 - WATER_SPRAY, 1 - HYDRO_PUMP, 2 - AQUA_RING)"<<endl;
                cin>>move;
                if (move>=0 && move<3) {
                    kun->addMove(static_cast<Move>(move));
                    cout<<"Move successfully added! New stats: "<<endl;
                    kun->printDetails();
                } else cout<<"Invalid Choice!"<<endl;
                break;
            }
            case 5:
                kun->heal();
                cout<<kun->getName()<<"'s HP has been restored"<<endl;
                break;
            default:
                cout<<"Invalid Choice!"<<endl;
                break;
        }
    }
}

void createTrainer() {
    string name;
    cout<<"Enter Trainer's Name: "<<endl;
    cin>>name;

    Trainer* trainer = new Trainer(name);
    Trainer** newTrainers = new Trainer*[trainerCount+1];
    for (int i=0;i<trainerCount;i++) newTrainers[i] = trainers[i];
    newTrainers[trainerCount] = trainer;
    if (trainers) delete [] trainers;
    trainers = newTrainers;
    trainerCount++;

    cout<<"New Trainer Created: "<<endl;
    trainer->printDetails();
}

void removeTrainer() {
    int selection = -1;
    if (!trainers) {
        cout<<"There're no trainers at this moment."<<endl;
    } else {
        cout<<"Current Trainers: "<<endl;
        for (int i=0;i<trainerCount;i++) cout<<"Trainer "<<i<<": "<<trainers[i]->getName()<<endl;
        cout<<"Which trainer do you want to remove?"<<endl;
        cin>>selection;
        Trainer** newTrainers = NULL;
        if (selection >= 0 && selection < trainerCount) {
            newTrainers = new Trainer*[trainerCount-1];
            for (int i=0;i<trainerCount;i++) {
                if (i<selection) newTrainers[i] = trainers[i];
                else if (i>selection) newTrainers[i-1] = trainers[i];
                else delete trainers[i];
            }
            trainerCount--;
            delete [] trainers;
            trainers = newTrainers;
            cout<<"Trainer removed!"<<endl;
        } else cout<<"Invalid Choice!"<<endl;
    }
}

void manageTrainer(Trainer* trainer) {
    bool exit = false;

    while (!exit) {
        int selection = -1;

        cout<<"\n******* Trainer \""<<trainer->getName()<<"\"! *******"<<endl<<endl;
        cout<<"Please enter your choice"<<endl;
        cout<<"1. View Trainer Detail"<<endl;
        cout<<"2. Add New Kun"<<endl;
        cout<<"3. Remove Kun"<<endl;
        cout<<"4. Manage Kun"<<endl;
        cout<<"5. Add New Item"<<endl;
        cout<<"6. Remove Item"<<endl;
        cout<<"7. Feed Item To Kun"<<endl;
        cout<<"0. Go Back"<<endl;

        cin>>selection;

        switch (selection) {
            case 0:
                exit = true;
                break;
            case 1:
                trainer->printDetails();
                break;
            case 2:
                addKun(trainer);
                break;
            case 3:
                removeKun(trainer);
                break;
            case 4: {
                Kun** kuns = trainer->getKunGroup().getKuns();
                int kunCount = trainer->getKunGroup().getKunCount();
                int kunSelection = -1;

                if (kuns) {
                    cout<<"Trainer \""<<trainer->getName()<<"\"'s Kuns: "<<endl;
                    for (int i=0;i<kunCount;i++) cout<<"Kun "<<i<<": "<<kuns[i]->getName()<<endl;
                    cout<<"Choose a kun to manage: "<<endl;
                    cin>>kunSelection;
                    if (kunSelection>=0 && kunSelection<kunCount) manageKun(kuns[kunSelection]);
                    else cout<<"Invalid Choice!"<<endl;
                } else cout<<"Trainer \""<<trainer->getName()<<"\" has no kun at this moment."<<endl;
                break;
            }
            case 5:
                addItem(trainer);
                break;
            case 6:
                removeItem(trainer);
                break;
            case 7: {
                Kun** kuns = trainer->getKunGroup().getKuns();
                int kunCount = trainer->getKunGroup().getKunCount();
                int kunSelection = -1;

                Item** items = trainer->getBackpack().getItems();
                int itemCount = trainer->getBackpack().getItemCount();
                int itemSelection = -1;

                if (!kuns) cout<<"Trainer currently has no kuns!"<<endl;
                if (!items) cout<<"Trainer currently has no items!"<<endl;
                if (kuns && items) {
                    cout<<"Trainer \""<<trainer->getName()<<"\"'s Kuns: "<<endl;
                    for (int i=0;i<kunCount;i++) cout<<"Kun "<<i<<": "<<kuns[i]->getName()<<endl;
                    cout<<"Choose a kun to get fed: "<<endl;
                    cin>>kunSelection;

                    cout<<"Trainer \""<<trainer->getName()<<"\"'s Items: "<<endl;
                    for (int i=0;i<itemCount;i++) cout<<"Item "<<i<<": "<<items[i]->getName()<<endl;
                    cout<<"Choose an item to feed to kun: "<<endl;
                    cin>>itemSelection;
                    if (kunSelection >= 0 && kunSelection < kunCount && itemSelection >= 0 && itemSelection < itemCount) {
                        trainer->feedItemToKun(items[itemSelection], kuns[kunSelection]);
                        cout<<"Item successfully fed to kun!"<<endl;
                        cout<<"Trainer new stats: "<<endl;
                        trainer->printDetails();
                                                //--------------------------------
                        cout <<"hahahhahahahahah"<< endl;
                        //----------------------------------------

                    } else cout<<"Invalid Choice!"<<endl;
                }
                break;
            }
            default:
                cout<<"Invalid Choice!"<<endl;
                break;
        }
    }
}

void manageTrainers() {
    bool exit = false;

    while (!exit) {
        int selection = -1;

        cout<<"\n******* Trainers! *******"<<endl<<endl;
        cout<<"Please enter your choice"<<endl;
        cout<<"1. View Current Trainers"<<endl;
        cout<<"2. Create New Trainer"<<endl;
        cout<<"3. Remove Trainer"<<endl;
        cout<<"4. Manage a Trainer"<<endl;
        cout<<"0. Go Back"<<endl;

        cin>>selection;

        switch (selection) {
            case 0:
                exit = true;
                break;
            case 1:
                if (trainers) {
                    cout<<"Current Trainers: "<<endl;
                    for (int i=0;i<trainerCount;i++) cout<<"Trainer "<<i<<": "<<trainers[i]->getName()<<endl;
                } else cout<<"No trainer at this moment."<<endl;
                break;
            case 2:
                createTrainer();
                break;
            case 3:
                removeTrainer();
                break;
            case 4: {
                int trainerSelection = -1;
                if (trainers) {
                    cout<<"Current Trainers: "<<endl;
                    for (int i=0;i<trainerCount;i++) cout<<"Trainer "<<i<<": "<<trainers[i]->getName()<<endl;
                    cout<<"Choose a trainer to manage: "<<endl;
                    cin>>trainerSelection;
                    if (trainerSelection>=0 && trainerSelection<trainerCount) manageTrainer(trainers[trainerSelection]);
                    else cout<<"Invalid Choice!"<<endl;
                } else cout<<"No trainer at this moment."<<endl;
                break;
            }
            default:
                cout<<"Invalid Choice!"<<endl;
                break;
        }
    }
}

void manageKunBattle() {
    bool exit = false;

    while (!exit) {
        int selection = -1;

        cout<<"\n******* Kun Battle! *******"<<endl<<endl;
        cout<<"1. View Current Attacker & Defender"<<endl;
        cout<<"2. Create / Modify Attacker"<<endl;
        cout<<"3. Create / Modify Defender"<<endl;
        cout<<"4. Battle!"<<endl;
        cout<<"0. Go Back"<<endl;

        cin>>selection;
        switch (selection) {
            case 0:
                exit = true;
                break;
            case 1:
                cout<<"Attacker: "<<endl;
                if (attacker) attacker->printDetails();
                else  cout<<"NULL"<<endl;
                cout<<"Defender: "<<endl;
                if (defender) defender->printDetails();
                else  cout<<"NULL"<<endl;
                break;
            case 2: {
                if (!attacker) {
                    string name;
                    cout<<"Enter Attacker's Name: "<<endl;
                    cin>>name;
                    Kun* kun = new Kun(name);
                    attacker = kun;
                    cout<<"Attacker successfully created!"<<endl;
                } else {
                    manageKun(attacker);
                }
                break;
            }
            case 3: {
                if (!defender) {
                    string name;
                    cout<<"Enter Defender's Name: "<<endl;
                    cin>>name;
                    Kun* kun = new Kun(name);
                    defender = kun;
                    cout<<"Defender successfully created!"<<endl;
                } else {
                    manageKun(defender);
                }
                break;
            }
            case 4:
                if (!attacker) cout<<"Attacker doesn't exist"<<endl;
                if (!defender) cout<<"Defender doesn't exist"<<endl;
                if (attacker && defender) {
                    CombatResult result = Arena().battle(attacker, defender);
                    switch (result) {
                        case ATTACKER_WINS:
                            cout<<"Attacker wins! Updated kuns' stats: "<<endl;
                            break;
                        case DEFENDER_WINS:
                            cout<<"Defender wins! Updated kuns' stats: "<<endl;
                            break;
                        case ENDLESS:
                            cout<<"Endless battle! Updated kuns' stats: "<<endl;
                            break;
                        case DIETOGETHER:
                            cout<<"Two kuns died together! Updated kuns' stats: "<<endl;
                            break;
                    }
                    cout<<"--- Attacker --- "<<endl;
                    attacker->printDetails();
                    cout<<"--- Defender --- "<<endl;
                    defender->printDetails();
                    cout<<"\nRemember to restore kun's HP"<<endl;
                    break;
                }
            default:
                cout<<"Invalid Choice!"<<endl;
                break;
        }
    }
}

void manageArena() {
    bool exit = false;

    while (!exit) {
        int selection = -1;

        cout<<"\n******* Arena! *******"<<endl<<endl;
        cout<<"1. Do Battle Between Trainers!!!"<<endl;
        cout<<"2. Do Battle Between Kuns!!!"<<endl;
        cout<<"0. Go Back"<<endl;

        cin>>selection;

        switch (selection) {
            case 0:
                exit = true;
                break;
            case 1: {
                if (trainerCount < 2) cout<<"Number of trainers is less than 2, please add more trainers."<<endl;
                else {
                    int attacker = -1, defender = -1;
                    for (int i=0;i<trainerCount;i++) cout<<"Trainer "<<i<<": "<<trainers[i]->getName()<<endl;
                    cout<<"Choose the attacker!"<<endl;
                    cin>>attacker;
                    cout<<"Choose the defender!"<<endl;
                    cin>>defender;
                    if (attacker == defender) cout<<"Attacker shouldn't be the same as defender."<<endl;
                    if (!(attacker >= 0 && attacker < trainerCount && defender >= 0 && defender < trainerCount)) cout<<"Attacker or defender index invalid."<<endl;
                    if (attacker >= 0 && attacker < trainerCount && defender >= 0 && defender < trainerCount && attacker != defender) {
                        cout<<"Battle Finished!"<<endl;
                        Trainer* winner = Arena().battle(trainers[attacker], trainers[defender]);
                        cout<<"Winner is ... "<<endl;
                        winner->printDetails();
                    }
                }
                break;
            }
            case 2:
                manageKunBattle();
                break;
            default:
                cout<<"Invalid Choice!"<<endl;
                break;
        }
    }
}
