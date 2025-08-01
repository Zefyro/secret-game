#include "texture_cacher.hpp"

#include <algorithm>
#include <filesystem>
#include <unordered_map>

static std::unordered_map<std::string, Texture2D> s_Textures = {};

Texture2D TextureCache::load(std::string&& fpath)
{
	// Happy path
	if (s_Textures.find(fpath) != std::end(s_Textures)) {
		return s_Textures[fpath];
	}

	if (!std::filesystem::is_regular_file(fpath)) {
		throw std::runtime_error("A file at '" + fpath + "' doesn't exist!");
	}
	Texture2D texture = LoadTexture(fpath.c_str());
	return s_Textures[fpath] = texture;
}

void TextureCache::unload_all()
{
	for (auto [fpath, texture] : s_Textures) {
		UnloadTexture(texture);
	}
	s_Textures.clear();
}
