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

#ifndef __RENDER_H__
#define __RENDER_H__

/** \class Render
 * Renders to a viewport any and all required objects
 */
class Render {
private:
	// Gets a shader compilation status / info log etc
	static bool checkShaderCompileStatus(GLuint shader, bool program = false);

	glm::vec3 mClearColour;

protected:
	/** 
	 * Constructor
	 */
	Render() : mClearColour(0.0f, 0.0f, 0.0f) {}

public:
	/**
	 * Initialise the renderer 
	 */
	static Render* initialise();

	/** 
	 * Load/Compiler a shader program
	 */
	static ShaderProgram loadShaderProgram(const char* vertShader, const char* fragShader, const char* geometrySource = NULL);

	/** Render an Object
	 */
	void  renderObject(const Viewport* viewPort,const Camera* camera, const Object*);
	inline void  renderObject(const Viewport& viewPort, const Camera& camera, const Object& r) { renderObject(&viewPort, &camera, &r); }

	/** 
	 * Sets the background clear colour
	 */
	inline void setClearColour(glm::vec3 c) 
	{
		mClearColour = c;
	}

	/** 
	 * Clear the viewport to black
	 */
	inline void clear() {
		glClearColor(mClearColour.r, mClearColour.g, mClearColour.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}


};

#endif //__RENDER_H__