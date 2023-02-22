#define SDL_MAIN_HANDLED
#include <ai/math/Vector2.h>
#include <engine/Globals.h>
#include <engine/Pathing.h>
#include <engine/Renderer.h>
#include <engine/Texture.h>

int main()
{
  bool globals  = globals::InitializeGlobals();
  bool renderer = renderer::InitializeRenderer();
  bool texture  = texture::InitializeTexture();
  bool pathing  = pathing::InitializePathing();
  if(!globals || !renderer || !texture || !pathing) return 1;

  Vector2 start_node{0, 0};
  Vector2 end_node{10, 10};

  std::vector<Vector2> path = pathing::CreatePath(start_node, end_node, pathing::Algo::A_Star);
  if(!path.size()) return 1;
  path.clear();

  path = pathing::CreatePath(start_node, end_node, pathing::Algo::BFS);
  if(!path.size()) return 1;
  path.clear();

  path = pathing::CreatePath(start_node, end_node, pathing::Algo::DFS);
  if(!path.size()) return 1;
  path.clear();

  path = pathing::CreatePath(start_node, end_node, pathing::Algo::GBFS);
  if(!path.size()) return 1;
  path.clear();

  return 0;
}