/**
 * Code developed and maintained by Sharded-Games.
 * Licensed under the GPLv3
 *
 * @author Dave Cotterill
 *
 * (c)2018 ShardedGames.com, https://github.com/sharded-gaming/opengl-cross-platform-example
 *
 * Please keep this notice here AS IS going forward.
 * ShardedGames and the author provide no warranty and liability for the code provided AS IS.
 */

#include "Core.h"

#ifndef PLATFORM_WINDOWS
#include <pthread.h>
#endif

Thread::Thread() : 	mThread(NULL)
{
#ifdef PLATFORM_WINDOWS
	mThread = CreateThread(NULL, 0, threadProc, (LPVOID)this, CREATE_SUSPENDED, NULL);
#else 
	/*if (pthread_create(&mThread, NULL, threadProc, (void*)this)) {
		//perror("Thread create failed");
	}*/
#endif
}

Thread::~Thread()
{
#ifdef PLATFORM_WINDOWS
	CloseHandle(mThread);
#else

#endif
}

#ifdef PLATFORM_WINDOWS
DWORD WINAPI Thread::threadProc(LPVOID lpParam)
{
	Thread *thread = (Thread*)lpParam;
	return thread->run();
}
#else 
void* Thread::threadProc(void *arg) 
{
	Thread* thread = (Thread*)arg;
	if(thread)
	{
		thread->run();
	}
	return arg;
}
#endif

void Thread::start()
{
#ifdef PLATFORM_WINDOWS
	ResumeThread(mThread);
#endif
}

bool Thread::isRunning()
{
	bool ret = false;

#ifdef PLATFORM_WINDOWS
	if (mThread)
	{
		DWORD result = 0;
		if (GetExitCodeThread(mThread, &result) != 0)
		{
			ret = result == STILL_ACTIVE;
		}
	}
#endif
	return ret;
}