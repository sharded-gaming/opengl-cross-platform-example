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

#ifndef __PLATFORMWASM_H__
#define __PLATFORMWASM_H__

#ifdef PLATFORM_WASM
/**
 * Platform class, handles all specific 'platform' calls.
 */

class Platform : public PlatformBase {
public:
	// WebGL Context
	static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE mContext;

	// Gets ticks since inception
	static U64 getTickCountMS();
protected:
	// Constructur
	Platform() {}

public:
	// Keyboard callback handler
	static EM_BOOL keyCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);

	// Initialise the platform
	static void initialise();


};
#endif

#endif //__PLATFORMWASM_H__