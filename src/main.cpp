#include <iostream>
#include <SDL.h>
#include "engine/Engine.h"
#include "engine/Renderer.h"

#include "Dll.h"

int main(int argc, char* args[])
{
	AI::HelloWorld();

#ifdef LOGGING
	std::cout << "\nLogging Enabled:\n\n";
#endif

	Engine g_App = Engine();
	if (!g_App.Initialize()) {
		std::cout << "Error could not init SDL!" << "\n";
	}

	unsigned int g_CurrentTime = SDL_GetPerformanceCounter();;
	unsigned int g_LastTime = 0;
	double g_LastAnimStep = 0.0;

	while (g_App.IsRunning()) {
		if (!g_App.IsPaused()) {
			g_LastTime = g_CurrentTime;
			g_CurrentTime = SDL_GetPerformanceCounter();
			double deltaTime = ((g_CurrentTime - g_LastTime) / (double)SDL_GetPerformanceFrequency());
			
			g_LastAnimStep > 0.125 ? g_App.UpdateAnimation(&g_LastAnimStep) : g_LastAnimStep += deltaTime;

			g_App.Input();
			g_App.Update(deltaTime);
			g_App.Draw();
		}
		else {
			g_App.Resume();
		}
	}
	g_App.UnInitialize();

	return 0;
}