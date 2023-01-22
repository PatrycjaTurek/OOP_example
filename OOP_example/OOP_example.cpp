// OOP_example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Cleric.h"
#include "Fighter.h"
#include "Character.h"
#include "Game.h"
int main()
{
 //   Cleric* C = new Cleric();
	srand(time(NULL));
    Game* G = new Game();
	while (G->keepGoing)
	{
		G->PlayATurn();
	}
	G->~Game(); //needed to call deconstructor cuz of dynamic object
}
