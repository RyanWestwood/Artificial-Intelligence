#include "Texture.h"
#include "Renderer.h"
#include <string.h>

namespace Texture {

	namespace {
		const std::string g_TextureDirectory = "C:/Users/Ryan/Documents/Git/Artificial-Intelligence/assets/textures/";
	}

	SDL_Texture* LoadTexture(const char* filename)
	{
#ifdef LOGGING
		std::cout << "Loading texture: " << filename << "\n";
#endif
		try {
			SDL_Surface* surface = IMG_Load((g_TextureDirectory + std::string(filename)).c_str());
			if (surface == nullptr) throw TextureError();
			SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), surface);
			if (texture == nullptr) throw TextureError();
			SDL_FreeSurface(surface);
			return texture;
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << ": " << "\t" << IMG_GetError();
			return nullptr;
		}
	}

	SDL_Rect LoadTextureRect(const char* filename)
	{
#ifdef LOGGING
		std::cout << "Loading texture rect: " << filename << "\n";
#endif
		try {
			SDL_Surface* surface = IMG_Load((g_TextureDirectory + std::string(filename)).c_str());
			SDL_Rect source = { 0,0,surface->w,surface->h };
			if (surface == nullptr) throw TextureError();
			SDL_FreeSurface(surface);
			return source;
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << ": " << "\t" << IMG_GetError();
			return { 0,0,0,0 };
		}
	}

	void Draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest)
	{
		SDL_RenderCopy(Renderer::GetRenderer(), texture, &src, &dest);
	}
}

Sprite::Sprite()
{
	m_Texture = nullptr;
	m_Source = { 0,0,0,0 };
	m_Destination = { 0,0,0,0 };
}

void Sprite::Initialize(const char* filename)
{
	m_Texture = Texture::LoadTexture(filename);
	m_Source = Texture::LoadTextureRect(filename);
	m_Destination = { 0,0,32,32 };
}

void Sprite::Draw()
{
	SDL_RenderCopy(Renderer::GetRenderer(), m_Texture, &m_Source, &m_Destination);
}