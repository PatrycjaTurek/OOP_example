#pragma once
#include "Fighter.h"

class Cleric : public Character
{
	int maxMana;
	int mana;
	void ResetStats();// only diference is having mana and maxMana stats
	void Heal(Fighter&);// heal teammates
public:
	Cleric();
	~Cleric();
	Cleric(std::string, unsigned);
	bool FindToHeal(std::vector<Fighter> &);//check if anyone in Fighter-vector need healing
	bool Attack(Character&); // pacific version of "harming" cuz clerics
	bool Attack(Character&, Character&);// AOE version of pacific "attack"
};

