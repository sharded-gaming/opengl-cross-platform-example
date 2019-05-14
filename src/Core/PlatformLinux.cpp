/**
 * Code developed and maintained by Sharded-Games.
 * Licensed under the GPLv3
 *
 * @author Dave Cotterill
 *
 * (c)2018 ShardedGames.com, https://github.com/sharded-gaming/opengl-cross-platform-example
 *
 * Please keep this notice here AS IS going forward.
 */

#include "Core.h"

#ifdef PLATFORM_LINUX

int main(int argc, char *argv[])
{
	Platform::initialise();
	return EXIT_SUCCESS;
}

U64 Platform::getTickCountMS()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (U64)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
}

void Platform::initialise()
{
    SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

   /* initialize SDL2 */
    int ec;
    if ((ec = SDL_Init(SDL_INIT_VIDEO)) < 0) 
	{
        printf("Error: couldn't initialize SDL2. EC %d\n", ec);
        printf("SDL Error: %s\n", SDL_GetError());
    }

    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mRender = Render::initialise();


	mGame = startup();
	mGame->initialise();


	U64 lastTick = 0;
    bool quit = false;
	SDL_Event event;

	while(!quit)
	{
		// 1. Process Keys
  		while( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
      			case SDL_KEYDOWN: 
				  	{
					  	Key *k = findKey(event.key.keysym.scancode);
					  	if(k)
					  	{
							k->mEventKeyState = KEY_DOWN;
						}				
				  	}
					break;

      			case SDL_KEYUP:
				  	{
					  	Key *k = findKey(event.key.keysym.scancode);
					  	if(k)
					  	{
							k->mEventKeyState = KEY_UP;
						}				
				  	}
					break;
			        break;

      			default:
        			break;
			}
		}

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
		mGame->onRender(mRender);
        SDL_GL_SwapWindow(window);
	};

	SDL_Quit();
}


#endif