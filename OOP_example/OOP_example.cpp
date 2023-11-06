// OOP_example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include "Game.h"

int main(int argc, char* args[])
{
 //   Cleric* C = new Cleric();
	srand(time(NULL));
    Game* G = new Game();
	while (G->keepGoing)
	{

		G->PlayATurn();
	}
	G->~Game(); //needed to call deconstructor cuz of dynamic object
	delete G;
	return 1;
}
