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



#include "GameManager.h"


/* ================== P U B L I C  F U N C T I O N S ================== */
/* ==================================================================== */


/* CGameManager constructor */
CGameManager::CGameManager()
{
	srand (static_cast<int>(time(0))); //Seed srand with time. Cast to int to avoid unnessesary warning
}//End CGameManager()


/*CGameManager destructor*/
CGameManager::~CGameManager()
{

}//End ~CGameManager()


/*Initializes game windows and runs the menu*/
void CGameManager::Initialize()
{
	//initializes the game window
	output.Initialize("                                                                              NITH Snake", SCREEN_WIDTH, SCREEN_HEIGHT, TEXT_YELLOW_BRIGHT, BACK_BLACK);
	
	_defaultSettings(); //defaults the settings of the game
	_gameMenu(); //starts the Game Menu

}//End Initialize()



/* ================= P R I V A T E  F U N C T I O N S ================= */
/* ==================================================================== */


/*the game loop. It starts after called form the menu, and runs untill
  game over or q/q is pressed by player.*/
void CGameManager::_gameLoop()
{
	/*resets the timer*/
	timer.Reset();
	
	/*sets the gamespeed*/
	timer.setGameSpeed(_iGameSpeed);
	
	//////////////_iGameSpeedY = _iGameSpeed / (100*80);/////////////////////////////////////
	
	/*resets the snake coordinates before a new game*/
	_dqSnakeX.clear();
	_dqSnakeY.clear();

	/*Resets the score*/
	 _iScore = 0;

	/*defaults and resets the snake possition*/
	 _iSnakeXPos = _iDefaultSnakeXPos;
	 _iSnakeYPos = _iDefaultSnakeYPos;

	/*resets the direction to right*/
	 _eDirection = RIGHT;

    /*clears the screen and prints the menu at bottom of play screen*/
	output.ClearScreen();
	output.SetColor(TEXT_WHITE, BACK_WHITE);
	output.PrintAt("                                                                                ", 0, 45);
	output.SetColor(TEXT_WHITE, BACK_BLACK);
	output.PrintAt("Arrow keys to controll the snake", 3, 47);
	output.PrintAt("Press Q to go to main Menu", 3, 48);
	output.PrintAt("Score:", 65, 47);
	output.PrintRelative("Speed:", 0, 1);
	output.PrintRelative("Walls [", -15, -1);
	output.PrintRelative("Mines [", 0, 1);
	
	/*prints On/off behind walls*/
	if (_bWalls == true)
	{
		output.SetColor(TEXT_YELLOW_BRIGHT);
		output.PrintAt("ON ", 57, 47);
		output.SetColor(TEXT_WHITE);
		output.PrintRelative("]", 2, 0);
	}
	else
	{
		output.SetColor(TEXT_RED_BRIGHT);
		output.PrintAt("OFF", 57, 47);
		output.SetColor(TEXT_WHITE);
		output.PrintRelative("]", 3, 0);
	}
	
	/*prints On/off behind Mines*/
	if(_bMines == true)
	{
		output.SetColor(TEXT_YELLOW_BRIGHT);
		output.PrintAt("ON ", 57, 48);
		output.SetColor(TEXT_WHITE);
		output.PrintRelative("]", 2, 0);
	}
	else
	{
		output.SetColor(TEXT_RED_BRIGHT);
		output.PrintAt("OFF", 57, 48);
		output.SetColor(TEXT_WHITE);
		output.PrintRelative("]", 3, 0);
	}
	
	output.SetColor(TEXT_YELLOW_BRIGHT);
	_food(); //prints first food
	
	/*adds 4 coordinates to the snake for the starter tail*/
	for(int i = 0; i < 4; i++)
	{
		_iSnakeXPos++;
		_dqSnakeX.push_back(_iSnakeXPos);
		_dqSnakeY.push_back(_iSnakeYPos);
	}
	
	/*the game loop. Will run untill game over or the player quits the game with q/Q*/
	while(_eGameStatus == PLAY)
	{
		
		/*sleep function to keep the number of loops constant*/
		timer.SleepUntilUpdate();

		/*Takes input from keyboard for the game*/
		input.GetNextKey(&_iGameInput);

		/*go to menu if player presses 'Q' or 'q'*/
		if(_iGameInput == 113 || _iGameInput == 81)
		{
			_eGameStatus = MENU;
			_gameMenu();
			break;
		}

		/*Sets the eDirection based on keyboard input*/
		if(_iGameInput == -12 && _eDirection != UP)
		{
			_eDirection = DOWN;
		}
		else if(_iGameInput == -11 && _eDirection != DOWN)
		{
			_eDirection = UP;
		}
		else if(_iGameInput == -13 && _eDirection != RIGHT)
		{
			_eDirection = LEFT;
		}
		else if (_iGameInput == -14 && _eDirection != LEFT)
		{
			_eDirection = RIGHT;
		}
		
		/*stores current head possition before changing it*/
		_iHeadX = _iSnakeXPos;
		_iHeadY = _iSnakeYPos;

		/*sets the snake to the direction determined 
		  by keyboard input above*/
		if(_eDirection == DOWN)
		{
			_iSnakeYPos++;
			//sets game over if this move will place the snake outside game area
			if(_iSnakeYPos > 44)
			{
				if(_bWalls == false)
				{
					_iSnakeYPos = 0;
				}
				else
				{
					_eGameStatus = GAMEOVER;
					_gameOver();
					break;
				}
			}
			_dqSnakeX.push_back(_iSnakeXPos);
			_dqSnakeY.push_back(_iSnakeYPos);
		}
		else if(_eDirection == UP)
		{
			_iSnakeYPos--;

			if(_iSnakeYPos < 0 )//sets game over if this move will place the snake outside game area
			{
				if(_bWalls == false)
				{
					_iSnakeYPos = 44;
				}
				else
				{
					_eGameStatus = GAMEOVER;
					_gameOver();
					break;
				}
			}
			_dqSnakeX.push_back(_iSnakeXPos);
			_dqSnakeY.push_back(_iSnakeYPos);
		}
		else if(_eDirection == LEFT)
		{
			_iSnakeXPos--;
			
			if(_iSnakeXPos < 0 )//sets game over if this move will place the snake outside game area
			{
				if(_bWalls == false)
				{
					_iSnakeXPos = 79;
				}
				else
				{
					_eGameStatus = GAMEOVER;
					_gameOver();
					break;
				}
			}

			_dqSnakeX.push_back(_iSnakeXPos);
			_dqSnakeY.push_back(_iSnakeYPos);
		}
		else if(_eDirection == RIGHT)
		{
			_iSnakeXPos++;

			if(_iSnakeXPos > 79 )//sets game over if this move will place the snake outside game area
			{
				if(_bWalls == false)
				{
					_iSnakeXPos = 0;
				}
				else
				{
					_eGameStatus = GAMEOVER;
					_gameOver();
					break;
				}
			}
			
			_dqSnakeX.push_back(_iSnakeXPos);
			_dqSnakeY.push_back(_iSnakeYPos);
		}
		
		/*sets Game Over, starts _gameOver() and breaks the gameloop if the snake 
		  head hits the snake body or a mine*/
		if(output.GetCharAt(_iSnakeXPos, _iSnakeYPos) == _cSnakeBody
			|| output.GetCharAt(_iSnakeXPos, _iSnakeYPos) == _cMine)
		{
			_eGameStatus = GAMEOVER;
			_gameOver();
			break;
		}
		
		/*Makes the snake grow if head hits a '_cFood', and adds to the score.
		  If mines are enabled, it also prints a new mine*/
		else if(output.GetCharAt(_iSnakeXPos, _iSnakeYPos) == _cFood)
		{
			_bDelayGrow = true;
			_iScore+= _iScoreIncrement * (_iGameSpeed / 2);
			_food();

			if(_bDynamicSpeed == true)
			{
				_iGameSpeed+= 1;
				timer.setGameSpeed(_iGameSpeed);
			}
			if(_bMines == true)
			{
				_mines();
			}
		}

		/*Deletes the last part of the tail as long as _bDelayGrow is false*/
		if (_bDelayGrow == false)
		{	
			//draws over the tail
			output.PrintAt(" ", _dqSnakeX.front(), _dqSnakeY.front());

			//deletes the tail coordinate drawn over from the deques
			_dqSnakeX.pop_front();
			_dqSnakeY.pop_front();
		}
		_bDelayGrow = false;

		output.PrintAt(_cSnakeBody, _iHeadX, _iHeadY);

		output.PrintAt(_cSnakeHead, _iSnakeXPos, _iSnakeYPos);
		
		/*prints the score*/
		output.PrintAt("", 71, 47);
		cout << _iScore;
		
		/*prints the game speed*/
		output.PrintAt("", 71, 48);
		cout << _iGameSpeed;
		
	
	}//end game loop
}//end gameLoop()


