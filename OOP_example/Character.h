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
	int maxmagicDEF;

	int meleeDMG;//after de/ -buffing
	int meleeDEF;//after de/ -buffing
	int magicDEF;//after de/ -buffing
	void ResetStats();
	void ResetBuffs();

public: 

	Character();
	~Character();
	Character(std::string, int);
	int getHealth() { return this->health; };
//	int Attack();
	bool Attack(Character&);
	void GetHit(int, dmgtype);
	void LevelUP();
	void DecreaseDMG(int);
	void DecreaseDEF(int);


	std::string name;

					  
	//	void UseItem(Item);
};
