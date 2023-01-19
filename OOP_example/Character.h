#pragma once
#include "CharacterInterface.h"
//#include "Item.h"
class Character  
{
protected:

	int health;
	unsigned int level;
	unsigned int maxhealth;
	unsigned int maxmeleeDMG;
	int maxmeleeDEF;
	int maxmagicDEF;

	unsigned int meleeDMG;//after de/ -buffing
	int meleeDEF;//after de/ -buffing
	int magicDEF;//after de/ -buffing
	void ResetStats();
	void ResetBuffs();

public: 

	Character();
	~Character();
	Character(std::string, unsigned int);
	int getHealth() { return this->health; };
//	int Attack();
	bool Attack(Character&);
	void GetHit(unsigned int, dmgtype);
	void LevelUP();
	void DecreaseDMG(int);
	void DecreaseDEF(int);


	std::string name;

					  
	//	void UseItem(Item);
};
