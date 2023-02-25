#include "Utils.h"

namespace utils
{
  namespace
  {
    Engine* g_Engine = nullptr;
  }

  bool InitializeUtils(Engine* engine)
  {
    g_Engine = engine;
    return g_Engine;
  }

  Player& GetPlayer()
  {
    return g_Engine->GetPlayer();
  }

} // namespace utils