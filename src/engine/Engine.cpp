#include "Engine.h"
#include "Collision.h"
#include "Globals.h"
#include "Input.h"
#include "Pathing.h"

bool Engine::Initialize()
{
	bool globals = Globals::Initialize();
	bool renderer = Renderer::InitializeRenderer();
	bool texture = Texture::Initialize();
	bool sound = Sound::InitializeSound();
	bool font = Font::InitializeFont();
	bool input = Input::InitialzieInput();
	bool pathing = PATHING::Initialize();
	Font::InitializeDefaultFont();

#ifdef LOGGING
	std::cout << "\n";
	std::cout << "Renderer: " << Renderer::GetRenderer() << "\n";
	std::cout << "Default font: " << Font::GetDefaultFont().m_Font << "\n\nLoading...\n";
#endif // LOGGING

	m_Music.Initialize("music.wav");
	m_Text.Initalize("LAST DREAM XIV");
	m_SoundEffect.Initialize("temp.wav");
	m_Tilemap.Initialize("tilemap.png", 16);
	m_Player.Initialize();
	m_Enemy.Initialize();

#ifdef LOGGING
	std::cout << "\n";
#endif // LOGGING

	m_Music.PlayMusic();
	m_SoundEffect.PlaySound();
	m_IsPaused = false;

	return renderer && sound && font && input && globals && texture && pathing; 
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
	m_Player.Resume();
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
	m_Player.Input();
#ifdef LOGGING
	PATHING::Input();
	m_Enemy.Input();
#endif // LOGGING
	Input::SetKeyUp(SDL_SCANCODE_F3, false);
}

void Engine::Update(const float& delta_time)
{
	m_Player.Update(delta_time);
	m_Enemy.Update(delta_time);
}

void Engine::UpdateAnimation(float* num)
{
#ifdef LOGGING
	//std::cout << "AnimStep: " << *num << "\n";
#endif // LOGGING
	*num = 0.0;
	m_Player.UpdateAnimation();
	m_Enemy.UpdateAnimation();
}

void Engine::UpdateAi(float* num)
{
#ifdef LOGGING
	//std::cout << "Update AI!\n";
#endif // LOGGING

	*num = 0.0;
	PATHING::Reset();
	//for (auto tile : PATHING::GetMap()) {
	//	if (COLLISION::BoxCollision(m_Player.GetCollider(), tile.GetCollider())) {
	//		PATHING::SetObstacle(tile.m_Position.x, tile.m_Position.y, true);
	//	}
	//	if (COLLISION::BoxCollision(m_Enemy.GetCollider(), tile.GetCollider())) {
	//		PATHING::SetObstacle(tile.m_Position.x, tile.m_Position.y, true);
	//	}
	//}
	m_Enemy.UpdateAi(m_Player.GetNodePosition());
	PATHING::UpdateAi();
}

void Engine::Draw()
{
	SDL_RenderClear(Renderer::GetRenderer());

	m_Tilemap.Draw();
	m_Text.Draw();
	m_Player.Draw();
	m_Enemy.Draw();

#ifdef LOGGING
	PATHING::Draw();
#endif // LOGGING

	SDL_RenderPresent(Renderer::GetRenderer());
}