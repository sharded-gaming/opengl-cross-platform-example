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

Viewport* Viewport::create(U32 w, U32 h)
{
Viewport *ret = new Viewport();

	if(w && h && ret)
	{
		ret->mProjection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
		ret->mWidth = w;
		ret->mHeight = h;
	}
	else
	{
		SAFEDELETE(ret);
	}

	return ret;
}