/*Started from the gameloop if you get gameover.
  Will print gameover screen untill player presses q/Q*/
void CGameManager::_gameOver()
{
	timer.Reset();
	//prints top and bottom borders
	output.SetColor(TEXT_WHITE, BACK_WHITE);
	output.PrintAt("                                       ", 20, 18);
	output.PrintRelative("                                       ", 0, 6);
	
	//prints black background
	output.SetColor(BACK_BLACK);
	output.PrintRelative("                                       ",0 , -1);
	output.PrintRelative("                                       ",0 , -1);
	output.PrintRelative("                                       ",0 , -1);
	output.PrintRelative("                                       ",0 , -1);
	
	//prints text
	output.SetColor(TEXT_WHITE, BACK_BLACK);
	output.PrintAt("GAME OVER!", 24, 20);
	output.PrintRelative("Press 'Q' for MAIN MENU", 5, 2);
	output.PrintRelative("Your Score :", 12, -2);
	output.SetColor(TEXT_YELLOW_BRIGHT);
	
	//prints the score you gained in the game
	cout << _iScore;

	//prints left and right border
	output.SetColor(TEXT_WHITE, BACK_WHITE);
	output.PrintAt(" ", 20, 19);
	output.PrintRelative(" ", 0, 1); 
	output.PrintRelative(" ", 0, 1);
	output.PrintRelative(" ", 0, 1);
	output.PrintRelative(" ", 0, 1);
	output.PrintAt(" ", 58, 19);
	output.PrintRelative(" ", 0, 1);
	output.PrintRelative(" ", 0, 1);
	output.PrintRelative(" ", 0, 1);
	output.PrintRelative(" ", 0, 1);

	
	//waits for player input to go to MENU
	while(_eGameStatus == GAMEOVER)
	{
		timer.SleepUntilUpdate();

		input.GetNextKey(&_iGameInput);
		if(_iGameInput == 113 || _iGameInput == 81)
		{
			_eGameStatus = MENU;
			_gameMenu();
			break;
		}
	}//end gameover loop
}//End _gameOver



