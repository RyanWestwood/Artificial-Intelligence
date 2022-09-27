#include "Engine.h"

bool Engine::Initialize()
{
	return Renderer::InitalizeSDL();
}

void Engine::Unintialize()
{
	Renderer::UninitalizeSDL();
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

}