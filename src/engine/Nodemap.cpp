#include "Nodemap.h"
#include <SDL.h>
#include "Globals.h"
#include "Renderer.h"
#include "../Clock.h"

#ifdef LOGGING
#include "Input.h"
#endif // LOGGING

NodeGrid::~NodeGrid()
{
#ifdef LOGGING
	SDL_DestroyTexture(m_DebugTextureData.m_Texture);
	SDL_DestroyTexture(m_DebugTextureExploredData.m_Texture);
	SDL_DestroyTexture(m_DebugTextureStartData.m_Texture);
	SDL_DestroyTexture(m_DebugTextureEndData.m_Texture);
#endif // LOGGING
}

void NodeGrid::Initialize()
{
	auto tilemap_dimensions = Globals::GetTileMapDimensions();
	m_Map = AI::PATH::CreateNodeMap((int)tilemap_dimensions.w, (int)tilemap_dimensions.h);
	m_Nodes = m_Map->GetMap();

	auto tile_size = Globals::GetTileDimensions();
	int tile_width = tile_size.w;
	int tile_height = tile_size.h;

#ifdef LOGGING
	SDL_Point start = { 40,1 };
	SDL_Point end = { 4,25 };
	
	SDL_Point start1 = { 2,1 };
	SDL_Point end2 = { 40,24 };

	auto start_node = m_Nodes.at(start.x + (start.y * tilemap_dimensions.w));
	auto end_node = m_Nodes.at(end.x + (end.y * tilemap_dimensions.w));
	CLOCK::StartTimer();
	auto solution_path = AI::PATH::BFS(m_Nodes, start_node, end_node);
	CLOCK::StopTimer("A_Star");

	auto start_node1 = m_Nodes.at(start1.x + (start1.y * tilemap_dimensions.w));
	auto end_node1 = m_Nodes.at(end2.x + (end2.y * tilemap_dimensions.w));
	CLOCK::StartTimer();
	auto solution_path2 = AI::PATH::A_Star(m_Nodes, start_node1, end_node1);
	CLOCK::StopTimer("A_Star");
	
	m_DebugNodes.reserve(tilemap_dimensions.w * tilemap_dimensions.w);
	m_DebugTextureData = Texture::LoadDebugTexture({ 100,100,100,255 }, { 32,32 });
	m_DebugTextureExploredData = Texture::LoadDebugTexture({ 0,0,255,255 }, { 32,32 });
	m_DebugTextureStartData = Texture::LoadDebugTexture({ 0,255,0,255 }, { 32,32 });
	m_DebugTextureEndData = Texture::LoadDebugTexture({ 255,0,0,255 }, { 32,32 });

	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			DebugNode node;
			node.m_TextureData = m_DebugTextureData;
			node.m_Position = { float(x),float(y) };
			node.m_Destination = { tile_width * x + 8, tile_height * y + 8, tile_width / 2, tile_height / 2 };
			m_DebugNodes.push_back(node);
		}
	}
	for (auto& node : solution_path) {
		auto position = node->GetPosition();
		auto& temp_node = m_DebugNodes.at(position.x + (position.y * tilemap_dimensions.w));
		temp_node.m_TextureData = m_DebugTextureExploredData;
	}
	for (auto& node : solution_path2) {
		auto position = node->GetPosition();
		auto& temp_node = m_DebugNodes.at(position.x + (position.y * tilemap_dimensions.w));
		temp_node.m_TextureData = m_DebugTextureExploredData;
	}
	m_DebugNodes.at(start.x + (start.y * tilemap_dimensions.w)).m_TextureData.m_Texture = m_DebugTextureStartData.m_Texture;
	m_DebugNodes.at(end.x + (end.y * tilemap_dimensions.w)).m_TextureData.m_Texture = m_DebugTextureEndData.m_Texture;
#endif // LOGGING
}

#ifdef LOGGING
void NodeGrid::Draw() 
{
	if (m_DebugActivate) {
		for (auto& node : m_DebugNodes) {
			node.Draw();
		}
	}
}

void NodeGrid::Input()
{
	if (Input::GetKeyUp(SDL_SCANCODE_F2)) {
		m_DebugActivate = !m_DebugActivate;
		Input::SetKeyUp(SDL_SCANCODE_F2, false);
	}
}

void DebugNode::Draw()
{
	SDL_RenderCopy(Renderer::GetRenderer(), m_TextureData.m_Texture, &m_TextureData.m_Source, &m_Destination);
}
#endif // LOGGING

