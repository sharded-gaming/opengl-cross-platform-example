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

#ifndef __PLATFORMLINUX_H__
#define __PLATFORMLINUX_H__

#ifdef PLATFORM_LINUX
/**
 * Platform class, handles all specific 'platform' calls.
 */

class Platform : public PlatformBase {
public:

	// Gets ticks since inception
	static U64 getTickCountMS();
protected:
	// Constructur
	Platform() {}

public:

	// Initialise the platform
	static void initialise();


};
#endif

#endif //__PLATFORMLINUX_H__