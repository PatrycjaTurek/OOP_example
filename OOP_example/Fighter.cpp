#include "Fighter.h"


Fighter::Fighter()
{
}

Fighter::Fighter(std::string name, unsigned level)
{
	this->name = name;
	this->level = level;
	maxhealth = 30;
	health = 30;
	maxmeleeDMG = 8;
	meleeDMG = 8;

	maxmeleeDEF = 8;
	maxmagicDEF = 1;

	meleeDEF = 8;
	magicDEF = 1;

	while(this->level < level)
	{
		LevelUP();
	}
}
Fighter::~Fighter()
{

}
void Fighter::LevelUP()
{
	maxhealth += rand() % (level + 5) + 2*level;
	maxmagicDEF += rand() % level +  5;
	maxmeleeDEF += rand() % level + 2;
	maxmeleeDMG += rand() % (level + 5) + 5;
	ResetStats();
};
/*
void Fighter::LevelUP()
{
	std::cout << health<<"\n";
	health = +20;
};*/