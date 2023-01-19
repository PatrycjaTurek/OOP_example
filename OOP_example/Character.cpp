#include "Character.h"

Character::Character(std::string name, int level)
{
//	this->level = level;
	this->level = 1;
	this->name = name;
	maxhealth = 20;
	health = 20;
	maxmeleeDMG = 5;
	meleeDMG = 5;

	maxmeleeDEF = 2;
	maxmagicDEF = 2;

	meleeDEF = 2;
	magicDEF = 2;

	while (this->level < level)
	{
		LevelUP();
	}
};

Character::Character()
{
	level = 1;
	maxhealth = 20;
	health = 20;
	maxmeleeDMG = 5;
	meleeDMG = 5;

	maxmeleeDEF = 2;
	maxmagicDEF = 2;

	meleeDEF = 2;
	magicDEF = 2;

};

Character::~Character()
{
}

bool Character::Attack(Character& Target)
{

	int tmpDMG = meleeDMG;
	switch (rand() % 19)
	{
	case 19:// D20 crit  hit 20
	{
		tmpDMG = ceil(meleeDMG * 1.5);
		break;
	}
	case 0: // D20 crit miss 0
	{
		tmpDMG = floor(meleeDMG / 2);
		break;
	}
	}
	int healthTMP = Target.getHealth();

	Target.GetHit(tmpDMG,physic);
	if (healthTMP != Target.getHealth())
	{
		std::cout << "\t" << name << " lowered " << Target.name << "'s from " << Target.getHealth() << " to " << Target.getHealth() << std::endl;
	}
	else
	{
		std::cout << "\t" << name << " waged attack against " << Target.name << " but armor was too strong" << std::endl;
	}
	if (Target.health > 0)
	{
		return true;
	}
	std::cout << "  " << Target.name << " has died \n";
	return false;
	//	Target.GetHit(tmpDMG,physic);
};

void Character::GetHit(int dmg, dmgtype type)
{
	if (type == physic)
	{
		if (dmg - meleeDEF > 0)
		{
			health -= dmg - meleeDEF;
		}
	}
	else if (type == magic)
	{
		if (dmg - magicDEF > 0)
		{
			health -= dmg - magicDEF;
		}
	}
	if (health < 0)
	{
		health = 0; 
	}
	
};

void Character::LevelUP()
{
	maxhealth += rand() % (level + 5 ) + 5 ;
	maxmagicDEF += rand() % level + 5;
	maxmeleeDEF += rand() % level  +2;
	maxmeleeDMG += rand() % (level + 5) + 5 ;
	level++;
	ResetStats();
};

void Character::ResetStats()
{
	health = maxhealth;
	ResetBuffs();
};

void Character::ResetBuffs()
{
	meleeDEF = maxmeleeDEF;
	meleeDMG = maxmeleeDMG;
	magicDEF = magicDEF;
};

void Character::DecreaseDMG(int howMuch)
{
	meleeDMG -= howMuch;
	if (meleeDMG < 3) meleeDMG = 3;
};
void Character::DecreaseDEF(int howMuch)
{
	magicDEF -= howMuch;
	if (magicDEF < 1) magicDEF = 1;

	meleeDMG -= howMuch;
	if (meleeDMG < 1) meleeDMG = 1;
};