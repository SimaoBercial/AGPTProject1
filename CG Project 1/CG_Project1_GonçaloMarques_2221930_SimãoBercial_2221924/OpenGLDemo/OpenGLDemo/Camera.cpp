#include "Camera.h"


Camera::Camera(glm::vec3 cameraPosition, glm::vec3 up, float cameraYaw, float cameraPitch)
	: front(glm::vec3(0.f, 0.f, -1.f)), movementSpeed(2.5f), mouseSensitivity(0.1f), fov(45.f)
{
	position = cameraPosition;
	worldUp = up;
	yaw = cameraYaw;
	pitch = cameraPitch;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboardInput(const Uint8* keyState, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (keyState[SDL_SCANCODE_W]) move(FORWARD, velocity);
	if (keyState[SDL_SCANCODE_S]) move(BACKWARD, velocity);
	if (keyState[SDL_SCANCODE_A]) move(LEFT, velocity);
	if (keyState[SDL_SCANCODE_D]) move(RIGHT, velocity);
}

void Camera::processMouseInput(float xpos, float ypos) {
	if (firstMouse) {
		firstMouse = false;
	}

	float xoffset = xpos;
	float yoffset = -ypos; // Reversed since y-coordinates go from bottom to top

	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	updateCameraVectors();
}


void Camera::updateCameraVectors()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::move(CameraMovement direction, float velocity)
{
	glm::vec3 horizontalFront = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	if (direction == FORWARD) position += horizontalFront * velocity;
	if (direction == BACKWARD) position -= horizontalFront * velocity;
	if (direction == LEFT) position -= glm::normalize(glm::cross(horizontalFront, worldUp)) * velocity;
	if (direction == RIGHT) position += glm::normalize(glm::cross(horizontalFront, worldUp)) * velocity;

	position.y = 0.0f;
}