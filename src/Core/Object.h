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

#ifndef __OBJECT_H__
#define __OBJECT_H__

/** \class Object
 * Object in 3-space
 * Uses a model and other data to render
 */
class Object {
private:
	// Positional Matrix
	glm::mat4		mMatrix;

	// Model reference
	const Model*	mModel;	

protected:
	// Constructors
	Object(const Model* m) { mModel = m; mMatrix = glm::mat4(1.0f); }
	Object(const Model& m) { mModel = &m; mMatrix = glm::mat4(1.0f);}

public:
	// Create an Object
	static Object* create(const Model* m);
	static inline Object* create(const Model& m) { return create(&m); }

	// Gets the model reference
	const Model* getModel() const { return mModel; }

	// Gets the matrix
	glm::mat4 getMatrix() const { return mMatrix; }
};

#endif //__OBJECT_H__