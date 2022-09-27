#include "Engine.h"

bool Engine::Initialize()
{
	bool renderer = Renderer::InitializeRenderer();
	bool sound = Sound::InitializeSound();
	bool font = Font::InitializeFont();

	text.Initalize("font.ttf", "HELLO WORLD!");
	sprite.Initialize("tilemap.png");
	music.Initialize("music.wav");
	sfx.Initialize("temp.wav");
	sprite.m_Destination = sprite.m_Source;
	sprite.m_Destination.y += 64;

	music.PlayMusic();
	sfx.PlaySound();

	return renderer && sound && font; 
}

void Engine::Unintialize()
{
	Font::UnInitializeFont();
	Sound::UninitalizeSound();
	Renderer::UninitalizeRenderer();
}

bool Engine::IsRunning()
{
	return true;
}

bool Engine::IsPaused()
{
	return false;
}

void Engine::Resume()
{

}

void Engine::Input()
{

}

void Engine::Update(double delta_time)
{

}

void Engine::Draw()
{
	SDL_RenderClear(Renderer::GetRenderer());

	text.Draw();
	sprite.Draw();

	SDL_RenderPresent(Renderer::GetRenderer());
}