#define SDL_MAIN_HANDLED
#include <engine/Globals.h>
#include <engine/Renderer.h>
#include <engine/Sound.h>

int main()
{
  bool globals  = globals::InitializeGlobals();
  bool renderer = renderer::InitializeRenderer();
  bool sound    = sound::InitializeSound();
  if(!globals || !renderer || !sound) return 1;

  SoundEffect sfx;
  sfx.Initialize("temp.wav");
  sfx.PlaySound();

  Music music;
  music.Initialize("music.wav");
  music.PlayMusic();
  return 0;
}