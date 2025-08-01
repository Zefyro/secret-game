#pragma once

#include <raylib.h>

#include <string>

class TextureCache {
public:
	static [[nodiscard]] Texture2D load(std::string&& fpath);
	static void unload_all();

private:
	TextureCache();
};
