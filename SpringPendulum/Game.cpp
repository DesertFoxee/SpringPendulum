#include "Game.h"



Game::Game(unsigned int width, unsigned int height, const std::string title) {
	this->width = width;
	this->title = title;
	this->height = height;
}


Game::~Game() {
}

void Game::init() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	this->window.create(sf::VideoMode(width, height), title ,sf::Style::Default , settings);
	spring_pendulum.init();
	bar1.init(Vector2D(100, 100), "Game", 0.f , 100.f);
}

void Game::handleKeyboard(const sf::Keyboard::Key key, bool state) {
	switch(key) {
		case sf::Keyboard::W:
			Keyboard::getIntance().setStateKeyboard(KEY_B::UP, state);
			break;
		case sf::Keyboard::S:
			Keyboard::getIntance().getIntance().setStateKeyboard(KEY_B::DOWN, state);
			break;
		case sf::Keyboard::A:
			Keyboard::getIntance().setStateKeyboard(KEY_B::LEFT, state);
			break;
		case sf::Keyboard::D:
			Keyboard::getIntance().setStateKeyboard(KEY_B::RIGHT, state);
			break;
		case sf::Keyboard::LControl:
		case sf::Keyboard::RControl:
			Keyboard::getIntance().setStateKeyboard(KEY_B::CONTROL, state);
			break;
		case sf::Keyboard::LShift:
		case sf::Keyboard::RShift:
			Keyboard::getIntance().setStateKeyboard(KEY_B::SHIFT, state);
			break;
		default:
			break;
	}
}

void Game::handleMouseClick(const sf::Mouse::Button btn, bool state) {
	switch(btn) {
		case sf::Mouse::Left:
			Mouse::getIntance().setStateMouse(MOUSE::MOUSE_B::LEFT, state);
			break;
		case sf::Mouse::Right:
			Mouse::getIntance().setStateMouse(MOUSE::MOUSE_B::RIGHT, state);
			break;
		case sf::Mouse::Middle:
			Mouse::getIntance().setStateMouse(MOUSE::MOUSE_B::MIDDLE, state);
			break;
		default:
			break;
	}
}

void Game::handleMouseScrolled(const sf::Mouse::Wheel wheel , int deltascr) {
	switch(wheel) {
		case sf::Mouse::VerticalWheel:
			// do something
			break;
		case sf::Mouse::HorizontalWheel:
			// do something
			break;
		default:
			break;
	}
	Mouse::getIntance().Zoom(deltascr);
}



void Game::process() {
	sf::Event event;

	Mouse::getIntance().resetClick();
	Mouse::getIntance().resetWheel();
	Keyboard::getIntance().resetPress();


	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				Keyboard::getIntance().setPress(true);
				this->handleKeyboard(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				this->handleKeyboard(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				Mouse::getIntance().setClick(true);
				this->handleMouseClick(event.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				this->handleMouseClick(event.mouseButton.button, false);
				break;
			case sf::Event::MouseWheelScrolled:
				Mouse::getIntance().setWheel(true);
				this->handleMouseScrolled(event.mouseWheelScroll.wheel ,event.mouseWheel.delta);
				break;
			default:
				break;
		}
	}

	spring_pendulum.process(window);
	bar1.process(window);
}

void Game::update()
{
	spring_pendulum.update();
	bar1.update();
}

void Game::render() {
	this->window.clear();
	spring_pendulum.render(window);
	bar1.render(window);
	this->window.display();
}

void Game::run() {
	this->init();

	while(this->window.isOpen()) {
		
		this->process();
		this->update();
		this->render();
	}	
}
