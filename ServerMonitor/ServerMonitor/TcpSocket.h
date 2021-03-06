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

#pragma once

#include "SipTcp.h"
#include <list>

#define TCP_TIMEOUT	10

/**
 * @ingroup ServerMonitor
 * @brief 모니터링 명령 저장 클래스
 */
class CMonitorCommand
{
public:
	std::string		m_strCommand;
	CListCtrl			* m_pclsListCtrl;
	CMonitorEntry m_clsEntry;
};

typedef std::list< CMonitorCommand > MONITOR_COMMAND_LIST;

/**
 * @ingroup ServerMonitor
 * @brief 모니터링 클라이언트
 */
class CTcpSocket
{
public:
	CTcpSocket();
	virtual ~CTcpSocket();

	bool Connect( const char * pszIp, int iPort );
	bool Connect( );
	void Close( );
	int Poll( );
	bool IsConnected();

	bool Receive( );

	bool AddCommand( const char * pszCommand, CListCtrl * pclsListCtrl, CMonitorEntry & clsEntry );
	bool DeleteCommand( const char * pszCommand, CListCtrl * pclsListCtrl );
	bool Execute();
	bool SendCommand( const char * pszCommand );

private:
	MONITOR_COMMAND_LIST	m_clsCommandList;
	MONITOR_COMMAND_LIST	m_clsSendCommandList;
	CMutex								m_clsMutex;
	char                  m_szSendPacket[2048];
	Socket                m_hSocket;
	std::string           m_strIp;
	int                   m_iPort;

	void SetItemText( const char * pszBuf, CMonitorCommand & clsCommand, int & iPos, int & i, int iRow, int iColumn );
	void ParseRecvData( const char * pszBuf, CMonitorCommand & clsCommand );
};

extern CTcpSocket gclsSocket;
