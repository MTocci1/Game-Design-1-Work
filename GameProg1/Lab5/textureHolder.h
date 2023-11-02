#ifndef H_TEXTUREHOLDER
#define H_TEXTUREHOLDER

#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureHolder {
public:
	static sf::Texture& GetTexture(std::string const& filename);

private:
	TextureHolder();
	TextureHolder(TextureHolder const&) = delete;
	TextureHolder& operator=(TextureHolder const&) = delete;

	std::map<std::string, sf::Texture> m_Textures;

	static TextureHolder* m_s_Instance;
};

#endif H_TEXTUREHOLDER