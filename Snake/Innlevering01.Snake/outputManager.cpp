///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File: outputManager.cpp
//
//	Original author: Tomas Sandnes / NITH / 2007
//	Changed by:	     Tomas Sandnes / NITH / 2011
//
//	Description: A class for handling console output.
//
//	Special notes: 1. All code placed in namespace Santom.
//				   2. Contains MS Windows specific code - NOT OS independent!
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "outputManager.h"
using Santom::COutputManager;


// P U B L I C   F U N C T I O N S
// ===============================

COutputManager::COutputManager()
{
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Get console handle.
	m_oLastPrintCoord.X = 0;
	m_oLastPrintCoord.Y = 0;

}  // END COutputManager


COutputManager::~COutputManager()
{
}  // END ~COutputManager


// Initializes the console window with its title, size, and default text and background 
// colors. Returns true as long as function don't fail.
bool COutputManager::Initialize(string		   strWindowTitle,	   // Defaults to empty string.
								short		   sWidth,			   // Defaults to 80.
								short		   sHeight,			   // Defaults to 50.
								unsigned short usTextColor,		   // Defaults to TEXT_WHITE (Std grey).
								unsigned short usBackgroundColor)  // Defaults to BACK_BLACK (Std black).
{
	bool r_bInitOk = false;

	if (INVALID_HANDLE_VALUE != m_hConsole)
	{
		// Set primary window data: title, buffer (drawing area) size, actual window size.
		SetConsoleTitleA(strWindowTitle.c_str());  
		COORD oSizeCoord = {sWidth, sHeight};
		SetConsoleScreenBufferSize(m_hConsole, oSizeCoord); 
		SMALL_RECT oSizeRect = {0, 0, sWidth - 1, sHeight - 1};
		SetConsoleWindowInfo(m_hConsole, TRUE, &oSizeRect);

		// Remove blinking cursor.
		CONSOLE_CURSOR_INFO oConsoleCursorInfo = {1, FALSE};
		SetConsoleCursorInfo(m_hConsole, &oConsoleCursorInfo);

		// Set output color.
		SetConsoleTextAttribute(m_hConsole, usTextColor | usBackgroundColor);
		ClearScreen();  // Clear screen to get any color effect done at once.

		r_bInitOk = true;
	}

	return r_bInitOk;

}  // END Initialize


// Blanks the screen.
void COutputManager::ClearScreen()
{
	system("cls");

}  // END ClearScreen


// Sets the colors for our console. (NOTE: Only works for NEW output - does not affect 
// already written output.) Returns true as long as function don't fail.
bool COutputManager::SetColor(unsigned short usTextColor,
							  unsigned short usBackgroundColor)  // Defaults to BACK_BLACK.
{
	return (TRUE == SetConsoleTextAttribute(m_hConsole, usTextColor | usBackgroundColor));

}  // END SetColor


// Lets us retrieve (returns) the output character at the specified console position. 
// No printed character is the same as a space (' ').
char COutputManager::GetCharAt(short sPosX, 
							   short sPosY)
{
	char r_cCharRead = ' ';
	unsigned long ulCharsRead = 0;
	COORD oScreenCoord = {sPosX, sPosY};
	ReadConsoleOutputCharacterA(m_hConsole, &r_cCharRead, 1, oScreenCoord, &ulCharsRead);

	return r_cCharRead;
}


// Outputs a string, starting at the specified console position. 
// Returns true as long as function don't fail.
bool COutputManager::PrintAt(string strOutput,
							 short  sPosX, 
							 short  sPosY)
{
	m_oLastPrintCoord.X = sPosX;
	m_oLastPrintCoord.Y = sPosY;

	bool r_bRetOk = _SetPosition(m_oLastPrintCoord);

	cout << strOutput;

	return r_bRetOk;

}  // END PrintAt


// As PrintAt above, but outputs a single char.
bool COutputManager::PrintAt(char  cOutput,
							 short sPosX, 
							 short sPosY)
{
	m_oLastPrintCoord.X = sPosX;
	m_oLastPrintCoord.Y = sPosY;

	bool r_bRetOk = _SetPosition(m_oLastPrintCoord);

	cout << cOutput;

	return r_bRetOk;

}  // END PrintAt


// As PrintAt above, but outputs an unsigned long.
bool COutputManager::PrintAt(unsigned long ulOutput,
							 short		   sPosX, 
							 short		   sPosY)
{
	m_oLastPrintCoord.X = sPosX;
	m_oLastPrintCoord.Y = sPosY;

	bool r_bRetOk = _SetPosition(m_oLastPrintCoord);

	cout << ulOutput;

	return r_bRetOk;

}  // END PrintAt


// Outputs a string, starting relative to the last output, offset by the supplied values.
// Example: "PrintRelative("World", 0, 1);" would print "World" just below what we output 
//          through our COutputManager last.
// Returns true as long as function don't fail.
bool COutputManager::PrintRelative(string strOutput,
								   short  sOffsetX, 
								   short  sOffsetY)
{
	m_oLastPrintCoord.X += sOffsetX;
	m_oLastPrintCoord.Y += sOffsetY;

	bool r_bRetOk = _SetPosition(m_oLastPrintCoord);

	cout << strOutput;

	return r_bRetOk;

}  // END PrintRelative


// As PrintRelative above, but outputs a single char.
bool COutputManager::PrintRelative(char  cOutput,
								   short sOffsetX, 
								   short sOffsetY)
{
	m_oLastPrintCoord.X += sOffsetX;
	m_oLastPrintCoord.Y += sOffsetY;

	bool r_bRetOk = _SetPosition(m_oLastPrintCoord);

	cout << cOutput;

	return r_bRetOk;

}  // END PrintRelative


// As PrintRelative above, but outputs an unsigned long.
bool COutputManager::PrintRelative(unsigned long ulOutput,
								   short		 sOffsetX, 
								   short		 sOffsetY)
{
	m_oLastPrintCoord.X += sOffsetX;
	m_oLastPrintCoord.Y += sOffsetY;

	bool r_bRetOk = _SetPosition(m_oLastPrintCoord);

	cout << ulOutput;

	return r_bRetOk;

}  // END PrintRelative


// P R I V A T E   F U N C T I O N S
// =================================

// Helper function, used by our other class functions, to move the cursor to our specified 
// COORD position. Returns true as long as function don't fail.
bool COutputManager::_SetPosition(COORD oNewPosition)
{
	return (TRUE == SetConsoleCursorPosition(m_hConsole, oNewPosition));

}  // END _SetPosition




