
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Config.h"
#include "Singleton.h"



class TextureManager : public ResourceManager<TextureManager , sf::Texture> , 
	public Singleton<TextureManager> 
{

	friend Singleton<TextureManager>;
private :
	TextureManager() :ResourceManager(DataConfig::ConfigPathResource::image_config) {};
	sf::Texture* loadResource(const std::string& path);

public :
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
};



#endif // !TEXTUREMANAGER_H


