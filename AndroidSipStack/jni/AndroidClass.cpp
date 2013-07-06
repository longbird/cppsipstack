#include "AndroidClass.h"
#include "AndroidLog.h"

CAndroidClass gclsClass;

CAndroidClass::CAndroidClass()
{
}

CAndroidClass::~CAndroidClass()
{
}

bool CAndroidClass::Init( JNIEnv * env, jclass jcSipUserAgent )
{
	m_jEnv = env;
	m_jcSipUserAgent = jcSipUserAgent;

	m_jcSipServerInfo = m_jEnv->FindClass( "com/cppsipstack/SipServerInfo" );
	if( m_jcSipServerInfo == NULL )
	{
		AndroidErrorLog( "com/cppsipstack/SipServerInfo is not found" );
		return false;
	}

	m_jcSipCallRtp = m_jEnv->FindClass( "com/cppsipstack/SipCallRtp" );
	if( m_jcSipCallRtp == NULL )
	{
		AndroidErrorLog( "com/cppsipstack/SipCallRtp is not found" );
		return false;
	}

	m_jmEventRegister = m_jEnv->GetStaticMethodID( jcSipUserAgent, "EventRegister", "(Lcom/cppsipstack/SipServerInfo;I)V" );
	if( m_jmEventRegister == NULL )
	{
		AndroidErrorLog( "EventRegister is not found" );
		return false;
	}

	m_jmEventIncomingCall = m_jEnv->GetStaticMethodID( jcSipUserAgent, "EventIncomingCall"
		, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lcom/cppsipstack/SipCallRtp;)V" );
	if( m_jmEventIncomingCall == NULL )
	{
		AndroidErrorLog( "EventIncomingCall is not found" );
		return false;
	}
	
	m_jmEventCallRing = m_jEnv->GetStaticMethodID( jcSipUserAgent, "EventCallRing", "(Ljava/lang/String;ILcom/cppsipstack/SipCallRtp;)V" );
	if( m_jmEventCallRing == NULL )
	{
		AndroidErrorLog( "EventCallRing is not found" );
		return false;
	}
	
	m_jmEventCallStart = m_jEnv->GetStaticMethodID( jcSipUserAgent, "EventCallStart", "(Ljava/lang/String;Lcom/cppsipstack/SipCallRtp;)V" );
	if( m_jmEventCallStart == NULL )
	{
		AndroidErrorLog( "EventCallStart is not found" );
		return false;
	}
	
	m_jmEventCallEnd = m_jEnv->GetStaticMethodID( jcSipUserAgent, "EventCallEnd", "(Ljava/lang/String;I)V" );
	if( m_jmEventCallEnd == NULL )
	{
		AndroidErrorLog( "EventCallEnd is not found" );
		return false;
	}

	m_jmSipServerInfoInit = m_jEnv->GetMethodID( m_jcSipServerInfo, "<init>", "()V" );
	if( m_jmSipServerInfoInit == NULL )
	{
		AndroidErrorLog( "SipServerInfo<init> is not found" );
		return false;
	}

	m_jmSipCallRtpInit = m_jEnv->GetMethodID( m_jcSipCallRtp, "<init>", "()V" );
	if( m_jmSipCallRtpInit == NULL )
	{
		AndroidErrorLog( "SipCallRtp<init> is not found" );
		return false;
	}

	return true;
}