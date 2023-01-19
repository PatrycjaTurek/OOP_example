#include "Game.h"

Game::Game()
{
	turn = 0;
	keepGoing = true;
	TurnsUntilLevelUP = 2;
	roomsLEFT = 15;
	score = 0;
	win = false;
	sizeOfTeam = 3;
	sizeOfEnemyTeam = 2;
	EmptyTeams();

	unsigned int charactersLevel = rand()% 5 + 2;

	for (int i = 0; i < sizeOfTeam; i++)
	{
		Fighter* FighterTMP = new Fighter( ("Player" + std::to_string(i+1) ), charactersLevel);
		PlayerTeam.push_back(*FighterTMP);
		delete FighterTMP;
	}
	
	PlayersCleric = new Cleric("Cleric ", charactersLevel); // he's not in vector of PCs beacuse he can't win game alone

	PrepareRoom();
	system("CLS");// to clear feedback from characters econstructor from Empty Teams

};
Game::~Game()
{
	if (win)
	{
		std::cout << "\n\n\t you won! ";
	}
	else
	{
		std::cout << "\n\n\t you lose! ";
	}
	std::cout << "with score of "<<score;
	std::cout << "\n\n\ ";
	EmptyTeams();
};

void Game::PlayerTeamAttack()
{
	if (PlayersCleric->getHealth() > 0)
	{
		if (!PlayersCleric->FindToHeal(PlayerTeam))
		{
			if (EnemyTeam.size() > 1)
			{
				PlayersCleric->Attack(EnemyTeam[rand() % EnemyTeam.size()], EnemyTeam[rand() % EnemyTeam.size()]);//but pacifist way
			}
			else if (!EnemyTeam.empty())
			{
				PlayersCleric->Attack(EnemyTeam[rand() % EnemyTeam.size()]);//but pacifist way
			}
		
		}
	}

	for (auto& tmpPlayer : PlayerTeam)
	{
		if (EnemyTeam.empty())
		{
			return;
		}
		if (EnemyTeam.size() == 1)
		{
			if (!tmpPlayer.Attack(EnemyTeam.back() ) )
			{
				EnemyTeam.pop_back();  // character's dead delete this character
			}
		}
		else
		{
			int tmp = rand() % EnemyTeam.size();
			if (!tmpPlayer.Attack(EnemyTeam[tmp]))
			{
				EnemyTeam.erase(EnemyTeam.begin() + tmp);  // character's dead delete this character
			}
		}
	}

};
void Game::EnemyTeamAttack()
{
	for (auto& tmpEnemy : EnemyTeam)
	{
		if (PlayerTeam.empty())
		{
			return;
		}
		if (rand() % (PlayerTeam.size() + 1) == 0 && PlayersCleric->getHealth() >0) //if enemy kill cleric
		{
			tmpEnemy.Attack(*PlayersCleric);
			continue; // to skip rest of loop
		}

		if (PlayerTeam.size() == 1)
		{
			if (!tmpEnemy.Attack(PlayerTeam.back()))
			{
				PlayerTeam.pop_back();  // character's dead delete this character
			}
		}
		else
		{
			int tmp = rand() % PlayerTeam.size();
			if (!tmpEnemy.Attack(PlayerTeam[tmp]))
			{
				PlayerTeam.erase(PlayerTeam.begin() + tmp); // character's dead delete this character
			}
		}
		int i = 0;
	}
};

void Game::PlayATurn()
{
	if (roomsLEFT == 0)
	{
		win = true;
		keepGoing = false;
		return;
	}
	if (PlayerTeam.empty())
	{
		win = false;
		keepGoing = false;
		return;
	}
	if(EnemyTeam.empty())
	{
		std::cout << "Room's empty "<< turn<<"\n";
		score += 100;

		if (TurnsUntilLevelUP == 0)
		{
			LevelUP();
			TurnsUntilLevelUP = 6;
		}
		TurnsUntilLevelUP--;
		PrepareRoom();
	}
	turn++;

	PlayerTeamAttack();
	EnemyTeamAttack();
};
void Game::PrepareRoom()
{
	turn++;
	unsigned int charactersLevel = rand() % (5 +turn) + turn;
	for (int i = 0; i < sizeOfEnemyTeam; i++)
	{
		Character* Enemy = new Character(("Goblin" + std::to_string(i + 1)), charactersLevel);
		EnemyTeam.push_back(*Enemy);
		delete Enemy;
	}
	roomsLEFT--;
}
void Game::EmptyTeams()
{
	while (!EnemyTeam.empty())
	{
		EnemyTeam.pop_back();
	}
	while (!PlayerTeam.empty())
	{
		PlayerTeam.pop_back();
	}
	if (PlayersCleric)
	{
		PlayersCleric->~Cleric();
	}
}

void Game::LevelUP()
{
	for (auto& tmpPlayer : PlayerTeam)
	{
		tmpPlayer.LevelUP();
	}
};