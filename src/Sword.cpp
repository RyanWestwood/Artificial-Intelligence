#include "Sword.h"
#include <iostream>

void Sword::Initialize(const char* filename) {
#ifdef LOGGING
	std::cout << "Sword initialize\n";
#endif
	m_Sprite.Initialize("tilemap.png");
	m_Sprite.m_Source = { 336,16,16,32 };
	m_Sprite.m_Destination = { 128,128,24,48 };
}