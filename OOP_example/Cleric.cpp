#include "Cleric.h"

void Cleric::ResetStats()
{
	ResetBuffs();
	health = maxhealth;
	mana = maxMana;
};

Cleric::Cleric(std::string name, unsigned int level)
{
	this->name = name;
	this->level = level;
	maxhealth = 15;
	health = 15;
	maxmeleeDMG = 2;
	meleeDMG = 2;

	maxmeleeDEF = 2;
	maxmagicDEF = 8;

	meleeDEF = 2;
	magicDEF = 8;

	maxMana = 10;
	mana = 10;

	while (this->level < level)
	{
		LevelUP();
	}
}

Cleric::Cleric()
{

};

Cleric::~Cleric()
{

};

void Cleric::Heal(Fighter &Target)
{
	Target.health += rand()%5 + level;
	std::cout << "\t Cleric healed " << Target.name << " to " << Target.health << std::endl;
};

bool Cleric::Attack(Character& Target)
{
	//cleric's pacifists so no dmg, debuff instead
	std::cout << "\t Cleric debuffed " << Target.name;
	if (rand() % 2)
	{
		Target.DecreaseDMG(level);
		std::cout << " damage \n ";
	}
	else
	{
		Target.DecreaseDEF(level);
		std::cout << " defence \n ";
	}
	return false;
};
bool Cleric::Attack(Character& Target, Character& Target2 )
{
	Target.DecreaseDMG(level);
	std::cout << "\t Cleric debuffed " << Target.name<< "damage \n ";

	Target.DecreaseDEF(level);
	std::cout << "\t Cleric debuffed " << Target2.name <<"defence \n ";

	return false;
}

bool Cleric::FindToHeal(std::vector<Fighter>& Teammates)
{
	if (Teammates.empty()) return false;

	int minHP = 10000;
	int whichOne = -1;
	int iterator = 0;
	for (auto& tmpF : Teammates)
	{
		if (tmpF.health > tmpF.maxhealth)
		{
			continue;
		}
		if (tmpF.health < minHP)
		{
			minHP == tmpF.health;
			whichOne = iterator;
		}
		iterator++;
	}
	if (whichOne == -1)
	{
		return false;
	}

	Heal(Teammates[whichOne]);
	return true;
};