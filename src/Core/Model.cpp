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


Model* Model::create(ShaderProgram program, const void* data, U32 count, const ModelFormat& format)
{
	Model * ret = NULL;

	if(data && count > 0)
	{
		ret = new Model();
		if(ret)
		{
			ret->mCount = count;

			// Create a Vertex Buffer Object and copy the vertex data to it
			glGenBuffers(1, &ret->mVertexBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, ret->mVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, format.mPitch * count, data, GL_STATIC_DRAW);

			// Specify the layout of the vertex data
			ret->mShaderProgram = program;

			// Setup Locations in buffer
			if (format.mVertexIndex >= 0)
			{
				GLint posAttrib = glGetAttribLocation(ret->mShaderProgram, "position");
				glEnableVertexAttribArray(posAttrib);
				glVertexAttribPointer(posAttrib, format.mVertexComponentCount, GL_FLOAT, GL_FALSE, format.mPitch, (GLvoid*)(format.mVertexIndex));
			}

		}
	}

	return ret;
}

