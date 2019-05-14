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

#ifndef __IGAME_H__
#define __IGAME_H__

class IGame {
private:
	

protected:
	IGame() {}

public:
	~IGame() {}

	virtual void initialise() = 0;
	virtual void onFocus() = 0;
	virtual void onLost() = 0;
	virtual void onQuit() = 0;
	virtual bool onUpdate(int) = 0;
	virtual void onRender(Render*) = 0;

	virtual const char* getName() = 0;
};

#endif //__IGAME_H__