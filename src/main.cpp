#include <iostream>
#include <SDL.h>
#include "engine/Engine.h"
#include "engine/Renderer.h"
#include "engine/Collision.h"

#include "Dll.h"

int main(int argc, char* args[])
{
	{
		AI::HelloWorld();

#ifdef LOGGING
		std::cout << "\nLogging Enabled:\n\n";
#endif // LOGGING

		Engine g_App = Engine();
		if (!g_App.Initialize()) {
			std::cout << "Error could not init SDL!" << "\n";
		}

		unsigned int g_CurrentTime = SDL_GetPerformanceCounter();;
		unsigned int g_LastTime = 0;
		float g_LastAnimStep = 0.0;
		float g_UpdateAnimTimer = 1.f / 8;

		while (g_App.IsRunning()) {
			if (!g_App.IsPaused()) {
				g_LastTime = g_CurrentTime;
				g_CurrentTime = SDL_GetPerformanceCounter();
				float deltaTime = ((g_CurrentTime - g_LastTime) / (float)SDL_GetPerformanceFrequency());

				if (g_LastAnimStep > g_UpdateAnimTimer) {
					g_App.UpdateAnimation(&g_LastAnimStep);
				}
				else {
					g_LastAnimStep += deltaTime;
				}
				g_App.Input();
				g_App.Update(deltaTime);
				g_App.Draw();
			}
			else {
				g_App.Resume();
				g_CurrentTime = SDL_GetPerformanceCounter();
			}
		}
		g_App.UnInitialize();
	}

	Font::UnInitializeFont();
	Sound::UninitalizeSound();
	Renderer::UninitalizeRenderer();

#if LOGGING
	std::cout << "Application Shutdown!\n";
#endif // LOGGING

	return 0;
}