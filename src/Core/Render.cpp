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

Render* Render::initialise()
{
#if defined( PLATFORM_WINDOWS ) || defined (PLATFORM_LINUX)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepthf(1.0f);
	glViewport(0, 0, 640,480);
#endif

	return new Render();
}

/**
 * Load/Compiler a shader program
 */
ShaderProgram Render::loadShaderProgram(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
ShaderProgram ret = 0;

	if (vertexSource && fragmentSource)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, nullptr);
		glCompileShader(vertexShader);
		checkShaderCompileStatus(vertexShader);

		// Create and compile the fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShader);
		checkShaderCompileStatus(fragmentShader);

		GLuint geoShader;
#ifdef PLATFORM_WINDOWS
		if(geometrySource)
		{
			geoShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geoShader, 1, &geometrySource, nullptr);
			glCompileShader(geoShader);
			checkShaderCompileStatus(geoShader);
		}
#endif 
		// Link the vertex and fragment shader into a shader program
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		if(geometrySource)
		{
			glAttachShader(shaderProgram, geoShader);
		}
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);
		checkShaderCompileStatus(shaderProgram, true);

		ret = shaderProgram;
	}

	return ret;
}

bool Render::checkShaderCompileStatus(GLuint shaderId, bool isProgram)
{
bool ret = true;

#if defined( PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
	GLint success;
	GLchar infoLog[1024];
	if(!isProgram)
	{
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
			DEBUGLOG(infoLog);
			ret = false;
		}
	}
	else
	{
		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetProgramInfoLog(shaderId, 1024, NULL, infoLog);
			DEBUGLOG(infoLog);
			ret = false;
		}
	}
#endif

	return ret;
}

/** Render an Object
 */
void Render::renderObject(const Viewport* viewPort, const Camera* camera, const Object *obj)
{
	GLint shader = obj->getModel()->getShader();

	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(viewPort->getFovy(), (float)viewPort->getWidth() / (float)viewPort->getHeight(), viewPort->getNear(), viewPort->getFar());
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);

	// camera/view transformation
	glm::mat4 view = camera->getViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);

	// calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model = obj->getMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, obj->getModel()->getCount());
}
