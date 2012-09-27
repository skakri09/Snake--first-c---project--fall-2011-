///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File: loopTimer.cpp
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

#include <windows.h>  // For Sleep()
#include "loopTimer.h"
using Santom::CLoopTimer;


// P U B L I C   F U N C T I O N S
// ===============================

CLoopTimer::CLoopTimer(unsigned short usWantedUpdatesPerSec)  // Defaults to 15.
{
	m_usWantedUPS = usWantedUpdatesPerSec;
	m_usUPSLastSec = 0;
	m_usUpdatesThisSec = 0;
	m_lCurrentSecStartClock = clock();
	m_lNextSecStartClock = m_lCurrentSecStartClock + CLOCKS_PER_SEC;
	m_lNextUpdateClock = m_lCurrentSecStartClock + ((m_usUpdatesThisSec + 1) * CLOCKS_PER_SEC / m_usWantedUPS);

}  // END CLoopTimer


CLoopTimer::~CLoopTimer()
{
}  // END ~CLoopTimer


// This function resets all clock values to current system values. 
// Should be used just before the gameloop starts.
void CLoopTimer::Reset()
{
	m_usUPSLastSec = 0;
	m_usUpdatesThisSec = 0;
	m_lCurrentSecStartClock = clock();
	m_lNextSecStartClock = m_lCurrentSecStartClock + CLOCKS_PER_SEC;
	m_lNextUpdateClock = m_lCurrentSecStartClock + ((m_usUpdatesThisSec + 1) * CLOCKS_PER_SEC / m_usWantedUPS);

}  // END Reset


// This function should be called at the start of any game loop. It will sleep (pause 
// without taking system resources) for the needed time to keep a constant number of loops 
// per second equaling the class member variable m_usWantedUPS.
void CLoopTimer::SleepUntilUpdate()
{
	clock_t lClocksRemaining = m_lNextUpdateClock - clock();
	if (0 < lClocksRemaining)
	{
		Sleep((lClocksRemaining * 1000) / CLOCKS_PER_SEC);
	}

	++m_usUpdatesThisSec;
	m_lNextUpdateClock = m_lCurrentSecStartClock + (((m_usUpdatesThisSec + 1) * CLOCKS_PER_SEC) / m_usWantedUPS);
	while (m_lNextUpdateClock > m_lNextSecStartClock)
	{
		m_usUPSLastSec = m_usUpdatesThisSec;
		m_lCurrentSecStartClock = m_lNextSecStartClock;
		m_lNextSecStartClock += CLOCKS_PER_SEC;
		m_usUpdatesThisSec = 0;
	}

}  // END SleepUntilUpdate


void CLoopTimer::setGameSpeed(int iNewGameSpeed)
{
	m_usWantedUPS = iNewGameSpeed;
}
