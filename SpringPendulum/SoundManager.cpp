#include "SoundManager.h"

sf::SoundBuffer* SoundManager::loadResource(const std::string& path)
{
	sf::SoundBuffer* sound = new sf::SoundBuffer();
	if (!sound->loadFromFile(path)) {
		delete sound;
		sound = nullptr;
		std::cout << "[ ! ] Failed : Load file failed : => path : " << path << std::endl;
	}
	return sound;
}