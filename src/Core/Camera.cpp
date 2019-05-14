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

Camera::Camera() :	mPosition(glm::vec3(0.0f,0.0f,0.0f)), 
					mUp(0.0f,1.0f,0.0f), 
					mYaw(-90.0f), 
					mPitch(0), 
					mFront(glm::vec3(0.0f,0.0f, -1.0f))

{
}

Camera::~Camera()
{

}

Camera* Camera::create(glm::vec3 pos)
{
Camera *ret = new Camera();
	
	if(ret)
	{
		ret->mPosition = pos;
	}
	return ret;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::update()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	front.y = sin(glm::radians(mPitch));
	front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	mUp = glm::normalize(glm::cross(mRight, mFront));
}
