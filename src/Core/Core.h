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

#ifndef __CORE_H__
#define __CORE_H__

// Platform Definitions
#ifdef _WIN32 
	#define PLATFORM_WINDOWS
#elif defined(__ANDROID__)
	#define PLATFORM_ANDROID
#elif defined(__APPLE__)
	#define PLATFORM_OSX
#elif defined(__linux__)
	#define PLATFORM_LINUX
#else
	#define PLATFORM_WASM
#endif

// System / Platform Includes
#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
	#define GL_GLEXT_PROTOTYPES 1
	#include <GL/glew.h>
#elif defined(PLATFORM_LINUX)
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	#define GL_GLEXT_PROTOTYPES 1
	#include <SDL2/SDL.h>
	//#include <SDL2/SDL_opengl.h>
	#include <SDL2/SDL_opengles2.h>
	
	using namespace std;
#else
	#include <emscripten.h>
	#include <functional>
	//#include <pthread.h>
	#include <emscripten/fetch.h>

	#define GL_GLEXT_PROTOTYPES 1
	#include <GLES2/gl2.h>
	#include <EGL/egl.h>
	#include <emscripten/Html5.h>
	#include <time.h>
	#include <stdio.h>
#endif

// Library Includes
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Global Definitions
typedef unsigned char		U8;
typedef signed char			S8; 
typedef unsigned short		U16;
typedef signed short		S16;
typedef unsigned int		U32;
typedef signed int			S32;
typedef int64_t				S64;
typedef uint64_t			U64;

typedef GLuint ShaderProgram;

// CRT Memory Debugging Dump for Win32
#ifdef _DEBUG
	#ifdef PLATFORM_WINDOWS
		#define _CRTDBG_MAP_ALLOC
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	#else
		#define DBG_NEW new
	#endif
#else
	#define DBG_NEW new
#endif

// Debug logging
#ifdef PLATFORM_WINDOWS
#define DEBUGLOG OutputDebugString
#elif defined(PLATFORM_WASM) 
#define DEBUGLOG printf
#elif defined(PLATFORM_LINUX)
#define DEBUGLOG(a) printf("%s", a)
#endif

/* Standard Macros */
#define SAFEDELETE(ptr)	\
	if(ptr)	\
	{ \
		delete (ptr); \
		ptr=NULL; \
	}

#define SAFEDELETEARRAY(ptr) \
	if(ptr) \
	{ \
		delete[] (ptr); \
		ptr = NULL; \
	}

#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

// Library Includes
#include "List.h"
#include "Model.h"
#include "Viewport.h"
#include "Object.h"
#include "Camera.h"
#include "Render.h"
#include "IGame.h"
#include "Thread.h"
#include "FileManager.h"
#include "PlatformBase.h"
#include "PlatformWindows.h"
#include "PlatformWasm.h"
#include "PlatformLinux.h"

// Required method to hook into the game
extern IGame* startup();

#endif //__CORE_H__