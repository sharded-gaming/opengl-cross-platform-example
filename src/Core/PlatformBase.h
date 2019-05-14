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

#ifndef __PLATFORMBASE_H__
#define __PLATFORMBASE_H__

// Key Enumeration table
// Can be overridden on a platform by platform basis
enum {
#if defined(PLATFORM_LINUX)
	VKEY_A = SDL_SCANCODE_A,
#else
	VKEY_A = 65,
#endif
	VKEY_B,
	VKEY_C,
	VKEY_D,
	VKEY_E,
	VKEY_F,
	VKEY_G,
	VKEY_H,
	VKEY_I,
	VKEY_J,
	VKEY_K,
	VKEY_L,
	VKEY_M,
	VKEY_N,
	VKEY_O,
	VKEY_P,
	VKEY_Q,
	VKEY_R,
	VKEY_S,
	VKEY_T,
	VKEY_U,
	VKEY_V,
	VKEY_W,
	VKEY_X,
	VKEY_Y,
	VKEY_Z,
};

/** \class PlatformBase
 * Base class for platforms
 */
class PlatformBase {
public:
	typedef enum __tag_keyState {
		KEY_UP = 0,
		KEY_DOWN,
		KEY_RELEASED
	} keyState;

	typedef struct Key {
		keyState mState;
		keyState mLastState;

#if defined(PLATFORM_WASM) || defined(PLATFORM_LINUX)
		keyState mEventKeyState;
#endif
		U32 mKeyID;
		U8 mKeyCode;
	} Key;
	typedef U32 KeyCode;

protected:
	static U32		mKeyID;
	static Render* mRender;
	static IGame*	mGame;
	static List<Key*> mRegisteredKeys;

	static Key* findKey(U8 key)
	{
		Key* ret = NULL;
		for(U32 i = 0 ; i < mRegisteredKeys.length() && !ret ; i++)
		{
			Key *k = mRegisteredKeys.get(i);
			if(k)
			{
				if(k->mKeyCode == key)
				{
					ret = k;
				}
			}
		}
		return ret;
	}

	static Key* findKeyID(U8 key)
	{
		Key* ret = NULL;
		for (U32 i = 0; i < mRegisteredKeys.length() && !ret; i++)
		{
			Key *k = mRegisteredKeys.get(i);
			if (k)
			{
				if (k->mKeyID == key)
				{
					ret = k;
				}
			}
		}
		return ret;
	}

public:

	// Register a key code for getting status
	static KeyCode registerKey(U8 key)		
	{ 
		S32 ret = -1;

		Key *k = findKey(key);
		if (!k)
		{
			mRegisteredKeys.length();
			Key *k = new Key();
			if (k)
			{
				k->mState = KEY_UP;
				k->mLastState = KEY_UP;
				k->mKeyCode = key;

				ret = mKeyID;
				k->mKeyID = ret;

				mRegisteredKeys.add(k);

				mKeyID++;
			}
		}
		else
		{
			ret = k->mKeyID;
		}

		return (KeyCode)ret;
	}

	// Deregister a key
	static void deregisterKey(KeyCode key)
	{
		bool ret = false;
		for (U32 i = 0; i < mRegisteredKeys.length() && !ret; i++)
		{
			Key *k = mRegisteredKeys.get(i);
			if (k)
			{
				if (k->mKeyID == key)
				{
					mRegisteredKeys.remove(k);
					ret = true;
				}
			}
		}
	}

	// Deregister all keys
	static void deregisterAllKeys()
	{
		mRegisteredKeys.deleteArray();
	}

	// Get Key 'status'
	static inline bool isKeyDown(KeyCode keyIndex)		{ return findKeyID(keyIndex)->mState == KEY_DOWN; }
	static inline bool isKeyUp(KeyCode keyIndex)		{ return findKeyID(keyIndex)->mState == KEY_UP || mRegisteredKeys.get(keyIndex)->mState == KEY_RELEASED; }
	static inline bool isKeyReleased(KeyCode keyIndex)	{ return findKeyID(keyIndex)->mState == KEY_RELEASED; }

};

#endif //__PLATFORMBASE_H__