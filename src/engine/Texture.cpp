#include "Texture.h"
#include <string.h>
#include "Renderer.h"
#include "Globals.h"

namespace Texture {

	namespace {
		std::string g_TextureDirectory = "Not yet initialized!\n";
	}

	bool Initialize()
	{
		g_TextureDirectory = Globals::GetAssetDirectory();
		g_TextureDirectory += "textures/";
		return true;
	}

	TextureData LoadTexture(const char* filename)
	{
#ifdef LOGGING
		std::cout << "Loading texture: " << filename << "\n";
#endif // LOGGING
		try {
			SDL_Surface* surface = IMG_Load((g_TextureDirectory + std::string(filename)).c_str());
			if (surface == nullptr) throw TextureError();
			SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), surface);
			if (texture == nullptr) throw TextureError();
			SDL_Rect source = { 0,0,surface->w,surface->h };
			SDL_FreeSurface(surface);
			return { texture, source };
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << "\t" << IMG_GetError() << "\n";
			return {};
		}
	}

	void Draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest)
	{
		SDL_RenderCopy(Renderer::GetRenderer(), texture, &src, &dest);
	}
} // namespace Texture

Sprite::Sprite()
{
	m_Texture = nullptr;
	m_Source = { 0,0,0,0 };
	m_Destination = { 0,0,0,0 };
}

Sprite::~Sprite()
{
	if(m_Texture) SDL_DestroyTexture(m_Texture);
}

void Sprite::Initialize(const char* filename)
{
	auto texture = Texture::LoadTexture(filename);
	m_Texture = texture.m_Texture;
	m_Source = texture.m_Source;
	m_Destination = { 0,0,32,32 };
}

void Sprite::Draw(const SDL_RendererFlip& flip, const float& angle, const SDL_Point& point)
{
	SDL_RenderCopyEx(Renderer::GetRenderer(), m_Texture, &m_Source, &m_Destination, angle, &point, flip);
}