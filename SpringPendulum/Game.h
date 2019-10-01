#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MouseManager.h"
#include "KeyboardManager.h"
#include "SpringPendulum.h"
#include "Bar.h"

using namespace MOUSE;
using namespace KEYBOARD;

class Game {
	public:
		Game(unsigned int width, unsigned int height,const std::string title);
		~Game();
		void run();

	private:
		void init();
		void handleKeyboard(const sf::Keyboard::Key key, bool state);
		void handleMouseClick(const sf::Mouse::Button btn, bool state);
		void handleMouseScrolled(const sf::Mouse::Wheel wheel , int deltascr);
		void update();
		void process();
		void render();
	private:
		
		sf::RenderWindow window ;
		std::string title;
		unsigned int width;
		unsigned int height;

		// object ;
		SpringPendulum spring_pendulum;
		Bar bar1;

};


#endif // !GAME_H



