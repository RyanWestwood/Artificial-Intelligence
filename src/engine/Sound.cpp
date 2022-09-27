#include "Sound.h"

namespace Sound {

	namespace {
		const std::string g_SoundDirectory = "C:/Users/Ryan/Documents/Git/Artificial-Intelligence/assets/sfx/";
		const std::string g_MusicDirectory = "C:/Users/Ryan/Documents/Git/Artificial-Intelligence/assets/music/";
	}

	bool InitalizeSound()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cout << "SDL_Mix could not init! SDL_Mix error: " << Mix_GetError() << "\n";
			return false;
		}
		return true;
	}

	void UninitalizeSound()
	{
		Mix_Quit();
	}

	Mix_Chunk* LoadSfx(const char* filename)
	{
#ifdef LOGGING
		std::cout << "Loading sound: " << filename << "\n";
#endif
		try {
			Mix_Chunk* result = Mix_LoadWAV((g_SoundDirectory + std::string(filename)).c_str());
			if (result == nullptr) throw SoundError();
			return result;
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << ": " << "\t" << Mix_GetError();
			return nullptr;
		}
	}

	Mix_Music* LoadMusic(const char* filename) {
#ifdef LOGGING
		std::cout << "Loading music: " << filename << "\n";
#endif
		try {
			Mix_Music* result = Mix_LoadMUS((g_MusicDirectory + std::string(filename)).c_str());
			if (result == nullptr) throw SoundError();
			return result;
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << std::endl;
			std::cout << e.what() << ": " << "\t" << Mix_GetError();
			return nullptr;
		}
	}
}

SoundEffect::SoundEffect()
{
	m_Sound = nullptr;
}

void SoundEffect::Initialize(const char* filename)
{
	m_Sound = Sound::LoadSfx(filename);
}

void SoundEffect::PlaySound()
{
	Mix_PlayChannel(-1, m_Sound, 0);
}

Music::Music()
{
	m_Music = nullptr;
}

void Music::Initialize(const char* filename)
{
	m_Music = Sound::LoadMusic(filename);
}

void Music::PlayMusic()
{
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(m_Music, -1);
	}
}