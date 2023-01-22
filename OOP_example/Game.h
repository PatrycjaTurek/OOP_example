#pragma once
#include "SDLClass.h"
#include "Cleric.h"

class Game: public SDLClass
{
	int shift_Y = floor(screenHeight / (4 * sizeOfTeam + 1)); //ratio used to render
	int shift_X = floor(screenWidth / 10); //ratio used to render
	SDL_Rect rectangle; //used to render sprits


	unsigned int roomsLEFT;// game can't go forever
	unsigned int turn;// if game's during turn or other part of game
	unsigned int charactersLevel;//level of PC, on it depends enemies' level
	unsigned int sizeOfTeam;
	unsigned int sizeOfEnemyTeam;// how mamy enemies, depends of player team's size
	unsigned int TurnsUntilLevelUP;//  how many rooms till PC's level up
	std::vector<Character> EnemyTeam;
	std::vector<Fighter> PlayerTeam;
	Cleric* PlayersCleric;// only character controlled by player TODO

	void PlayerTeamAttack();
	void EnemyTeamAttack();
	void LevelUP();

	void DoPC_Turn();// now it only make cleric-type character paly their turn
	void RenderRoom();
	void RenderNEWRoom();
	void RenderCharacters(std::string, std::string);
	void RenderCharacters(std::string);//turn of character controlled by player 

public:
	bool keepGoing; // if game should keep going or end
	int score;
	bool win;//need to be paired with keepGoing variable

	Game();
	~Game();
	void PrepareRoom();//spawn enemy team
	void PlayATurn();//process with characters actions
	void EmptyTeams();//delete ALL teams
};

