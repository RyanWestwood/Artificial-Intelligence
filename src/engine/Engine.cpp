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
#endif

	text.Initalize("font.ttf", "HELLO WORLD!");
	music.Initialize("music.wav");
	sfx.Initialize("temp.wav");
	tilemap.Initialize("tilemap.png", {32,32}, {48,27}, 16, 32);
	player.Initialize();

#ifdef LOGGING
	std::cout << "\n";
#endif

	music.PlayMusic();
	sfx.PlaySound();
	m_IsPaused = false;

	return renderer && sound && font && input && globals; 
}

void Engine::UnInitialize()
{
	Font::UnInitializeFont();
	Sound::UninitalizeSound();
	Renderer::UninitalizeRenderer();
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
				SDL_ShowCursor(!m_IsPaused);
#ifdef LOGGING
				std::cout << "Resumed\n";
#endif
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
				SDL_ShowCursor(!m_IsPaused);
#ifdef LOGGING
				std::cout << "Paused\n";
#endif
			}
#ifdef LOGGING
			if (Input::GetKeyDown(SDL_SCANCODE_F1)) {
				std::cout << "Key Down: F1!\n";
			}
#endif
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
#endif
		}
	}
	player.Input();
}

void Engine::Update(double delta_time)
{
	player.Update(delta_time);
}

void Engine::UpdateAnimation(double* num)
{
#ifdef LOGGING
		std::cout << "AnimStep: " << *num << "\n";
#endif
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