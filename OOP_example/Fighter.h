#pragma once
#include "Character.h"
class Fighter : public Character
{

public:
	Fighter();
	Fighter(std::string, unsigned int);
	~Fighter();
	void LevelUP();

	friend class Cleric;
	friend void DebuffDMG();
	friend void DebuffDEF();
};

