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

#ifndef __PLATFORMWINDOWS_H__
#define __PLATFORMWINDOWS_H__

#ifdef PLATFORM_WINDOWS
/**
 * Platform class, handles all specific 'platform' calls.  
 */

class Platform : public PlatformBase {
public:
	/** \class AppThread
	 * Actually runs the app in a different thread to the message pump
	 */
	class AppThread : public Thread {
	private:

	public:
		AppThread() {}
		U32 run();
	};

private:
	// Window Data
	static HWND mWindow;
	static HDC mHDC;
	static HGLRC mHRC;
	static HINSTANCE mInstance;
	static AppThread *mAppThread;

protected:
	// Constructor
	Platform() {}

public:
	// Windows Handling methods
	static BOOL createWindow(int nCmdShow);
	static BOOL prepareWindow();
	static LRESULT	CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Initialise the platform
	static void initialise(HINSTANCE hInst, int nCmdShow);

};
#endif

#endif //__PLATFORMWINDOWS_H__