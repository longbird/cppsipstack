#ifndef _ANDROID_CLASS_CONVERT_H_
#define _ANDROID_CLASS_CONVERT_H_

#include <jni.h>
#include "SipUserAgent.h"

bool GetSipServerInfo( JNIEnv * env, jobject clsSipServerInfo, CSipServerInfo & clsOutput );
bool GetSipStackSetup( JNIEnv * env, jobject clsSipStackSetup, CSipStackSetup & clsOutput );

#endif