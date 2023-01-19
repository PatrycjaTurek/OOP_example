#pragma once
#include "Cleric.h"

class Game
{
	unsigned int roomsLEFT;
	unsigned int turn;
	unsigned int sizeOfTeam;
	unsigned int sizeOfEnemyTeam;
	unsigned int TurnsUntilLevelUP;
	std::vector<Character> EnemyTeam;
	std::vector<Fighter> PlayerTeam;
	Cleric* PlayersCleric;

	void PlayerTeamAttack();
	void EnemyTeamAttack();
	void LevelUP();

public:
	bool keepGoing;
	int score;
	bool win;

	Game();
	~Game();
	void PrepareRoom();
	void PlayATurn();
	void EmptyTeams();
};

