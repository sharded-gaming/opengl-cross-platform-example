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

#include "game.h"

// Shader sources
const GLchar* vertexSource =
"attribute vec4 position;											\n"
"uniform mat4 model;												\n"
"uniform mat4 view;													\n"
"uniform mat4 projection;											\n"
"void main()														\n"
"{																	\n"
"	gl_Position = projection * view * model * position;		\n"
"}																	\n";


const GLchar* fragmentSource =
#ifndef PLATFORM_LINUX
"precision mediump float;\n"
#endif
"void main()                                  \n"
"{                                            \n"
"  gl_FragColor[0] = gl_FragCoord.x/640.0;    \n"
"  gl_FragColor[1] = gl_FragCoord.y/480.0;    \n"
"  gl_FragColor[2] = 0.5;                     \n"
"}                                            \n";

// an example of something we will control from the javascript side
bool mQuitRequested = false;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,//  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,//  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,//  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,//  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,//  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,//  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,//  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,//  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,// 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,//  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,//  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,//  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,// 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,//  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,//  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,//  0.0f, 1.0f
};


Object * mObject = NULL;
Camera *mCamera = NULL;
Viewport *mViewport = NULL;

IGame* startup()
{
	return new Game();
}

void Game::initialise()
{
	// View and camera
	mViewport = Viewport::create(640,480);
	mCamera = Camera::create(glm::vec3(0.0f,0.0f,3.0f));

	// Create and compile the vertex shader
	ShaderProgram basicShader = Render::loadShaderProgram(vertexSource, fragmentSource);

	// Load Model
	Model *m = Model::create(basicShader, vertices, (sizeof(vertices) / sizeof(GLfloat))/3, { sizeof(GLfloat)*3, 0,3, -1,0, -1,0 });
	if(m)
	{
		mObject = Object::create(m);
	}

	// Register Keys
	mLeftKey = Platform::registerKey(VKEY_A);
	mRightKey = Platform::registerKey(VKEY_D);

}

void Game::onFocus()
{
}

void Game::onLost()
{
}

void Game::onQuit()
{
	mQuitRequested = true;	
}

bool Game::onUpdate(int)
{
bool isRunning = true;

	if(mQuitRequested)
	{
		isRunning = false;
	}
	else
	{
		if(Platform::isKeyDown(mLeftKey))
		{
			mCamera->move(0.01f,0,0);
		}
		if (Platform::isKeyDown(mRightKey))
		{
			mCamera->move(-0.01f, 0, 0);
		}
	}

	return isRunning;
}

void Game::onRender(Render *render)
{
	// Clear the screen
	render->clear();

	// Draw an object
	render->renderObject(mViewport, mCamera, mObject);
}
