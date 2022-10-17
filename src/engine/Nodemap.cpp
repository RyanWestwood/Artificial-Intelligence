#include "Nodemap.h"
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
	SDL_DestroyTexture(m_DebugObstacle.m_Texture);
#endif // LOGGING
}

void NodeGrid::Initialize()
{
	auto tilemap_dimensions = Globals::GetTileMapDimensions();
	m_NodePtrs = AI::PATH::CreateNodeMap((int)tilemap_dimensions.w, (int)tilemap_dimensions.h)->GetMap();
	m_Nodes.reserve(tilemap_dimensions.w * tilemap_dimensions.h);
	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{		
			m_Nodes.emplace_back(std::make_shared<Node>());
		}
	}
#ifdef LOGGING
	auto tile_size = Globals::GetTileDimensions();
	int tile_width = tile_size.w;
	int tile_height = tile_size.h;

	m_DebugTextureData = Texture::LoadDebugTexture({ 100,100,100,255 }, { 32,32 });
	m_DebugTextureExploredData = Texture::LoadDebugTexture({ 255,255,255,255 }, { 32,32 });
	m_DebugTextureStartData = Texture::LoadDebugTexture({ 0,255,0,255 }, { 32,32 });
	m_DebugTextureEndData = Texture::LoadDebugTexture({ 0,0,255,255 }, { 32,32 });
	m_DebugObstacle = Texture::LoadDebugTexture({ 255,0,0,255 }, { 32,32 });

	DebugPaths(tilemap_dimensions, tile_width, tile_height);
#endif // LOGGING
}

void NodeGrid::Update()
{
#ifdef LOGGING
	auto tilemap_dimensions = Globals::GetTileMapDimensions();
	auto tile_size = Globals::GetTileDimensions();
	DebugPaths(tilemap_dimensions, tile_size.w, tile_size.h);
#endif // LOGGING
}

void NodeGrid::Reset()
{
	auto tilemap_dimensions = Globals::GetTileMapDimensions();
	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			m_NodePtrs.at(x + (y * tilemap_dimensions.w))->SetObstacle(false);
		}
	}
}

void NodeGrid::DebugPaths(Globals::Vector& tilemap_dimensions, int tile_width, int tile_height)
{
#ifdef LOGGING
	SDL_Point start = { 40,1 };
	SDL_Point end = { 4,25 };

	SDL_Point start1 = { 2,1 };
	SDL_Point end1 = { 40,24 };

	auto start_node = m_NodePtrs.at(start.x + (start.y * tilemap_dimensions.w));
	auto end_node = m_NodePtrs.at(end.x + (end.y * tilemap_dimensions.w));
	CLOCK::StartTimer();
	auto solution_path = AI::PATH::BFS(m_NodePtrs, start_node, end_node);
	CLOCK::StopTimer("BFS");

	auto start_node1 = m_NodePtrs.at(start1.x + (start1.y * tilemap_dimensions.w));
	auto end_node1 = m_NodePtrs.at(end1.x + (end1.y * tilemap_dimensions.w));
	CLOCK::StartTimer();
	auto solution_path2 = AI::PATH::A_Star(m_NodePtrs, start_node1, end_node1);
	CLOCK::StopTimer("A_Star");

	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			m_Nodes[x + (y * tilemap_dimensions.w)]->m_TextureData = m_NodePtrs.at(x + (y * tilemap_dimensions.w))->IsObstacle() ? m_DebugObstacle : m_DebugTextureData;
			m_Nodes[x + (y * tilemap_dimensions.w)]->m_Position = { float(x),float(y) };
			m_Nodes[x + (y * tilemap_dimensions.w)]->m_Collider = { x * 32 , y * 32,32,32 };
			m_Nodes[x + (y * tilemap_dimensions.w)]->m_Destination = { tile_width * x + 8, tile_height * y + 8, tile_width / 2, tile_height / 2 };
		}
	}
	for (auto& node : solution_path) {
		m_Nodes.at(node.x + (node.y * tilemap_dimensions.w))->m_TextureData = m_DebugTextureExploredData;
	}
	for (auto& node : solution_path2) {
		m_Nodes.at(node.x + (node.y * tilemap_dimensions.w))->m_TextureData = m_DebugTextureExploredData;
	}
	m_Nodes.at(start.x + (start.y * tilemap_dimensions.w))->m_TextureData.m_Texture = m_DebugTextureStartData.m_Texture;
	m_Nodes.at(end.x + (end.y * tilemap_dimensions.w))->m_TextureData.m_Texture = m_DebugTextureEndData.m_Texture;
	m_Nodes.at(start1.x + (start1.y * tilemap_dimensions.w))->m_TextureData.m_Texture = m_DebugTextureStartData.m_Texture;
	m_Nodes.at(end1.x + (end1.y * tilemap_dimensions.w))->m_TextureData.m_Texture = m_DebugTextureEndData.m_Texture;
#endif // LOGGING
}

void NodeGrid::SetObstacle(int x, int y, bool value)
{
	auto tilemap_dimensions = Globals::GetTileMapDimensions();
	m_NodePtrs.at(x + (y * tilemap_dimensions.w))->SetObstacle(value);
}

Node::Node()
{
	Entity::Entity();
}

#ifdef LOGGING
void NodeGrid::Draw() 
{
	if (m_DebugActivate) {
		for (auto& node : m_Nodes) {
			node->Draw();
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

void Node::Draw()
{
	SDL_RenderCopy(Renderer::GetRenderer(), m_TextureData.m_Texture, &m_TextureData.m_Source, &m_Destination);
}
#endif // LOGGING

