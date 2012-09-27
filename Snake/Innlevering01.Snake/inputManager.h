#ifndef INPUT_MANAGER_H  // Inclusion guard.
#define INPUT_MANAGER_H

///////////////////////////////////////////////////////////////////////////////////////////////////
//																			  
//	File: inputManager.h													  
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

namespace Santom
{

	// C L A S S   D E C L A R A T I O N
	// =================================

	class CInputManager
	{
	public:
		static const int iKEY_NONE =		-1;		// Return code, meaning: "No key specified/unable to identify key."
		static const int iKEY_ARROWUP =		-11;	// Return code for [ARROW UP] key.
		static const int iKEY_ARROWDOWN =	-12;	// Return code for [ARROW DOWN] key.
		static const int iKEY_ARROWLEFT =	-13;	// Return code for [ARROW LEFT] key.
		static const int iKEY_ARROWRIGHT =	-14;	// Return code for [ARROW RIGHT] key.

		/* OPTIONAL TODO: Function keys not implemented - feel free to do so yourself if you want them.
		static const int iKEY_F1 =			-21;	// Return code for [F1] key.
		static const int iKEY_F2 =			-22;	// Return code for [F2] key.
		static const int iKEY_F3 =			-23;	// Return code for [F3] key.
		static const int iKEY_F4 =			-24;	// Return code for [F4] key.
		static const int iKEY_F5 =			-25;	// Return code for [F5] key.
		static const int iKEY_F6 =			-26;	// Return code for [F6] key.
		static const int iKEY_F7 =			-27;	// Return code for [F7] key.
		static const int iKEY_F8 =			-28;	// Return code for [F8] key.
		static const int iKEY_F9 =			-29;	// Return code for [F9] key.
		static const int iKEY_F10 =			-30;	// Return code for [F10] key.
		static const int iKEY_F11 =			-31;	// Return code for [F11] key.
		static const int iKEY_F12 =			-32;	// Return code for [F12] key.
		*/

		CInputManager();	
		~CInputManager();	

		// Returns true if there are any cached keypresses not acted upon yet.
		bool AnyKeyPressed();  

		// Returns 'false' if no key has been pressed. Else 'true', and the parameter keeps the next 
		// buffered keypress (first one that hasn't been extracted or cleared in any way).
		bool GetNextKey(int* r_piKeyPressed);  

		// As GetNextKey, above, but always return uppercase version of the key.
		bool GetNextKeyUpper(int* r_piKeyPressed);  

		// Waits for input if no key has been pressed yet. Parameter keeps the next buffered keypress 
		// (first one that hasn't been extracted or cleared in any way). 
		void GetNextKeyWait(int* r_piKeyPressed);  

		// As GetNextKeyWait, above, but always return uppercase version of the key.
		void GetNextKeyUpperWait (int* r_piKeyPressed);  

	private:
		static const int m_iFUNCTIONKEY_PREFIX =  0;	// _getch prefix code for any function key: 0.
		static const int m_iARROWKEY_PREFIX =	224;	// _getch prefix code for any arrow key (decimal 224 = hexadecimal 0xE0).
		static const int m_iARROW_UP =			 72;	// _getch code for [ARROW UP] key.
		static const int m_iARROW_DOWN =		 80;	// _getch code for [ARROW DOWN] key.
		static const int m_iARROW_LEFT =		 75;	// _getch code for [ARROW LEFT] key.
		static const int m_iARROW_RIGHT =		 77;	// _getch code for [ARROW RIGHT] key.

		// Internal function doing the nitty gritty stuff.
		bool _GetTheKey(int* r_piKeyPressed, bool bToUpper, bool bWaitIfNoneYet);  
	};

}  // END namespace

#endif  // END inlusion guard
