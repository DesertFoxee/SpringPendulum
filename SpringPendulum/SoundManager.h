#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "ResourceManager.h"
#include "Singleton.h"
#include <SFML/Audio.hpp>
#include "Config.h"


class SoundManager : public ResourceManager<SoundManager ,sf::SoundBuffer > 
	, public Singleton <SoundManager>
{
	friend Singleton <SoundManager>;

private:
	
	sf::SoundBuffer* loadResource(const std::string& path);

	SoundManager() :ResourceManager(DataConfig::ConfigPathResource::sound_config) {};
public:
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
};



#endif // !SOUNDMANAGER_H



