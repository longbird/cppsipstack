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

#include "KSipServer.h"
#include "SipParserDefine.h"
#include "XmlUser.h"
#include "XmlElement.h"
#include "SipServerSetup.h"
#include "Directory.h"
#include "MemoryDebug.h"

CXmlUser::CXmlUser() : m_bDnd(false)
{
}

CXmlUser::~CXmlUser()
{
}

/**
 * @ingroup KSipServer
 * @brief XML 파일을 읽어서 SIP 사용자 정보를 가져온다.
 * @param pszFileName XML 파일 이름
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool CXmlUser::Parse( const char * pszFileName )
{
	CXmlElement clsXml;

	Clear();

	if( clsXml.ParseFile( pszFileName ) == false ) return false;

	clsXml.SelectElementData( "Id", m_strId );
	clsXml.SelectElementData( "PassWord", m_strPassWord );

	std::string	strTemp;

	if( clsXml.SelectElementData( "DND", strTemp ) )
	{
		if( !strcasecmp( strTemp.c_str(), "true" ) )
		{
			m_bDnd = true;
		}
	}

	clsXml.SelectElementData( "CallForward", m_strCallForward );
	clsXml.SelectElementData( "GroupId", m_strGroupId );

	if( m_strId.empty() ) return false;

	return true;
}

/**
 * @ingroup KSipServer
 * @brief 내부 변수를 초기화시킨다.
 */
void CXmlUser::Clear()
{
	m_strId.clear();
	m_strPassWord.clear();
	m_bDnd = false;
	m_strCallForward.clear();
}

/**
 * @ingroup KSipServer
 * @brief 착신거부 ( Do Not Disturb ) 인가?
 * @returns 착신거부이면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CXmlUser::IsDnd()
{
	return m_bDnd;
}

/**
 * @ingroup KSipServer
 * @brief 착신전환 ( Call Forward ) 인가?
 * @returns 착신전환이면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CXmlUser::IsCallForward()
{
	if( m_strCallForward.empty() ) return false;

	return true;
}

/**
 * @ingroup KSipServer
 * @brief SIP 사용자 정보를 XML 파일 또는 MySQL 에서 읽어서 저장한다.
 * @param pszUserId SIP 사용자 아이디
 * @param clsUser		SIP 사용자 정보 저장 객체
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool SelectUser( const char * pszUserId, CXmlUser & clsUser )
{	
	std::string	strFileName = gclsSetup.m_strUserXmlFolder;

	CDirectory::AppendName( strFileName, pszUserId );
	strFileName.append( ".xml" );

	return clsUser.Parse( strFileName.c_str() );
}
