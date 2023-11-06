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


	Init();
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
{
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
	RenderRoom();
	RenderCharacters(PlayersCleric->name);
};

void Game::PlayerTeamAttack()
{

	DoPC_Turn(); // Cleric is little different than other in this team

	for (auto& tmpPlayer : PlayerTeam)
	{
		RenderRoom();
		if (EnemyTeam.empty())
		{
			return;
		}
		if (EnemyTeam.size() == 1)
		{
			if (!tmpPlayer.Attack(EnemyTeam.back() ) )
			{
				RenderCharacters(tmpPlayer.name, EnemyTeam.back().name);
				EnemyTeam.pop_back();  // character's dead delete this character
			}
		}
		else
		{
			int tmp = rand() % EnemyTeam.size();
			if (!tmpPlayer.Attack(EnemyTeam[tmp]))
			{
				RenderCharacters(tmpPlayer.name, EnemyTeam[tmp].name);
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
			RenderCharacters(tmpEnemy.name, PlayersCleric->name);
			continue; // to skip rest of loop
		}

		if (PlayerTeam.size() == 1)// to not use rand if there's only 1 enemy
		{
			if (!tmpEnemy.Attack(PlayerTeam.back()))
			{
				RenderCharacters(tmpEnemy.name, PlayerTeam.back().name);
				PlayerTeam.pop_back();  // character's dead delete this character
			}
		}
		else
		{
			int tmp = rand() % PlayerTeam.size();
			if (!tmpEnemy.Attack(PlayerTeam[tmp]))
			{
				RenderCharacters(tmpEnemy.name, PlayerTeam[tmp].name);
				PlayerTeam.erase(PlayerTeam.begin() + tmp); // character's dead delete this character
			}
		}
		int i = 0;
	}

};

void Game::PlayATurn()
{
	
	CheckForEvents();

	//check if game has ended 
	if (roomsLEFT == 0 || exitprogram)
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
		std::cout << "\n\nRoom "<< turn<<" is empty\n\n";
		score += 100;

		if (TurnsUntilLevelUP == 0)// if players team should level now
		{
			LevelUP();
			TurnsUntilLevelUP = 6;// set next level up at 6 rooms from now
		}
		TurnsUntilLevelUP--;
		PrepareRoom(); // spawn enemy team
	}

	PlayerTeamAttack(); //player team's turn
	EnemyTeamAttack(); //enemy's turn


};



void Game::PrepareRoom()
{
	std::cout << "\n \t new room was made\n";
	turn++;
	if (rand()% 20 <= 5 && EnemyTeam.size() <= 5)
	{
		sizeOfEnemyTeam++;
	}
	else if (rand()% 20 > 18)
	{
		sizeOfEnemyTeam--;
	}

	charactersLevel += rand() %4 -2 ;


	SDL_SetTextureColorMod(GoblinSprite.mTexture, rand() & 22 * 10 + 10, rand() & 22 * 10 + 10, rand() & 22 * 10 + 10);
	for (int i = 0; i < sizeOfEnemyTeam; i++)
	{

		Character *Enemy = new Character(("Goblin" + std::to_string(i + 1)), charactersLevel);
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


void Game::RenderRoom()
{
	SDL_RenderClear(gRenderer);
	Background.Render(gRenderer);
	shift_Y = floor(screenHeight / (4 * sizeOfTeam + 1));
	shift_X = floor(screenWidth / 10);

}

void Game::RenderCharacters(std::string attacker, std::string attackee)
{

	RenderRoom();

	rectangle.y = ceil(screenHeight / 2) + shift_Y * (PlayerTeam.size() - 1);
	rectangle.w = shift_X;
	rectangle.h = shift_Y;


	if (PlayersCleric->name == attackee)
	{
		rectangle.x = floor(shift_X /2 );

		ClericSprite.Render(gRenderer, &rectangle);
		rectangle.y -= shift_Y;
	}
	else if (PlayersCleric->getHealth() > 0)
	{
		rectangle.x = shift_X;
		ClericSprite.Render(gRenderer, &rectangle);
	}

	rectangle.y = ceil(screenHeight / 2);

	for (auto& tmpChar : PlayerTeam)
	{
		rectangle.x = shift_X * 3;

		if (attacker == tmpChar.name)
		{
			rectangle.x += shift_X;
		}
		else if (attackee == tmpChar.name)
		{
			rectangle.x -= shift_X;
		}
		FighterSprite.Render(gRenderer, &rectangle);
		rectangle.y += 2 * shift_Y;
	}
	if (sizeOfEnemyTeam < 4)
	{
		rectangle.y = ceil(screenHeight / 2);
	}
	else
	{
		rectangle.y = ceil(screenHeight / 3);
	}


	for (auto& tmpChar : EnemyTeam)
	{
		rectangle.x = (screenWidth - (shift_X * 3));
		if (attacker == tmpChar.name)
		{
			rectangle.x -= shift_X;
		}
		else if (attackee == tmpChar.name)
		{
			rectangle.x += shift_X;
		}
		GoblinSprite.Render(gRenderer, &rectangle);
		rectangle.y += 2 * shift_Y;
	}
	limitingFrames();
	SDL_RenderPresent(gRenderer);
};

void Game::RenderCharacters(std::string attacker)
{
	RenderRoom();

	if (PlayersCleric->getHealth() > 0)
	{
		rectangle.x = 2* shift_X;
		rectangle.y = ceil( screenHeight / 2) + shift_Y * (PlayerTeam.size() -1 ) ;
		rectangle.w = shift_X;
		rectangle.h = shift_Y;
		ClericSprite.Render(gRenderer, &rectangle);
	}


	rectangle.y = ceil(screenHeight / 2);
	rectangle.x = shift_X * 3;

	for (auto& tmpChar : PlayerTeam)
	{
		FighterSprite.Render(gRenderer, &rectangle);
		rectangle.y += 2 * shift_Y;
	}

	rectangle.x = (screenWidth - (shift_X * 2));

	if (sizeOfEnemyTeam < 4)
	{
		rectangle.y = ceil(screenHeight / 2);
	}
	else
	{
		rectangle.y = ceil(screenHeight / 3);
	}

	for (auto& tmpChar : EnemyTeam)
	{
		GoblinSprite.Render(gRenderer, &rectangle);
		rectangle.y += 2 * shift_Y;
	}
	limitingFrames();
	SDL_RenderPresent(gRenderer);
//	SDL_Delay(500);
}

