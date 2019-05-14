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

#ifdef PLATFORM_WINDOWS

#include <functional>

#include <Windows.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>

U32 mWidth = 640;
U32 mHeight = 480;
U32 mDepth = 24;

HWND Platform::mWindow = NULL;
HDC	Platform::mHDC = NULL;
HGLRC Platform::mHRC = NULL;
HINSTANCE Platform::mInstance = NULL;
Platform::AppThread* Platform::mAppThread = NULL;

// windowProc  
LRESULT	CALLBACK Platform::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//POINTS	pointerPosition;

	switch (uMsg)
	{
		case WM_CREATE:
			return TRUE;

		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;

		case WM_CLOSE:
			PostQuitMessage(0);
			return TRUE;

		case WM_LBUTTONDOWN:
			/*pointerPosition = MAKEPOINTS(lParam);
			MInputCallbacks::processEvent(MInputCallbacks::INPUTEVENT_POINTER_DOWN, 0, pointerPosition.x, pointerPosition.y);
			SetCapture(hWnd);*/
			break;

		case WM_MOUSEMOVE:
			if ((wParam & MK_LBUTTON) != 0)
			{
				/*pointerPosition = MAKEPOINTS(lParam);
				MInputCallbacks::processEvent(MInputCallbacks::INPUTEVENT_POINTER_DOWN, 0, pointerPosition.x, pointerPosition.y);*/
			}
			break;

		case WM_LBUTTONUP:
			/*pointerPosition = MAKEPOINTS(lParam);
			MInputCallbacks::processEvent(MInputCallbacks::INPUTEVENT_POINTER_UP, 0, pointerPosition.x, pointerPosition.y);
			ReleaseCapture();
			*/
			break;

		/*case WM_GETMINMAXINFO: {
			RECT r;
			GetWindowRect(hWnd, &r);
			MINMAXINFO *mm = (MINMAXINFO *)lParam;
			mm->ptMaxSize.x = r.right - r.left;
			mm->ptMaxSize.y = r.bottom - r.top;
			return 0;
		}*/

		/*case WM_SIZE:
			switch (wParam)
			{
				case SIZE_MAXIMIZED:
					mRenderWindow->setFullscreen(true);
					return 0;

				case SIZE_RESTORED:
					mRenderWindow->setFullscreen(false);
					return 0;

				case SIZE_MINIMIZED:
					// Pause
					return 0;
				}
			}
			break;*/

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/**
 * Creates the window
 */
BOOL Platform::createWindow(int nCmdShow)
{
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	DWORD       width = mWidth;
	DWORD       height = mHeight;
	RECT        appRect = { 50,50,width + 50,height + 50 };
	HICON		ico = NULL;
	int			len = strlen(mGame->getName()) + 4;
	char		*className = new char[len];
	strcpy_s(className,len,mGame->getName());
	strcat_s(className,len,"cls");

	// Create the class
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_SAVEBITS;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)windowProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = mInstance;							// Set The Instance
	wc.hIcon = ico;//LoadIcon(appINSTANCE, MAKEINTRESOURCE(IDI_APPICON));		// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.lpszClassName = className;	// Set The Class Name
	wc.lpszMenuName = NULL;//MAKEINTRESOURCE(IDR_MENU);     // We Want A Menu
	wc.hbrBackground = NULL;	                            // Background for workspace

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, TEXT("Failed To Register The Window Class."), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	dwExStyle = 0;//WS_EX_WINDOWEDGE;			                                // Window Extended Style
	dwStyle = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	AdjustWindowRectEx(&appRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create the app window
	if (!(mWindow = CreateWindowEx(dwExStyle,	   						// Extended Style For The Window
		className,
		mGame->getName(),
		dwStyle, 							// Defined Window Style
		appRect.left,
		appRect.top,					// Window Position
		appRect.right - appRect.left,   // WindowRect.right,
		appRect.bottom - appRect.top,
		NULL,							// No Parent Window
		NULL,							// No Menu
		mInstance,						// Instance
		NULL)))							// Dont Pass Anything To WM_CREATE
	{
		MessageBox(NULL, TEXT("Failed To Create Window"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	SAFEDELETE(className);

	// Failed
	return TRUE;
}

/**
 * Prepares the window and the opengl stuff
 */
BOOL Platform::prepareWindow()
{
	BOOL ret = false;


	GLuint	PixelFormat;			// Holds The Results After Searching For A Match

	//mFullscreen = fs;
	//mFullscreenFrequency = 0;
	//mWidth = w;
	//mHeight = h;
	//mDepth = d;

	//mFullscreenPossible = false;
	DEVMODE dm;
	dm.dmSize = sizeof(DEVMODE);
	dm.dmDriverExtra = 0;
	DWORD id = 0;
	while (EnumDisplaySettings(NULL, id, &dm))
	{
		if (dm.dmPelsWidth == mWidth && dm.dmPelsHeight == mHeight && dm.dmBitsPerPel == mDepth)
		{
			//mFullscreenFrequency = max(mFullscreenFrequency, dm.dmDisplayFrequency);
			//mFullscreenPossible = true;
		}

		id++;
	}

	//setFullscreen(fs);

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		(BYTE)mDepth,									// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(mHDC = GetDC(mWindow)))							// Did We Get A Device Context?
	{
		MessageBox(NULL, TEXT("Can't Create A GL Device Context."), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}

	if (!(PixelFormat = ChoosePixelFormat(mHDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		MessageBox(NULL, TEXT("Can't Find A Suitable PixelFormat."), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}

	if (!SetPixelFormat(mHDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		MessageBox(NULL, TEXT("Can't Set The PixelFormat."), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}

	if (!(mHRC = wglCreateContext(mHDC)))				// Are We Able To Get A Rendering Context?
	{
		MessageBox(NULL, TEXT("Can't Create A GL Rendering Context."), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}

	if (!wglMakeCurrent(mHDC, mHRC))					// Try To Activate The Rendering Context
	{
		MessageBox(NULL, TEXT("Can't Activate The GL Rendering Context."), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}

	// Prepare GL Settings

	// Disable current thread access to GL
	wglMakeCurrent(mHDC, mHRC);
	ret = TRUE;

	return ret;
}

U32 Platform::AppThread::run()
{
	bool isRunning = true;
	U32 lastTick = 0;

	if (prepareWindow())
	{
		glewInit();

		Platform::mRender = Render::initialise();

		mGame->initialise();

		while (isRunning)
		{
			// 1. Process Keys
			for (U32 i = 0; i < mRegisteredKeys.length(); i++)
			{
				Key *k = mRegisteredKeys.get(i);
				if (k)
				{
					k->mLastState = k->mState;
					BOOL down = GetAsyncKeyState(k->mKeyCode);
					if (down)
					{
						k->mState = KEY_DOWN;
					}
					else
					{
						if (k->mState == KEY_DOWN)
						{
							k->mState = KEY_RELEASED;
						}
						else
						{
							k->mState == KEY_UP;
						}
					}
				}
			}
			

			// 2. Calculate the tick delta
			U32 tickDelta = 0;
			U32 cTick = GetTickCount();
			if(lastTick != 0)
			{
				tickDelta = cTick - lastTick;
			}
			lastTick = cTick;

			// 3. Run the update
			isRunning = mGame->onUpdate(tickDelta);

			// 4. Render
			mGame->onRender(mRender);
			SwapBuffers(mHDC);
		}
	}

	return 0;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR     lpCmdLine, int       nCmdShow)
{
	Platform::initialise(hInstance, nCmdShow);
	return EXIT_SUCCESS;
}

void Platform::initialise(HINSTANCE hInstance, int nCmdShow)
{
	mInstance = hInstance;
	mAppThread = new AppThread();

	mGame = startup();

	if (mGame && Platform::createWindow(nCmdShow))
	{

		ShowWindow(mWindow, nCmdShow);				// Show The Window
		SetForegroundWindow(mWindow);				// Slightly Higher Priority
		SetFocus(mWindow);							// Sets Keyboard Focus To The Window


		mAppThread->start();

		// do loop
		bool done = false;
		MSG msg;
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)	done = TRUE;
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
	SAFEDELETE(mGame);
}


#endif