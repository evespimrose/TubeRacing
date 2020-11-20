#include "Camera.h"

void Camera::setpSpeed(float s)
{
	pSpeed = s;
}

void Camera::setRotate(float r)
{
	rotate = r;
}

void Camera::setPosition(glm::vec3 p)
{
	posx = p.x;
	posy = p.y;
	posz = p.z;
}

void Camera::setSpeed(float speed)
{
	float zoom = 0.0003f;
	if (speed > 0.0f && posz < 10.0f)
	{
		posz += speed * zoom;
		posy += speed * zoom * 0.5;
	}

	pSpeed = 0.0f;
}

glm::vec3 Camera::getPosition()
{
	return glm::vec3(posx, posy - 1.0f, posz - 3.0f);
}

void Camera::setAT()
{
	AT = glm::vec3(0, 0, 0.0f);
}

void Camera::Render(GLuint ShaderProgram)
{
	glm::mat4 Projection = glm::mat4(1.0f);
	Projection = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 1000.0f);
	unsigned int ProjectionLocation = glGetUniformLocation(ShaderProgram, "projectionTransform");;
	glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, &Projection[0][0]);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
	glm::vec3 cameraDirection = AT;
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	view = glm::translate(view, glm::vec3(0.0f, -1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(-rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, glm::vec3(-posx, -posy, -posz));


	unsigned int viewLocation = glGetUniformLocation(ShaderProgram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}
