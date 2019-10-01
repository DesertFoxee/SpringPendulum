#include "FontManager.h"

sf::Font* FontManager::loadResource(const std::string& path)
{
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(path)) {
		delete font;
		font = nullptr;
		std::cout << "[ ! ] Loading font failed ! => [" << path << "]" << std::endl;
	}
	return font;
}
