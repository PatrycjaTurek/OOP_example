#pragma once
#include "Character.h"
class Fighter : public Character
{

public:
	Fighter();
	Fighter(std::string, unsigned);
	~Fighter();
	void LevelUP();

	friend class Cleric;
	friend void DebuffDMG();//TODO
	friend void DebuffDEF();//TODO
};

