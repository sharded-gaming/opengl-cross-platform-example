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

#ifndef __THREAD_H__
#define __THREAD_H__

/** \class Thread
 * Handles threading for the platform
 */
class Thread {
public:
#ifdef PLATFORM_WINDOWS
	static DWORD WINAPI threadProc(LPVOID lpParam);
#else
	static void* threadProc(void *arg);
#endif

private:
#ifdef PLATFORM_WINDOWS
	HANDLE	mThread;
#else 
	//pthread_t	mThread;
	void* mThread;
#endif

protected:
	Thread();

	virtual U32 run() = 0;
public:
	~Thread();

	/** Thread Control */
	void	start();
	bool	isRunning();
};

#endif //__THREAD_H__