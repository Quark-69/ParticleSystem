#include "App.hpp"
#include "../ParticleSim/ParticleSystem.hpp"


App::App(Window* window)
	: window_(window), keyboard_(&Keyboard::getInstance()), mouse_(&Mouse::getInstance()),
	  dt(0.0f), lastFrame(0.0f)
{
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}

	window_->setParams();
	Keyboard::setupKeyboard(window_->getWindow());
	Mouse::setupMouse(window_->getWindow());
}

void App::Run()
{
	Shader shader("assets/vert.glsl", "assets/frag.glsl");

	ParticleSystem pSystem(window_, mouse_);
	pSystem.AddParticles(100, ParticleType::Circle);

	while (!window_->shouldWindowClose())
	{
		updateDt();

		processInput();

		window_->update();

		shader.activate();

		pSystem.Update(dt);

		glm::mat4 projection = glm::ortho(0.0f, (float)window_->getSreenWidth(), (float)window_->getSreenHeight(), 0.0f, -1.0f, 1.0f);
		shader.setMat4("projection", projection);

		pSystem.Render(shader);

		window_->newFrame();
	}

	pSystem.cleanup();
}

void App::processInput() const
{
	if (keyboard_->KeyWentDown(GLFW_KEY_ESCAPE))
	{
		window_->setWindowShouldClose(true);
	}
}

void App::updateDt()
{
	double currentTime = glfwGetTime();
	dt = currentTime - lastFrame;
	lastFrame = currentTime;
}
