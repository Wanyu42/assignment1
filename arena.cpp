#include "arena.h"

Arena::Arena() : MAX_BATTLE_TIME(1000) ,MAX_NUM_OF_ROUNDS(1000){}

CombatResult Arena::battle(Kun* attacker, Kun* defender){
	//init battle conditions
	int currentRound = 0;

	int attacker_atk = attacker->getAttack();
	int attacker_def = attacker->getDefense();

	int defender_atk = defender->getAttack();
	int defender_def = defender->getDefense();

	int attackerhp = attacker->getHP();
	int defenderhp = defender->getHP();

	int attacker_current_atk, defender_current_atk, attacker_current_def, defender_current_def;

	int attacker_damage, defender_damage, attacker_heal, defender_heal;

	Move attacker_current_move;
	Move defender_current_move;

	int attacker_Move_Count, defender_Move_Count;
	Move* attacker_move_list;
	Move* defender_move_list;
	if(attacker->getMoveCount() > 0){
		attacker_Move_Count = attacker->getMoveCount();
		attacker_move_list = attacker->getMoveList();
	}
	else{
		attacker_Move_Count = 1;
		Move attacker_move_list_default[] = {WATER_SPRAY};
		attacker_move_list = &attacker_move_list_default[0];
	}

	if(defender->getMoveCount() > 0){
		defender_Move_Count = defender->getMoveCount();
		defender_move_list = defender->getMoveList();
	}
	else{
		defender_Move_Count = 1;
		Move defender_move_list_default[] = {WATER_SPRAY};
		defender_move_list = &defender_move_list_default[0];
	}

	bool finisher = false;

	do{
		attacker_current_move = attacker_move_list[currentRound % attacker_Move_Count];
		defender_current_move = defender_move_list[currentRound % defender_Move_Count];

		//attacker move
		switch(attacker_current_move){
			case WATER_SPRAY:
				attacker_current_atk = attacker_atk;
				attacker_current_def = attacker_def;
				break;
			case HYDRO_PUMP:
				attacker_current_atk = attacker_atk * 1.5;
				attacker_current_def = attacker_def * 0.7;
				break;
			case AQUA_RING:
				attacker_current_atk = attacker_atk;
				attacker_current_def = attacker_def;
				break;
		}

		switch(defender_current_move){
			case WATER_SPRAY:
				defender_current_atk = defender_atk;
				defender_current_def = defender_def;
				break;
			case HYDRO_PUMP:
				defender_current_atk = defender_atk * 1.5;
				defender_current_def = defender_def * 0.7;
				break;
			case AQUA_RING:
				defender_current_atk = attacker_atk;
				defender_current_def = defender_def;
				break;
		}
		//calculate the damage and heal value;
		//for attacker
		if(attacker_current_move == AQUA_RING){
			attacker_damage = 0;
			attacker_heal = 5;
		}
		else{
			attacker_damage = attacker_current_atk - defender_current_def;
			if(attacker_damage < 1)
				attacker_damage = 1;
			attacker_heal = 0;
		}
		//for defender
		if(defender_current_move == AQUA_RING){
			defender_damage = 0;
			defender_heal = 5;
		}
		else{
			defender_damage = defender_current_atk - attacker_current_def;
			if(defender_damage < 1)
				defender_damage = 1;
			attacker_heal = 0;
		}

        attackerhp = attackerhp - defender_damage + attacker_heal;
        defenderhp = defenderhp - attacker_damage + defender_heal;

		currentRound++;

		if(attackerhp <= 0 || defenderhp <= 0 || currentRound > this->MAX_NUM_OF_ROUNDS)
			finisher = true;

	}while(!finisher);

	CombatResult result;
	if(attackerhp <= 0 && defenderhp > 0)
		result = DEFENDER_WINS;
	else if(attackerhp > 0 && defenderhp <= 0)
		result = ATTACKER_WINS;
	else if(attackerhp <= 0 && defenderhp <= 0)
		result = DIETOGETHER;
	else if(currentRound > this->MAX_NUM_OF_ROUNDS)
		result = ENDLESS;

	return result;
}

Trainer* Arena::battle(Trainer* attacker, Trainer* defender){
	clock_t t = clock();

}
