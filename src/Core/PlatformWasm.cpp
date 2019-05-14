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

#ifdef PLATFORM_WASM
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE Platform::mContext;

std::function<void()> loop;
void main_loop() { loop(); }

int main()
{
	Platform::initialise();
	return EXIT_SUCCESS;
}

EM_BOOL Platform::keyCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
{
	Key *k = NULL;

	//printf("KEY %lu\n", keyEvent->keyCode);

	for (U32 i = 0; i < mRegisteredKeys.length() && !k; i++)
	{
		Key *t = mRegisteredKeys.get(i);
		if (t)
		{
			if (t->mKeyCode == keyEvent->keyCode)
			{
				k = t;
			}
		}
	}
	
	if (k)
	{
		if (eventType == EMSCRIPTEN_EVENT_KEYDOWN)
		{
			k->mEventKeyState = KEY_DOWN;
		}
		else if (eventType == EMSCRIPTEN_EVENT_KEYUP)
		{
			k->mEventKeyState = KEY_UP;
		}
	}

	return true;
}

U64 Platform::getTickCountMS()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (U64)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
}

void Platform::initialise()
{
	mRender = Render::initialise();

	// Context configurations
	EmscriptenWebGLContextAttributes attrs;
	attrs.explicitSwapControl = 0;
	//attrs.renderViaOffscreenBackBuffer = 1;
	attrs.depth = 1;
	attrs.stencil = 1;
	attrs.antialias = 1;
	attrs.majorVersion = 2;
	attrs.minorVersion = 0;

	char canvasName[] = "canvas";

	mContext = emscripten_webgl_create_context(canvasName, &attrs);
	emscripten_webgl_make_context_current(mContext);


	mGame = startup();
	mGame->initialise();

	emscripten_set_keydown_callback("#canvas", nullptr, true, Platform::keyCallback);
	emscripten_set_keyup_callback("#canvas", nullptr, true, Platform::keyCallback);

	U64 lastTick = 0;

	loop = [&]
	{
		// 1. Process Keys
		for (U32 i = 0; i < mRegisteredKeys.length(); i++)
		{
			Key *k = mRegisteredKeys.get(i);
			if (k)
			{
				k->mLastState = k->mState;
				bool down = k->mEventKeyState == KEY_DOWN;
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
						k->mState = KEY_UP;
					}
				}
			}
		}

		// 2. Calculate Timedelta
		U64 cTick = getTickCountMS();
		U64 tickDelta = 0;
		if(lastTick != 0)
		{
			tickDelta = cTick - lastTick;
		}
		lastTick = cTick;

		// 3. Update Game
		mGame->onUpdate((U32)tickDelta);

		// 4. Update Render
		emscripten_webgl_make_context_current(mContext);
		mGame->onRender(mRender);

	};

	emscripten_set_main_loop(main_loop, 0, true);

}


#endif