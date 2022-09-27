#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

namespace Sound {
	class SoundError : public std::exception {
	public:
		const char* what() const throw(){ return "Sound Loading Error!\n"; }		
	};

	bool InitializeSound();
	void UninitalizeSound();

	Mix_Chunk* LoadSfx(const char* filename);
	Mix_Music* LoadMusic(const char* filename);
}

class SoundEffect {
public:
	SoundEffect();

	void Initialize(const char* filename);
	void PlaySound();

public:
	Mix_Chunk* m_Sound;
};

class Music {
public:
	Music();

	void Initialize(const char* filename);
	void PlayMusic();

public:
	Mix_Music* m_Music;
};