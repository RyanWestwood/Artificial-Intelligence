#include "Nodemap.h"
#include <SDL.h>
#include "Globals.h"
#include "Renderer.h"

#ifdef LOGGING
#include "Input.h"
#endif // LOGGING


void NodeGrid::Initialize()
{
	auto tilemap_dimensions = Globals::GetTileMapDimensions();
	m_Map = AI::PATH::CreateNodeMap((int)tilemap_dimensions.w, (int)tilemap_dimensions.h);
	m_Nodes = m_Map->GetMap();

	auto tile_size = Globals::GetTileDimensions();
	int tile_width = tile_size.w;
	int tile_height = tile_size.h;

#ifdef LOGGING
	auto start_node = m_Nodes.at(40 + (1 * tilemap_dimensions.w));
	auto end_node = m_Nodes.at(4 + (25* tilemap_dimensions.w));
	auto solution_path = AI::PATH::A_Star(m_Nodes, start_node, end_node);

	m_DebugTextureData = Texture::LoadTexture("ui_foredrop.png");
	m_DebugTextureExploredData = Texture::LoadTexture("ui_backdrop.png");
	m_DebugNodes.reserve(tilemap_dimensions.w * tilemap_dimensions.w);

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

