///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File: inputManager.cpp
//
//	Original author: Tomas Sandnes / NITH / 2007
//	Changed by:	     Tomas Sandnes / NITH / 2011
//
//	Descr.: A class for handling keyboard input. Normal input is returned
//			as an INT with the ASCII/ANSI value of the key.	Arrow-keys and
//			function-keys are given a NEGATIVE int value (see the PUBLIC
//			static const values in class CInputManager (inputManager.h) as
//			they aren't represented in the normal, positive ASCII/ANSI
//			range.
//
//	Special notes: 1. All code placed in namespace Santom.
//				   2. Contains MS Windows specific code - NOT OS independent!
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>  // For fflush and stdin.
#include <conio.h>   // Stuff for rearding keyboard input. (Standard C++'s cin can't read single 
					 // keypresses, so not suited for games. However, the conio.h stuff can. :-)
#include "inputManager.h"
using Santom::CInputManager;


// P U B L I C   F U N C T I O N S
// ===============================

CInputManager::CInputManager()
{
}  // END CInputManager


CInputManager::~CInputManager()
{
}  // END ~CInputManager


// Returns true if there are any cached keypresses not acted upon yet.
bool CInputManager::AnyKeyPressed()
{
	if (0 != _kbhit())
	{
		return true;
	}
	return false;

}  // END AnyKeyPressed


// Returns 'false' if no key has been pressed. Else 'true', and the parameter keeps the next 
// buffered keypress (first one that hasn't been extracted or cleared in any way).
bool CInputManager::GetNextKey(int* r_piKeyPressed)  // Return value for key pressed, if any. 
{
	return _GetTheKey(r_piKeyPressed, false, false);

}  // END GetNextKey


// As GetNextKey, above, but always return uppercase version of the key.
bool CInputManager::GetNextKeyUpper(int* r_piKeyPressed)
{
	return _GetTheKey(r_piKeyPressed, true, false);

}  // END GetNextKeyUpper


// Waits for input if no key has been pressed yet. Parameter keeps the next buffered keypress 
// (first one that hasn't been extracted or cleared in any way). 
void CInputManager::GetNextKeyWait(int* r_piKeyPressed)
{
	_GetTheKey(r_piKeyPressed, false, true);

}  // END GetNextKeyWait


// As GetNextKeyWait, above, but always return uppercase version of the key.
void CInputManager::GetNextKeyUpperWait(int* r_piKeyPressed)
{
	_GetTheKey(r_piKeyPressed, true, true);

}  // END GetNextKeyUpperWait


// P R I V A T E   F U N C T I O N S
// =================================

// Internal function doing the nitty gritty keypress stuff.
bool CInputManager::_GetTheKey(int* r_piKeyPressed,  // Return value for actual keypress.
							   bool bToUpper,        // If true, always convert param above to uppercase.
							   bool bWaitIfNoneYet)  // If true, dont return - wait for first coming keypress.
{
	bool r_bAnyKeyPressed = false;
	int iInput = 0;
	*r_piKeyPressed = iKEY_NONE;

	// Get the next keypress. 
	// NOTE: A while-statement would get the last keypress not acted upon yet, skiping any in-between. 
	//       As we want the first keypress not acted upon, we do an if-statement instead.
	if ((0 != _kbhit()) || bWaitIfNoneYet)
	{
		iInput = _getch();  // If bWaitIfNoneYet is true and no key has been pressed, execution will halt here until we get a keypress.
		r_bAnyKeyPressed = true;

		if (m_iARROWKEY_PREFIX == iInput) 
		{
			// NOTE: Special keys (arrow-keys and function-keys) are coded as TWO keypresses in conio.h, as they don't fit in the 
			//       normal ASCII table. Thus, if the first keypress we read indicates a special key, we have to combine it with 
			//       the next keypress immediately (which in reality is the 2nd part of the arrow-/function-key anyway). We then
			//       translate this double-press and return our own const representing that special key to the caller.
			iInput = _getch();
			switch (iInput)
			{
				case m_iARROW_UP:
				{
					*r_piKeyPressed = iKEY_ARROWUP;
					break;
				}
				case m_iARROW_DOWN:
				{
					*r_piKeyPressed = iKEY_ARROWDOWN;
					break;
				}
				case m_iARROW_LEFT:
				{
					*r_piKeyPressed = iKEY_ARROWLEFT;
					break;
				}
				case m_iARROW_RIGHT:
				{
					*r_piKeyPressed = iKEY_ARROWRIGHT;
					break;
				}

			}
		}
		else if (m_iFUNCTIONKEY_PREFIX == iInput)
		{
			// OPTIONAL TODO: Implement function keys - same system as for arrow keys.
			_getch();  // (Just using a _getch() to "flush" the function key input for now, until someone implements support for function-keys.)
			*r_piKeyPressed = iKEY_NONE;
		}
		else
		{
			if (bToUpper)
			{
				*r_piKeyPressed = toupper(iInput);
			}
			else
			{
				*r_piKeyPressed = iInput;
			}
		}
	}

	return r_bAnyKeyPressed;

}  // END _GetTheKey


