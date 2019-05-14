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

Render* PlatformBase::mRender = NULL;
IGame*	PlatformBase::mGame = NULL;
List<PlatformBase::Key*> PlatformBase::mRegisteredKeys;
U32		PlatformBase::mKeyID = 1;