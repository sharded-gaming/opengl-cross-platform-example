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

#ifndef __MODEL_H__
#define __MODEL_H__

/** modelFormat Structure
 * Defines how the model looks from the data point of view
 */
typedef struct __tag_ModelFormat {
	S32		mPitch;

	S32		mVertexIndex;
	S32		mVertexComponentCount;

	S32		mColorIndex;
	S32		mColorComponentCount;

	S32		mNormalIndex;
	S32		mNormalComponentCount;

} ModelFormat;

/**
 * \class ModelData 
 */
class ModelData {
private:
	ModelFormat		mFormat;

public:

};

/** \class Model
 */
class Model {
private:
	ModelFormat		mFormat;
	GLuint			mVertexBuffer;
	ShaderProgram	mShaderProgram;
	U32				mCount;

protected:
	Model() : mVertexBuffer(0), mShaderProgram(0) {}

public:
	// Create a model
	static Model*	create(ShaderProgram program, const void* data, U32 count, const ModelFormat& format);

	// Face and/or vertex count;
	U32 getCount() const { return mCount; }
	
	// Shader 
	ShaderProgram getShader() const { return mShaderProgram; }

	// Modify Data in Buffer
	ModelData&		lock();
	void			unlock(ModelData&);
};

#endif //__MODEL_H__