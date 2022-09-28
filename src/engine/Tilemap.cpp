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

Tilemap::Tilemap()
{
	for (int y = 0; y < 27; y++)
	{
		for (int x = 0; x < 48; x++)
		{
			MAP_DATA[y][x] = 33;
		}
	}
}

Tilemap::~Tilemap()
{

}

void Tilemap::Initialize()
{
	m_Spritesheet.Initialize("tilemap.png");
	for (int y = 0; y < 27; y++)
	{
		for (int x = 0; x < 48; x++)
		{
			Tile tile = { m_Spritesheet };
			tile.m_Sprite.m_Destination = { 32 * x, 32 * y, 32, 32 };
			tile.m_Sprite.m_Source = { 16, 64, 16, 16 };
			m_Tiles.push_back(tile);
		}
	}
#ifdef LOGGING
	std::cout << "Tiles created: " << 27*48 << "\n";
#endif
}

void Tilemap::Draw()
{
	for (auto& tile : m_Tiles) {
		tile.Draw();
	}
}
