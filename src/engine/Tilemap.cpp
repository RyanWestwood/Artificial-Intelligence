#include "Tilemap.h"

Tile::Tile(Sprite spritesheet)
{
	m_Sprite = spritesheet;
}

Tile::~Tile()
{

}

void Tile::Draw()
{
	m_Sprite.Draw();
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

}

void Tilemap::Initialize(const char* filename, SDL_Point spriteTiles, SDL_Point dimensons, int srcTileSize, int dstTileSize)
{
	m_Spritesheet.Initialize(filename);
	for (int y = 0; y < dimensons.y; y++)
	{
		for (int x = 0; x < dimensons.x; x++)
		{
			Tile tile = { m_Spritesheet };
			tile.m_Sprite.m_Destination = { dstTileSize * x, dstTileSize * y, dstTileSize, dstTileSize };
			tile.m_Sprite.m_Source = { (MAP_DATA[y][x] % spriteTiles.x) * srcTileSize, (MAP_DATA[y][x] / spriteTiles.y) * srcTileSize, srcTileSize, srcTileSize };
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
