#ifndef LOOP_TIMER_H  // Inclusion guard.
#define LOOP_TIMER_H

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File: loopTimer.h
//
//	Original author: Tomas Sandnes / NITH / 2007
//	Changed by:	     Tomas Sandnes / NITH / 2011
//					 Kristian Skarseth / NITH / 2011
//
//	Description: A helper class for gameLoop timing. This is a very basic
//				 loopTimer - it can NOT change the number of loops per
//				 second after its made, for example.
//
//	Special notes: 1. All code placed in namespace Santom.
//				   2. Contains MS Windows specific code - NOT OS independent!
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <ctime>  // clock(), clock_t.

namespace Santom
{

	// C L A S S   D E C L A R A T I O N
	// =================================

	class CLoopTimer
	{
	public:
		CLoopTimer(unsigned short usWantedUpdatesPerSec = 15);
		~CLoopTimer();

		// This function resets all clock values to current system values. Should be used just 
		// before the gameloop starts.
		void Reset();  
		void setGameSpeed(int);

		// This function should be called at the start of any game loop. It will sleep (pause 
		// without taking system resources) for the needed time to keep a constant number of loops 
		// per second equaling the class member variable m_usWantedUPS.
		void SleepUntilUpdate();  

	private:
		unsigned short	m_usWantedUPS;				// Number of updates we're striving to get per sec.
		unsigned short	m_usUPSLastSec;				// Number of updates last sec total.
		unsigned short	m_usUpdatesThisSec;			// Number of updates this sec so far.
		clock_t			m_lCurrentSecStartClock;	// When current sec started.
		clock_t			m_lNextSecStartClock;		// When next sec starts.
		clock_t			m_lNextUpdateClock;			// Ideal time for next update.
	};

}  // END namespace

#endif  // END inlusion guard
