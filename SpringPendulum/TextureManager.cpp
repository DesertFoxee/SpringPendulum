#include "TextureManager.h"

sf::Texture * TextureManager::loadResource(const std::string& path) {
	sf::Texture* texture = new sf::Texture();
	if(!texture->loadFromFile(path)) {
		delete texture;
		texture = nullptr;
		std::cout << "[x] Loading image failed ![" << path << "]" << std::endl;
	}
	return texture;
}
