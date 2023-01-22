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
	EmptyTeams();// clear memory , just for be sure

	charactersLevel = rand()% 5 + 2;

	for (int i = 0; i < sizeOfTeam; i++)
	{
		Fighter* FighterTMP = new Fighter( ("Player" + std::to_string(i+1) ), charactersLevel);
		PlayerTeam.push_back(*FighterTMP);
		delete FighterTMP;
	}
	
	PlayersCleric = new Cleric("Cleric ", charactersLevel); // he's not in vector of PCs beacuse he can't win game alone

	PrepareRoom();
	system("CLS");// to clear console from characters Empty Teams couts

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

void Game::DoPC_Turn()
{//TODO change it to be controlable by player
//check if character's still alive
	if (PlayersCleric->getHealth() > 0)
	{
		if (!PlayersCleric->FindToHeal(PlayerTeam))//if there's noone to heal cleric will pray to weak their enemies
		{
			if (EnemyTeam.size() > 1 & rand() % 20 >= 15)// if enemy team has more that 1 member and "roll" 15 or more it will debuff 2 enemies
			{
				PlayersCleric->Attack(EnemyTeam[rand() % EnemyTeam.size()], EnemyTeam[rand() % EnemyTeam.size()]);//but pacifist way
			}
			else if (!EnemyTeam.empty())
			{
				PlayersCleric->Attack(EnemyTeam[rand() % EnemyTeam.size()]);//but pacifist way
			}

		}
	}
};

void Game::PlayerTeamAttack()
{

	DoPC_Turn(); // Cleric is little different than other in this team

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
		if (rand() % (PlayerTeam.size() + 1) == 0 && PlayersCleric->getHealth() >0) //check if enemy kill cleric
		{
			tmpEnemy.Attack(*PlayersCleric);
			continue; // to skip rest of loop
		}

		if (PlayerTeam.size() == 1)// to not use rand if there's only 1 enemy
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
	//check if game has ended 
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
	//if game didn't end proceed with checking if room's enmpty
	if(EnemyTeam.empty())
	{
		std::cout << "\n\nRoom's empty "<< turn<<"\n\n";
		score += 100;

		if (TurnsUntilLevelUP == 0)// if players team should level now
		{
			LevelUP();
			TurnsUntilLevelUP = 6;// set next level up at 6 rooms from now
		}
		TurnsUntilLevelUP--;
		PrepareRoom(); // spawn enemy team
	}
	turn++;

	PlayerTeamAttack(); //player team's turn
	EnemyTeamAttack(); //enemy's turn
};
void Game::PrepareRoom()
{
	turn++;
	charactersLevel += rand() %4 -2 ;
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