#pragma once
#include "pch.h"

enum dmgtype
{
	physic = 0,
	magic = 1,
};


class CharacterInterface
{
public:
	virtual int ResetStats() = 0;
	virtual int LevelUP() = 0;
	virtual int Attack() = 0;
	virtual void GetHit(int, dmgtype) = 0;

};

