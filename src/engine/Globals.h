#pragma once
#include <string>

namespace Globals {

	enum class Direction {
		North = 0,
		South,
		East,
		West,
		None
	};

	bool Initialize();
	std::string GetAssetDirectory();

	struct Vector {
		float w, h;
	};
	Vector GetScreenDimensions();
	Vector GetTileDimensions();
	Vector GetTileMapDimensions();

} // namespace Globals