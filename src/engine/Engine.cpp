#include "Engine.h"
#include "Input.h"
#include "Globals.h"

bool Engine::Initialize()
{
	bool globals = Globals::Initialize();
	bool renderer = Renderer::InitializeRenderer();
	bool texture = Texture::Initialize();
	bool sound = Sound::InitializeSound();
	bool font = Font::InitializeFont();
	bool input = Input::InitialzieInput();

#ifdef LOGGING
	std::cout << "\n";
	std::cout << "Renderer: " << Renderer::GetRenderer() << "\n\nLoading...\n";
#endif // LOGGING

	music.Initialize("music.wav");
	sfx.Initialize("temp.wav");
	tilemap.Initialize("tilemap.png", 16, 32);
	player.Initialize();

#ifdef LOGGING
	std::cout << "\n";
#endif // LOGGING

	music.PlayMusic();
	sfx.PlaySound();
	m_IsPaused = false;

	return renderer && sound && font && input && globals && texture; 
}

void Engine::UnInitialize()
{

}

bool Engine::IsRunning()
{
	SDL_PumpEvents();

	SDL_Event event;
	if (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
		return false;
	}

	return true;
}

bool Engine::IsPaused()
{
	return m_IsPaused;
}

void Engine::Resume()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_KEYDOWN) {
			if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
				m_IsPaused = !m_IsPaused;
				Input::SetKeyUp(SDL_SCANCODE_ESCAPE, true);
				Input::SetKeyDown(SDL_SCANCODE_ESCAPE, false);
				SDL_ShowCursor(m_IsPaused);
#ifdef LOGGING
				std::cout << "Resumed\n";
#endif // LOGGING
			}
		}
	}	
}

void Engine::Input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode < 512) {
				Input::SetKeyDown(e.key.keysym.scancode, true);
				Input::SetKeyUp(e.key.keysym.scancode, false);
			}
			if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
				m_IsPaused = !m_IsPaused;		
				SDL_ShowCursor(m_IsPaused);
#ifdef LOGGING
				std::cout << "Paused\n";
#endif // LOGGING
			}
#ifdef LOGGING
			if (Input::GetKeyDown(SDL_SCANCODE_F1)) {
				std::cout << "Key Down: F1!\n";
			}
#endif // LOGGING
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.scancode < 512) {
				Input::SetKeyDown(e.key.keysym.scancode, false);
				Input::SetKeyUp(e.key.keysym.scancode, true);
			}
#ifdef LOGGING
			if (Input::GetKeyUp(SDL_SCANCODE_F1)) {
				std::cout << "Key Up: F1!\n";
				Input::SetKeyUp(e.key.keysym.scancode, false);
			}
#endif // LOGGING
		}
	}
	player.Input();
	tilemap.Input();
}

void Engine::Update(const float& delta_time)
{
	player.Update(delta_time);
}

void Engine::UpdateAnimation(float* num)
{
#ifdef LOGGING
		std::cout << "AnimStep: " << *num << "\n";
#endif // LOGGING
		*num = 0.0;

		player.UpdateAnimation();
}

void Engine::Draw()
{
	SDL_RenderClear(Renderer::GetRenderer());

	tilemap.Draw();
	text.Draw();
	player.Draw();

	SDL_RenderPresent(Renderer::GetRenderer());
}