/*the game menu. Will run on game start, and wait for input from player
  to change to the game loop itself, or to quit the game.*/
void CGameManager::_gameMenu()
{
	timer.Reset();
	output.SetColor(TEXT_WHITE, BACK_BLACK);
	output.ClearScreen();
	output.SetColor(TEXT_MAGENTA_BRIGHT);
	output.PrintAt("Snake\n", 36, 10);
	output.SetColor(TEXT_YELLOW);
	output.PrintRelative("[P]Play", -1, 2);
	output.PrintRelative("[S]Settings", 0, 1);
	output.PrintRelative("[Q]Quit", 0, 1);
	output.SetColor(TEXT_YELLOW_BRIGHT);
	output.PrintAt("ooo@", 36, 22);
	output.SetColor(TEXT_WHITE);
	
	_eGameStatus = MENU;

	while(_eGameStatus == MENU)
	{
		timer.SleepUntilUpdate();
		input.GetNextKey(&_iGameInput);

		//If input is P/p, the game is started.
		if(_iGameInput == 112 || _iGameInput == 80)
		{
			_eGameStatus = PLAY;
			_gameLoop();
			break;
		}
		//If input is Q/q, game exits
		else if(_iGameInput == 113 || _iGameInput == 81)
		{
			_eGameStatus = QUIT;
			break;
		}
		//if input is S/s, the settings menu is shown
		else if (_iGameInput == 115 ||_iGameInput == 83)
		{
			_eGameStatus = SETTINGS;
			_gameSettings();
			break;
		}		
	}//end menu loop
}//End _gameMenu()



