#include "Tilemap.h"
#include "Renderer.h"

Tile::Tile(Texture::TextureData spritesheet)
{
	m_Texture = spritesheet;
}

Tile::~Tile()
{

}

void Tile::Draw()
{
	SDL_RenderCopy(Renderer::GetRenderer(), m_Texture.m_Texture, &m_Texture.m_Source, &m_Destination);
}

//	TODO; @RyanWestwood - Make this read in from a file or assign the array manually
Tilemap::Tilemap()
{
	for (int y = 0; y < 27; y++)
	{
		for (int x = 0; x < 48; x++)
		{
			MAP_DATA[y][x] = (2) + (3 * 32); // x = 0-31, y = 0-31
		}
	}
}

Tilemap::~Tilemap()
{
	if (m_TextureData.m_Texture) SDL_DestroyTexture(m_TextureData.m_Texture);
}

void Tilemap::Initialize(const char* filename, SDL_Point spriteTiles, SDL_Point dimensons, int srcTileSize, int dstTileSize)
{
	auto texture = Texture::LoadTexture(filename);
	m_TextureData.m_Texture = texture.m_Texture;
	m_TextureData.m_Source = texture.m_Source;
	m_Destination = { 0,0,32,32 };

	for (int y = 0; y < dimensons.y; y++)
	{
		for (int x = 0; x < dimensons.x; x++)
		{
			Tile tile = { m_TextureData };
			tile.m_Destination = { dstTileSize * x, dstTileSize * y, dstTileSize, dstTileSize };
			tile.m_Texture.m_Source = { (MAP_DATA[y][x] % spriteTiles.x) * srcTileSize, (MAP_DATA[y][x] / spriteTiles.y) * srcTileSize, srcTileSize, srcTileSize };
			m_Tiles.push_back(tile);
		}
	}
#ifdef LOGGING
	std::cout << "Tiles created: " << dimensons.x * dimensons.y << "\n";
#endif
}

void Tilemap::Draw()
{
	for (auto& tile : m_Tiles) {
		tile.Draw();
	}
}
