#pragma once
#include <string>

namespace Globals {

	bool Initialize();
	std::string GetAssetDirectory();

	struct Vector {
		float w, h;
	};
	Vector GetScreenDimensions();
	Vector GetTileDimensions();
} // namespace Globals