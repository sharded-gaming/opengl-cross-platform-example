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

#ifndef __GAME_H__
#define __GAME_H__

#include "Core.h"

/** \class Game
 * Basic game example code
 */
class Game : public IGame {
public:
	Platform::KeyCode mLeftKey, mRightKey;

	/** Initialise 
	 * Called first after the startup() method once the Game object has been constructed
	 */
	void initialise();

	/** onFocus
	 * Called when focus is applied
	 */
	void onFocus();

	/** onLost
	 * Called when focus on the window has been lost
	 */
	void onLost();

	/** onQuit
	 * Called when the user has attempted to close the game
	 */
	void onQuit();

	/** onUpdate 
	 * Called periodically whenever an update is required
	 * @param tDelta Time delta since last call was started
	 * @return true if still running or false otherwhise
	 */
	bool onUpdate(int tDelta);

	/** onRender
	 * Called when a render is required, may not be in-sync with update
	 * @param Render object
	 */
	void onRender(Render *render);

	/** getName
	 * Returns the application/game's name
	 */
	const char* getName() { return "Shard"; }

};

#endif //__GAME_H__