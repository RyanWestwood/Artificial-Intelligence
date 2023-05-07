#include "Tilemap.h"
#include "engine/Globals.h"
#include "engine/Renderer.h"
#include <algorithm>

Tile::Tile(SDL_FRect destination, SDL_Point position)
{
  m_Destination = destination;
  m_Position    = position;
}

//	TODO; @RyanWestwood - Make this read in from a file or assign the array manually
Tilemap::Tilemap()
{
  auto tilemap_dimensions = globals::GetTileMapDimensions();
  for(int y = 0; y < tilemap_dimensions.h; y++)
  {
    for(int x = 0; x < tilemap_dimensions.w; x++)
    {
      MAP_DATA[y][x] = (1) + (4 * 32); // tile location on "tilemap.png"
    }
  }
  m_Tiles.reserve(tilemap_dimensions.w * tilemap_dimensions.h);
  m_TextureData = texture::TextureData{nullptr, SDL_Rect{0}};
  m_Map         = nullptr;
}

Tilemap::~Tilemap()
{
  if(m_TextureData.m_Texture)
    SDL_DestroyTexture(m_TextureData.m_Texture);
  if(m_Map)
    SDL_DestroyTexture(m_Map);
}

void Tilemap::Initialize(const char* filename, int src_tile_size)
{
  auto texture            = texture::LoadTexture(filename);
  m_TextureData.m_Texture = texture.m_Texture;
  m_TextureData.m_Source  = texture.m_Source;

  auto spritesheet_column = m_TextureData.m_Source.w / src_tile_size;
  auto spritesheet_row    = m_TextureData.m_Source.h / src_tile_size;

  auto tilemap_dimensions = globals::GetTileMapDimensions();
  auto tile_size          = globals::GetTileDimensions();

  m_Map = SDL_CreateTexture(renderer::GetRenderer(),
                            SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET,
                            globals::GetScreenDimensions().x,
                            globals::GetScreenDimensions().y);

  SDL_SetRenderTarget(renderer::GetRenderer(), m_Map);
  for(int y = 0; y < tilemap_dimensions.h; y++)
  {
    for(int x = 0; x < tilemap_dimensions.w; x++)
    {
      SDL_FRect destination = {tile_size.w * x, tile_size.h * y, tile_size.w, tile_size.h};
      SDL_Point position    = {x, y};
      m_Tiles.emplace_back(Tile{destination, position});

      SDL_Rect source = {(MAP_DATA[y][x] % spritesheet_column) * src_tile_size,
                         (MAP_DATA[y][x] / spritesheet_row) * src_tile_size,
                         src_tile_size,
                         src_tile_size};
      SDL_RenderCopyF(renderer::GetRenderer(), texture.m_Texture, &source, &destination);
    }
  }
  SDL_SetRenderTarget(renderer::GetRenderer(), nullptr);

#ifdef LOGGING
  std::cout << "Loading tiles: " << spritesheet_row * spritesheet_column << "\n";
#endif // LOGGING
}

void Tilemap::Draw()
{
  SDL_Rect src = {0, 0, 1536, 864};
  SDL_RenderCopy(renderer::GetRenderer(),
                 m_Map,
                 &src,
                 &src);
}