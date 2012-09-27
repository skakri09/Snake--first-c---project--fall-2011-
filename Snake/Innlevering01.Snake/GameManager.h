//////////////////////////////////////////////////////////////////////////////
//
//	File: GameManager.h
//
//  Original author: Kristian Skarseth / NITH / 2011
//  Changed by:   
//
//  Description: GameManager is running a console snake game.
//				 The class is using COutputmanager, CInputManager
//				 and CLooptimer by Tomas Sandnes.
//
//			========  Extra in-game settings (extra features)  ========
//					* No wall mode (you can go trough walls)
//					* Mines spawn when food spawn.
//					* 3 Speed levels as well as a custom speed option
//					* Dynamically changing speed
//			===========================================================
//
//	Special notes: 1: All code placed in namespace Santom.
//				   2: Contains MS windows spesific code - NOT OS independent!
//				   3: Code is window size dependant.
//
//////////////////////////////////////////////////////////////////////////////

//Inclusion guard
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

//includes
#include <deque>
#include <iostream>
#include <iomanip>

//headers
#include "inputManager.h"
#include "loopTimer.h"
#include "outputManager.h"

//Namespaces
using namespace std;
using namespace Santom;

//Game Setting constants.
static const string WINDOW_TITLE  =	   "NITH Snake";    //Window title
static const int SCREEN_WIDTH     =	    80;			    //Window Width
static const int SCREEN_HEIGHT    =	    50;				//window Height


// C L A S S   D E C L A R A T I O N
// =================================

class CGameManager
{
public:
	CGameManager();   //CGameManager constructor
	~CGameManager();  //CGameManager destructor

	//Initializes the game window and runs the menu
	void Initialize(); 

	enum eGameStatus{PLAY, QUIT, MENU, GAMEOVER, SETTINGS}; //enum with the games' status (quit, play, gameover, menu)
	enum eDirection{LEFT, RIGHT, UP, DOWN};                 //enum with the 4 directions the snake can move
	enum eGameSpeed{SLOW, MEDIUM, HIGH, CUSTOM};            //enum for the game speed

private:
	eDirection _eDirection;         //the direction of the snake
	eGameStatus _eGameStatus;       //the status of the game (menu/settings/advanced settings/playing/quitting)
	eGameSpeed _eGameSpeed;         //enum for the game speed


	Santom::CInputManager input;    //Object of class InputManager to get player key actions
	Santom::COutputManager output;  //Object of class Outputmanager to write to console
	Santom::CLoopTimer timer;       //Object of class LoopTimer to get time based updates
	
	int _iScore;			    //stores the score of the game
	int _iGameInput;			// stores keystroke done by player, used for navigating the snake and menu
	int _iSnakeXPos;		//x coordinate for the snake body
	int _iSnakeYPos;		//y coordinate for the snake body
	int _iDefaultSnakeXPos;	//the default snake X coordinate
	int _iDefaultSnakeYPos;	//the default snake Y coordinate
	int _iFoodX;			//x coordinate of the food
	int _iFoodY;			//y coordinate of the food
	int _iScoreIncrement;	//the amount of score you gain
	int _iHeadX;			//stores the last X coordinate of the snake head before it's changed in the new loop
	int _iHeadY;			//stores the last y coordinate of the snake head before it's changed in the new loop
	int _iGameSpeed;		//variable used to change gamespeed
	int _iMineX;			//x coordinate for mines
	int _iMineY;			//y coordinate for mines
	
	char _cSnakeHead;	//the char that stores the head of the snake
	char _cSnakeBody;	//the char that's used for the body of the snake
	char _cFood;		//the char that's used for the food
	char _cMine;		//the char that's used for the mine

	bool _bDynamicSpeed;		//when true, gamespeed increases dynamically
	bool _bWalls;				//decides if walls are on or off
	bool _bDelayGrow;			//used to decide if the snake grows or not
	bool _bMines;				//used to decide if mines are enabled or not
	bool _bChangingCustomSpeed; //used for a loops that change numbers with arrow-keys


	//the game loop. It starts after being called form the menu, and runs untill
    //game over or q/q is pressed by player.
	void _gameLoop();
	
	//Started from the gameloop if you get gameover.
	//Will print gameover screen untill player presses q/Q
	void _gameOver(); 

	//the game menu. Will run on game start, and wait for input from player
    //to change to run _gameLoop(), _gameSettings() or quit.
	void _gameMenu();
	
	//Settings screen where ingame settings can be changed, can be called from _gameMenu()
	void _gameSettings(); 
	
	//Prints a mine at a random location if the mine would have 
    //appeared where the snake or a food currently is, it will find a new location
	void _mines();
	
	//Prints a new food on a random location. if the food would have appeared 
	//where the snake allready is, it creates a new location. Called from _gameLoop()
	void _food();

	//Resets settings to default. Called on game launch and can be called from _gameSettings()
	void _defaultSettings();

	deque<int> _dqSnakeX; //deque storing the X coordinates of the snake
	deque<int> _dqSnakeY; //deque storing the Y coordinates of the snake
	
	
};
 
#endif 