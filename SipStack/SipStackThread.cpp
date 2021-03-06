/* 
 * Copyright (C) 2012 Yee Young Han <websearch@naver.com> (http://blog.naver.com/websearch)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#include "SipStackThread.h"
#include "SipDeleteQueue.h"
#include "TimeUtility.h"
#include "ServerUtility.h"
#include "MemoryDebug.h"

time_t giTime = 0;

/**
 * @ingroup SipStack
 * @brief 주기적으로 SIP stack 을 실행하는 쓰레드
 * @param lpParameter SIP stack 객체
 * @returns 0 을 리턴한다.
 */
THREAD_API SipStackThread( LPVOID lpParameter )
{
	CSipStack * pclsSipStack = (CSipStack *)lpParameter;
	struct timeval sttTime;
	time_t	iOldTime = 0;

	pclsSipStack->m_bStackThreadRun = true;

	while( pclsSipStack->m_bStopEvent == false )
	{
		gettimeofday( &sttTime, NULL );
		giTime = sttTime.tv_sec;
		pclsSipStack->Execute( &sttTime );
		MiliSleep( pclsSipStack->m_clsSetup.m_iStackExecutePeriod );

		if( giTime != iOldTime )
		{
			gclsSipDeleteQueue.DeleteTimeout();
			iOldTime = giTime;
		}
	}

	pclsSipStack->ThreadEnd( -1 );
	pclsSipStack->m_bStackThreadRun = false;

	return 0;
}

/**
 * @ingroup SipStack
 * @brief SIP stack thread 를 시작한다.
 * @param pclsSipStack SIP stack 객체
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool StartSipStackThread( CSipStack * pclsSipStack )
{
	return StartThread( "SipStackThread", SipStackThread, pclsSipStack );
}
