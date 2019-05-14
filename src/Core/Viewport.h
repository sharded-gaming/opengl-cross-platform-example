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

#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

/** \class Viewport
 * Used to render to a subset (or entire) screen/window
 */
class Viewport {
private:	
	glm::mat4	mProjection;
	U32			mWidth;
	U32			mHeight;

protected:
	// Constructor
	Viewport() {}

public:
	//Destructor
	~Viewport() {}

	// Creates a viewport with set dimensions
	static Viewport* create(U32 w, U32 h);

	// Viewport information
	inline U32 getWidth() const	{ return mWidth; }
	inline U32 getHeight() const { return mHeight; }
	inline float getFovy() const { return glm::radians(45.0f); }
	inline float getNear() const { return 0.1f; }
	inline float getFar() const { return 100.0f; }
};

#endif //__VIEWPORT_H__