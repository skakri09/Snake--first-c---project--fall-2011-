///////////////////////////////////////////////////////////////////
//
//	File: Main.cpp
//
//	Original author: Kristian Skarseth / NITH / 2011
//	Changed by:	   -
//
//	Description: Contains the main().
//				 Starts the game.
//
///////////////////////////////////////////////////////////////////

#include "GameManager.h"

int main()
{
	
	//Creates a pointer to object of CGameManager
	CGameManager* snakeGame;
	snakeGame = new CGameManager();
	
	//Initializes game window and runs the menu
	snakeGame->Initialize();
	
	//deletes the pointer
	if(snakeGame)
	{
		delete snakeGame;
		snakeGame = 0;
	}

	return 0;
} //End main()
