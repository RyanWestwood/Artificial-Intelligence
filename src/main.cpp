#include <iostream>
#include <SDL.h>
#include "engine/Engine.h"
#include "engine/Renderer.h"

int main(int argc, char* args[])
{
#ifdef LOGGING
	std::cout << "Logging Enabled:\n";
#endif

	Engine g_App = Engine();
	if (!g_App.Initialize()) {
		std::cout << "Error could not init SDL!" << "\n";
	}

#ifdef LOGGING
	std::cout << "Renderer: " << Renderer::GetRenderer() << "\n";
#endif

	unsigned int g_CurrentTime = SDL_GetPerformanceCounter();;
	unsigned int g_LastTime = 0;

	while (g_App.IsRunning()) {
		if (!g_App.IsPaused()) {
			g_LastTime = g_CurrentTime;
			g_CurrentTime = SDL_GetPerformanceCounter();
			double deltaTime = ((g_CurrentTime - g_LastTime) / (double)SDL_GetPerformanceFrequency());

			g_App.Input();
			g_App.Update(deltaTime);
			g_App.Draw();
		}
		else {
			g_App.Resume();
		}
	}
	g_App.Unintialize();

	return 0;
}