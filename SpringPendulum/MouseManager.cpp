#include "MouseManager.h"

namespace MOUSE {

	sf::Vector2i  Mouse::pos = sf::Vector2i(0, 0);
	int Mouse::mouse_zoom = MIN_ZOOM;

	Mouse::Mouse()
	{
		for (auto i = 0; i < MOUSE::COUNT_MOUSE_B; i++) {
			mouse.push_back(false);
		}
		is_wheel = false;
		is_click = false;
	}

	Mouse::~Mouse()
	{
	}

	void Mouse::setStateMouse(MOUSE::MOUSE_B mousekey, bool state)
	{
		this->mouse[static_cast<int>(mousekey)] = state;
	}

	bool Mouse::getStateMouse(MOUSE::MOUSE_B mousekey)
	{
		return this->mouse[static_cast<int>(mousekey)];
	}



	void Mouse::resetMouseReal()
	{
		for (auto i = 0; i < MOUSE::COUNT_MOUSE_B; i++) {
			this->mouse[i] = false;
		}
	}

	sf::Vector2i Mouse::getMouseScreen()
	{
		Mouse::pos = sf::Mouse::getPosition();
		return pos;
	}

	sf::Vector2i Mouse::getMouseWindow(const sf::Window& window)
	{
		Mouse::pos = sf::Mouse::getPosition(window);
		return Mouse::pos;
	}

	void Mouse::setMouseScreen(const sf::Vector2i& pos)
	{
		sf::Mouse::setPosition(pos);
	}

	void Mouse::setMouseWindow(const sf::Window& window, const sf::Vector2i& pos)
	{
		sf::Mouse::setPosition(pos, window);
	}

	void Mouse::show()
	{
		std::cout << "Mouse map : ";
		for (auto i = 0; i < MOUSE::COUNT_MOUSE_B; i++) {
			std::cout << mouse[i];
		}
		std::cout << std::endl;
	}

	void Mouse::showMousePos()
	{
		std::cout << "Mouse : (" << pos.x << " , " << pos.y << ")" << std::endl;
	}

	void Mouse::Zoom(int delta)
	{
		mouse_zoom += delta;
		if (mouse_zoom < MIN_ZOOM) mouse_zoom = MIN_ZOOM;
		else if (mouse_zoom > MAX_ZOOM) mouse_zoom = MAX_ZOOM;
	}

	void Mouse::resetWheel()
	{
		if (this->is_wheel) is_wheel = false;
	}

	void Mouse::setWheel(bool state)
	{
		this->is_wheel = state;
	}

	bool Mouse::isWheel()
	{
		return is_wheel;
	}


	// unique_mouse 
	bool Mouse::getStateMouseUniq(MOUSE::MOUSE_B mousekey)
	{
		if (is_click) {
			return this->mouse[static_cast<int>(mousekey)];
		}
		return false;
	}
	void Mouse::setClick(bool isClick)
	{
		is_click = isClick;
	}
}