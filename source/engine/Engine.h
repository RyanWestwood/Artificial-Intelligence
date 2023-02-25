#pragma once
#include "../Ad.h"
#include "../Boss.h"
#include "../Player.h"
#include "../Tilemap.h"
#include "Renderer.h"
#include "Sound.h"
#include "Texture.h"

class Engine
{
public:
  bool Initialize();
  void UnInitialize();

  bool IsRunning();
  bool IsPaused();
  void Resume();

  void Input();
  void Draw();
  void Update(const float&);
  void UpdateAnimation(float*);
  void UpdateAi(float*);

public: // Utils
  Player& GetPlayer();

public:
  bool        m_IsPaused;
  Music       m_Music;
  SoundEffect m_SoundEffect;
  Tilemap     m_Tilemap;
  Player      m_Player;
  Ad          m_Enemy;
  Boss        m_Boss;
};