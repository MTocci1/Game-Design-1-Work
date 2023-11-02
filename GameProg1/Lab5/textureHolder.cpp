#include "textureHolder.h"
#include <cassert>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;


TextureHolder::TextureHolder() 
{
	assert(m_s_Instance == nullptr); // This should never happen
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) 
{
	static TextureHolder holder; // persists between invocations of this method

	auto& m = holder.m_Textures;

	auto keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

