#include "Tilemap.h"
#include "engine/Renderer.h"
#include "engine/Globals.h"

Tile::Tile(Texture::TextureData spritesheet)
{
	m_TextureData = spritesheet;
	m_Destination = { 0,0,0,0 };
}

Tile::~Tile()
{

}

void Tile::Draw()
{
	SDL_RenderCopy(Renderer::GetRenderer(), m_TextureData.m_Texture, &m_TextureData.m_Source, &m_Destination);
}

//	TODO; @RyanWestwood - Make this read in from a file or assign the array manually
Tilemap::Tilemap()
{
	auto tilemap_dimensions = Globals::GetTileMapDimensions();
	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			MAP_DATA[y][x] = (1) + (4 * 32); // x = 0-31, y = 0-31
		}
	}
}

Tilemap::~Tilemap()
{
	if (m_TextureData.m_Texture) SDL_DestroyTexture(m_TextureData.m_Texture);
}

void Tilemap::Initialize(const char* filename, int src_tile_size, int dst_tile_size)
{
	auto texture = Texture::LoadTexture(filename);
	m_TextureData.m_Texture = texture.m_Texture;
	m_TextureData.m_Source = texture.m_Source;
	m_Destination = { 0,0,32,32 };

	auto spritesheet_column = m_TextureData.m_Source.w / src_tile_size;
	auto spritesheet_row = m_TextureData.m_Source.h / src_tile_size;
	auto tilemap_dimensions = Globals::GetTileMapDimensions();

#ifdef LOGGING
	m_Nodes = AI::PATH::CreateNodeMap(tilemap_dimensions.w, tilemap_dimensions.h);
#endif // LOGGING

	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			Tile tile = { m_TextureData };
			tile.m_Destination = { dst_tile_size * x, dst_tile_size * y, dst_tile_size, dst_tile_size };
			tile.m_TextureData.m_Source = { (MAP_DATA[y][x] % spritesheet_column) * src_tile_size, (MAP_DATA[y][x] / spritesheet_row) * src_tile_size, src_tile_size, src_tile_size };
			m_Tiles.push_back(tile);
		}
	}
#ifdef LOGGING
	m_DebugTextureData = Texture::LoadTexture("ui_foredrop.png");
	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			Tile tile = { m_DebugTextureData };
			tile.m_Destination = { dst_tile_size * x + 8, dst_tile_size * y + 8, dst_tile_size / 2, dst_tile_size / 2 };
			m_DebugTiles.push_back(tile);
		}
	}
	std::cout << "Loading tiles: " << spritesheet_row * spritesheet_column << "\n";
#endif // LOGGING
}

void Tilemap::Draw()
{
	for (auto& tile : m_Tiles) {
		tile.Draw();
	}
#ifdef LOGGING
	if (m_DebugActivate) {
		for (auto& tile : m_DebugTiles) {
			tile.Draw();
		}
	}
#endif // LOGGING
}

#ifdef LOGGING
#include "engine/Input.h"

void Tilemap::Input()
{
	if (Input::GetKeyUp(SDL_SCANCODE_F2)) {
		m_DebugActivate = !m_DebugActivate;
		Input::SetKeyUp(SDL_SCANCODE_F2, false);
	}
}
#endif // LOGGING