/*Settings screen where ingame settings can be changed*/
void CGameManager::_gameSettings()
{
	/*Draws static info to Game Setting screen*/
	output.ClearScreen();
	output.SetColor(TEXT_YELLOW_BRIGHT);
	output.PrintAt("-----GAME SETTINGS-----", 27, 8);
	output.SetColor(TEXT_YELLOW);
	output.PrintAt("Game Speed", 20, 10);
	output.PrintAt("Extra features", 20, 24);
	output.SetColor(TEXT_WHITE);
	output.PrintAt("[D] Default all settings", 20, 34);
	output.PrintRelative("[Q] Back to Main Menu", 0, 2);

	/*prints different speed indication when entering the settings menu
	  based on what _eGameSpeed is at when entering*/
	switch(_eGameSpeed)
	{
	case SLOW:
		output.PrintAt("[1] Low speed [ ]", 20, 12);
		output.PrintRelative("[2] Medium speed [-]", 0, 1);
		output.PrintRelative("[3] High speed [-]", 0, 1);
		output.PrintRelative("[4] Custom speed(1-100):", 0, 2);
		output.SetColor(TEXT_YELLOW_BRIGHT);
		output.PrintAt("X", 35, 12);
		output.SetColor(TEXT_WHITE);
		break;
	case MEDIUM:
		output.PrintAt("[1] Low speed [-]", 20, 12);
		output.PrintRelative("[2] Medium speed [ ]", 0, 1);
		output.PrintRelative("[3] High speed [-]", 0, 1);
		output.PrintRelative("[4] Custom speed(1-100):", 0, 2);
		output.SetColor(TEXT_YELLOW_BRIGHT);
		output.PrintAt("X", 38, 13);
		output.SetColor(TEXT_WHITE);
		break;
	case HIGH:
		output.PrintAt("[1] Low speed [-]", 20, 12);
		output.PrintRelative("[2] Medium speed [-]", 0, 1);
		output.PrintRelative("[3] High speed [ ]", 0, 1);
		output.PrintRelative("[4] Custom speed(1-100):", 0, 2);
		output.SetColor(TEXT_YELLOW_BRIGHT);
		output.PrintAt("X", 36, 14);
		output.SetColor(TEXT_WHITE);
		break;
	case CUSTOM:
		output.PrintAt("[1] Low speed [-]", 20, 12);
		output.PrintRelative("[2] Medium speed [-]", 0, 1);
		output.PrintRelative("[3] High speed [-]", 0, 1);
		output.PrintRelative("[4] Custom speed (1-100): ", 0, 2);
		output.SetColor(TEXT_YELLOW_BRIGHT);
		output.PrintAt("", 45, 16);
		cout << setfill('0') << setw(3) <<_iGameSpeed;
		output.SetColor(TEXT_WHITE);
		break;
	}
	
	/*prints if dynamic speed is on or off when going to settings menu*/
	if(_bDynamicSpeed == false)
	{
		output.PrintAt("[5]Toggle Dynamically increasing speed [-]", 20, 18);
	}
	else
	{
		output.PrintAt("[5]Toggle Dynamically increasing speed [ ]", 20, 18);
		output.SetColor(TEXT_YELLOW_BRIGHT);
		output.PrintAt("X", 60, 18);
		output.SetColor(TEXT_WHITE);
	}

	/*prints if walls are on or off when going to settings menu*/
	if(_bWalls == false)
	{
		output.PrintAt("[6] Walls [        ]", 20, 26);
		output.SetColor(TEXT_RED_BRIGHT);
		output.PrintAt("Disabled", 31, 26);
		output.SetColor(TEXT_WHITE);
	}
	else
	{
		output.PrintAt("[6] Walls [       ]", 20, 26);
		output.SetColor(TEXT_GREEN_BRIGHT);
		output.PrintAt("Enabled", 31, 26);
		output.SetColor(TEXT_WHITE);
	}

	/*prints if Mines are on or off when going to settings menu*/
	if(_bMines == false)
	{
		output.PrintAt("[7] Mines [        ]", 20, 28);
		output.SetColor(TEXT_RED_BRIGHT);
		output.PrintAt("Disabled", 31, 28);
		output.SetColor(TEXT_WHITE);
	}
	else
	{
		output.PrintAt("[7] Mines [       ]", 20, 28);
		output.SetColor(TEXT_GREEN_BRIGHT);
		output.PrintAt("Enabled", 31, 28);
		output.SetColor(TEXT_WHITE);
	}

	//loop for taking input and visually changing
	//what's toggeled on/off etc
	while(_eGameStatus == SETTINGS)
	{
		timer.SleepUntilUpdate();
		input.GetNextKey(&_iGameInput);

		/*switch taking keys 1-7 and changing a setting for each key*/
		switch(_iGameInput)
		{
		case 49://1
			_iGameSpeed = 8;
			if(_eGameSpeed == CUSTOM)
			{
				output.PrintAt("   ", 45, 16);
			}
			_eGameSpeed = SLOW;
			output.SetColor(TEXT_YELLOW_BRIGHT);
			output.PrintAt("X", 35, 12);
			output.SetColor(TEXT_WHITE);
			output.PrintAt("-", 38, 13);
			output.PrintAt("-", 36, 14);
			break;

		case 50://2
			_iGameSpeed = 15;
			if(_eGameSpeed == CUSTOM)
			{
				output.PrintAt("   ", 45, 16);
			}
			_eGameSpeed = MEDIUM;
			output.PrintAt("-", 35, 12);
			output.SetColor(TEXT_YELLOW_BRIGHT);
			output.PrintAt("X", 38, 13);
			output.SetColor(TEXT_WHITE);
			output.PrintAt("-", 36, 14);
			break;

		case 51://3
			_iGameSpeed = 30;
			if(_eGameSpeed == CUSTOM)
			{
				output.PrintAt("   ", 45, 16);
			}
			_eGameSpeed = HIGH;
			output.PrintAt("-", 35, 12);
			output.PrintAt("-", 38, 13);
			output.SetColor(TEXT_YELLOW_BRIGHT);
			output.PrintAt("X", 36, 14);
			output.SetColor(TEXT_WHITE);
			break;
		
		case 52://4, sets gamespeed to custom and lets you change it with arrow keys
			_eGameSpeed = CUSTOM;
			_bChangingCustomSpeed = true;
			output.PrintAt("-", 35, 12);
			output.PrintAt("-", 38, 13);
			output.PrintAt("-", 36, 14);
			output.PrintAt("ENTER to confirm", 50, 16);
			output.PrintRelative("Up/Down keys to change value", 0, -1);
			output.SetColor(TEXT_YELLOW_BRIGHT);
			/*lets you change the gamespeed while ChangingCustomSpeed is true*/
			while(_bChangingCustomSpeed == true)
			{
				timer.SleepUntilUpdate();
				input.GetNextKey(&_iGameInput);
				if(_iGameInput == -12)//down
				{
					_iGameSpeed--;
				}
				else if(_iGameInput == -11)//up
				{
					_iGameSpeed++;
				}
				else if(_iGameInput == 13)//enter
				{
					output.PrintAt("                ", 50, 16);
					output.PrintRelative("                            ", 0, -1);
					_bChangingCustomSpeed = false;
				}
				
				//makes sure game speed cannot be less then 1 or more then 100
				if (_iGameSpeed < 1)
				{
					_iGameSpeed = 1;
				}
				else if(_iGameSpeed > 100)
				{
					_iGameSpeed = 100;
				}
				
				//prints the gamespeed
				output.PrintAt("", 45, 16);
				cout << setfill('0') << setw(3) <<_iGameSpeed;
			}
			break;
		
		case 53://5, toggles dynamic speed on/off
			if(_bDynamicSpeed == false)
			{
				_bDynamicSpeed = true;
				output.SetColor(TEXT_YELLOW_BRIGHT);
				output.PrintAt("X", 60, 18);
				output.SetColor(TEXT_WHITE);
				break;
			}
			else
			{
				_bDynamicSpeed = false;
				output.PrintAt("-", 60, 18);
				break;
			}
		
		case 54://6, toggles walls on/off
			if(_bWalls == false)
			{
				output.SetColor(TEXT_YELLOW_BRIGHT);
				output.PrintAt("Enabled", 31, 26);
				output.SetColor(TEXT_WHITE);
				cout << "] ";
				_bWalls = true;
			}
			else
			{
				output.SetColor(TEXT_RED_BRIGHT);
				output.PrintAt("Disabled", 31, 26);
				output.SetColor(TEXT_WHITE);
				cout << "]";
				_bWalls = false;
			}
			break;
		
		case 55://7, toggles Mines on/off
			if(_bMines == false)
			{
				output.SetColor(TEXT_YELLOW_BRIGHT);
				output.PrintAt("Enabled", 31, 28);
				output.SetColor(TEXT_WHITE);
				cout << "] ";
				_bMines = true;
			}
			else
			{
				output.SetColor(TEXT_RED_BRIGHT);
				output.PrintAt("Disabled", 31, 28);
				output.SetColor(TEXT_WHITE);
				cout << "]";
				_bMines = false;
			}
			break;
		}
		
		/*If D/d is pressed, all settings resets to default*/
		if(_iGameInput == 100 || _iGameInput == 68)
		{
			_defaultSettings();
			break;
		}
		
		/*Goes to Main Menu if Q/q is pressed*/
		else if(_iGameInput == 113 || _iGameInput == 81)
		{
			_eGameStatus = MENU;
			_gameMenu();
			break;
		}	
	}//end settings loop
}//end _gameSettings()


