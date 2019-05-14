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


#ifndef __CAMERA_H__
#define __CAMERA_H__

/** \class Camera
 * Basic camera class.
 */
class Camera {
private:
	// Data
	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mWorldUp;

	float mYaw;
	float mPitch;

	/** Update the camera positional data and matrix
	 */
	void update();

protected:
	/** Constructor */
	Camera();

public:
	/** Destructor */
	~Camera();

	/** Camera Creation 
	 * @param pos Initial position
	 * @return Camera
	 */
	static Camera* create(glm::vec3 pos);

	/** Gets the view matrix calculated using Euler Angles and the LookAt Matrix
	 * @returns the mat4 matrix
	 */
	glm::mat4 getViewMatrix() const	{
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	/** Move the camera
	 * @param x - x
	 * @param y - y
	 * @param z - z
	 */
	void move(float x, float y, float z) { mPosition.x += x; mPosition.y += y ; mPosition.z += z; }

	/** Rotate the camera around the X-Axis
	 * @param x radian to rotate
	 */
	void rotateX(float x) { mPitch += x; }
};

#endif //__CAMERA_H__