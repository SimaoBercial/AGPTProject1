#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "ModelLoader.h"

int main(int argc, char** argv)
{

	float screenWidth = 800;
	float screenHeight = 600;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_Window* window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_CaptureMouse(SDL_TRUE);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		SDL_Quit();
		return -2;
	}
	Shader shaderProgram("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
	
	shaderProgram.use();
	
	ModelLoader loader;

	if (!loader.loadModel("resources/lost-empire/lost_empire.obj", shaderProgram)) {
		std::cerr << "Failed to load model" << std::endl;
		return -1;
	}

	stbi_set_flip_vertically_on_load(true);

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

	glm::mat4 view;
	view = camera.getViewMatrix();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -13.0f, 0.0f)); 
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(camera.getFov()), screenWidth / screenHeight, 0.1f, 100.0f);

	shaderProgram.setMat4("model", model);
	shaderProgram.setMat4("view", view);
	shaderProgram.setMat4("projection", projection);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	SDL_Event event;

	int start = SDL_GetTicks();
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrameTime = start; // Time of last frame

	glEnable(GL_DEPTH_TEST);
	bool isRunning = true;

	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (isRunning) // Render Loop
	{
		int now = SDL_GetTicks();
		float deltaTime = (now - lastFrameTime) / 1000.0f;
		lastFrameTime = now;


		while (SDL_PollEvent(&event) != 0) // Event Loop
		{
			if (event.type == SDL_QUIT) isRunning = false;

			if (event.type == SDL_MOUSEMOTION) {
				camera.processMouseInput(event.motion.xrel, event.motion.yrel);
			}
		}

		const Uint8* keyState = SDL_GetKeyboardState(nullptr);
		camera.processKeyboardInput(keyState, deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.use();

		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera.getFov()), screenWidth / screenHeight, 0.1f, 100.0f);

		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);

		loader.draw(shaderProgram);

		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