/*function that prints a mine at a random location
  if the mine would have appeared where the snake or a food currently is,
  it will find a new location*/
void CGameManager::_mines()
{
	_iMineX = (rand() % 80);
	_iMineY = (rand() % 45);

	if(output.GetCharAt(_iMineX, _iMineY) == _cSnakeBody 
	  || output.GetCharAt(_iMineX, _iMineY) == _cSnakeHead
	  || output.GetCharAt(_iMineX, _iMineY) == _cFood
	  || output.GetCharAt(_iMineX, _iMineY) == _cMine)
	{
		_mines();	
	}
	else 
	{
		output.SetColor(TEXT_GREEN);
		output.PrintAt(_cMine, _iMineX, _iMineY);
		output.SetColor(TEXT_YELLOW_BRIGHT);
	}
}//End _mines()


/*Prints a new food on a random location. 
  if the food would have appeared where the snake allready is, it creates a new location.*/
void CGameManager::_food()
{
	_iFoodX = (rand() % 80);
	_iFoodY = (rand() % 45);

	if(output.GetCharAt(_iFoodX, _iFoodY) == _cSnakeBody 
		|| output.GetCharAt(_iFoodX, _iFoodY) == _cSnakeHead
		|| output.GetCharAt(_iFoodX, _iFoodY) == _cMine)
	{
		_food();	
	}
	else 
	{
		output.SetColor(TEXT_GREEN_BRIGHT);
		output.PrintAt(_cFood, _iFoodX, _iFoodY);
		output.SetColor(TEXT_YELLOW_BRIGHT);
	}
}//End _food()


/*called to reset all settings to default*/
void CGameManager::_defaultSettings()
{
	_iScoreIncrement = 5; //the amount of score you gain
	_iGameSpeed = 15; //variable used for dynamically changing gamespeed
	
	//start coordinates for the snake
	_iDefaultSnakeXPos = 35; //x starting coordinate for snake 
	_iDefaultSnakeYPos = 22; //y starting coordinate for snake 

	_cSnakeHead = '@'; //the default snake head
	_cSnakeBody = 'o'; //the default snake body
	_cFood = '$';
	_cMine = '*';

	_bDynamicSpeed = false; //when true, gamespeed increases dynamically
	_bWalls = true; //decides if walls are on or off
	_bMines = false; //used to decide if mines are enabled or not
	_bChangingCustomSpeed = false; //used for a loop that changes custom speed

	_eDirection = RIGHT; //the default starting direction of the snake
	_eGameSpeed = MEDIUM; //the speed of the game, medium is default
	
	//Runs the the settings menu again if the _defaultSettings() 
	//was called from the settings menu
	if(_eGameStatus == SETTINGS)
	{
		_gameSettings();
	}
}//end _defaultSettings()
