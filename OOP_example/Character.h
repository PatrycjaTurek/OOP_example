#pragma once
#include "CharacterInterface.h"
//#include "Item.h"
class Character  
{
protected:

	int health;
	int level;
	int maxhealth; 

	int maxmeleeDMG;
	int maxmeleeDEF;
	
	//magic demage will be added later TODO
	int magicDEF;//after de/ -buffing
	int maxmagicDEF;

	bool wounded;//if that character has health < maxhealth

	int meleeDMG;//after de/ -buffing
	int meleeDEF;//after de/ -buffing

	void ResetStats();//  set health to max and call ResetBuffs()
	void ResetBuffs(); //set damage and defence stats to max option 

public: 

	Character();
	virtual ~Character();
	Character(std::string, int); //making character, take name and level
	int getHealth() { return this->health; }; // return unaccesable variable encapsulation example
//	int Attack();
	virtual bool Attack(Character&); // return true on succesfull attack( or other action)
	virtual void GetHit(int, dmgtype);// calculate result of getting hit, take flat dmg and dmg type
	virtual void LevelUP();// strenght stats and heal up
	virtual void DecreaseDMG(int);// //
	virtual void DecreaseDEF(int);


	std::string name;

};
