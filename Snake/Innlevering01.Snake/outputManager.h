#ifndef OUTPUT_MANAGER_H  // Inclusion guard.
#define OUTPUT_MANAGER_H

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File: outputManager.h
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

#include <windows.h>  // Windows defines.
#include <iostream>  // std::cout, ...
#include <string>  // string functionality.
using std::cout;
using std::endl;
using std::string;

namespace Santom
{

	// D E F I N E S   /   C O N S T A N T S   /   . . .
	// =================================================

	// NOTE: What we do here is just to make shorter and more easily understood names for the 
	//       different color combinations, by combining the existing color flags in new defines.

	// Text/character/symbol colors:
	#define		TEXT_WHITE				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	#define		TEXT_WHITE_BRIGHT		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
	#define		TEXT_RED				FOREGROUND_RED
	#define		TEXT_RED_BRIGHT			FOREGROUND_RED | FOREGROUND_INTENSITY
	#define		TEXT_GREEN				FOREGROUND_GREEN
	#define		TEXT_GREEN_BRIGHT		FOREGROUND_GREEN | FOREGROUND_INTENSITY
	#define		TEXT_BLUE				FOREGROUND_BLUE
	#define		TEXT_BLUE_BRIGHT		FOREGROUND_BLUE | FOREGROUND_INTENSITY
	#define		TEXT_YELLOW				FOREGROUND_RED | FOREGROUND_GREEN
	#define		TEXT_YELLOW_BRIGHT		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
	#define		TEXT_CYAN				FOREGROUND_GREEN | FOREGROUND_BLUE
	#define		TEXT_CYAN_BRIGHT		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
	#define		TEXT_MAGENTA			FOREGROUND_BLUE | FOREGROUND_RED 
	#define		TEXT_MAGENTA_BRIGHT		FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY 
	#define		TEXT_BLACK				0

	// Background colors:
	#define		BACK_WHITE				BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
	#define		BACK_WHITE_BRIGHT		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
	#define		BACK_RED				BACKGROUND_RED
	#define		BACK_RED_BRIGHT			BACKGROUND_RED | BACKGROUND_INTENSITY
	#define		BACK_GREEN				BACKGROUND_GREEN
	#define		BACK_GREEN_BRIGHT		BACKGROUND_GREEN | BACKGROUND_INTENSITY
	#define		BACK_BLUE				BACKGROUND_BLUE
	#define		BACK_BLUE_BRIGHT		BACKGROUND_BLUE | BACKGROUND_INTENSITY
	#define		BACK_YELLOW				BACKGROUND_RED | BACKGROUND_GREEN
	#define		BACK_YELLOW_BRIGHT		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY
	#define		BACK_CYAN				BACKGROUND_GREEN | BACKGROUND_BLUE
	#define		BACK_CYAN_BRIGHT		BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
	#define		BACK_MAGENTA			BACKGROUND_BLUE | BACKGROUND_RED 
	#define		BACK_MAGENTA_BRIGHT		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY 
	#define		BACK_BLACK				0

	
	// C L A S S   D E C L A R A T I O N
	// =================================

	class COutputManager
	{
	public:
		COutputManager();
		~COutputManager();

		// Initializes the console window with its title, size, and default text and background 
		// colors. Returns true as long as function don't fail.
		bool Initialize(string strWindowTitle = "", short sWidth = 500, short sHeight = 300, unsigned short usTextColor = TEXT_BLUE, unsigned short	usBackgroundColor = BACK_BLACK);
		
		// Blanks the screen.
		void ClearScreen();

		// Sets the colors for our console. (NOTE: Only works for NEW output - does not affect 
		// already written output.) Returns true as long as function don't fail.
		bool SetColor(unsigned short usTextColor, unsigned short usBackgroundColor = BACK_BLACK);

		// Lets us retrieve (returns) the output character at the specified console position. 
		// No printed character is the same as a space (' ').
		char GetCharAt(short sPosX, short sPosY);

		// Outputs a string, starting at the specified console position. 
		// Returns true as long as function don't fail.
		bool PrintAt(string strOutput, short sPosX, short sPosY);

		// As PrintAt above, but outputs a single char.
		bool PrintAt(char cOutput, short sPosX, short sPosY);

		// As PrintAt above, but outputs an unsigned long.
		bool PrintAt(unsigned long ulOutput, short sPosX, short sPosY);

		// Outputs a string, starting relative to the last output, offset by the supplied values.
		// Example: "PrintRelative("World", 0, 1);" would print "World" just below what we output 
		//          through our COutputManager last.
		// Returns true as long as function don't fail.
		bool PrintRelative(string strOutput, short sOffsetX, short sOffsetY);

		// As PrintRelative above, but outputs a single char.
		bool PrintRelative(char cOutput, short sOffsetX, short sOffsetY);

		// As PrintRelative above, but outputs an unsigned long.
		bool PrintRelative(unsigned long ulOutput, short sOffsetX, short sOffsetY);

	private:
		// Helper function, used by our other class functions, to move the cursor to our specified 
		// COORD position. Returns true as long as function don't fail.
		bool _SetPosition(COORD oNewPosition);	// Moves cursor to position [x, y].

		HANDLE	m_hConsole;			// Console handle.
		COORD	m_oLastPrintCoord;	// Position where last screen print started.
	};

}

#endif  // OUTPUT_MANAGER_H

