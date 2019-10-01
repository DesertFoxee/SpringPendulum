
#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

/*
	-Get number Mouse in enum class using Complie = current line - begin line - space
*/
#define MIN_ZOOM 1

#define MAX_ZOOM 20


constexpr auto BEGIN_MOUSE = __LINE__;
namespace MOUSE {
	enum class MOUSE_B
	{
		RIGHT,
		LEFT,
		MIDDLE,
		WHEEL,
	};
	constexpr static auto COUNT_MOUSE_B = __LINE__ - BEGIN_MOUSE - 4;

	enum class MOUSE_E
	{
	};


	class Mouse
	{
	public:
		~Mouse();

		static Mouse& getIntance()
		{
			static std::unique_ptr<Mouse> instance = std::unique_ptr<Mouse>(new Mouse());
			return *instance;
		}


		sf::Vector2i getMouseScreen();
		sf::Vector2i getMouseWindow(const sf::Window& window);


		void setMouseScreen(const sf::Vector2i& pos);
		void setMouseWindow(const sf::Window& window, const sf::Vector2i& pos);


		void show();
		void showMousePos();

		// procee wheel moose ;
		void Zoom(int delta = 1);
		int getZoom() { return Mouse::mouse_zoom; };
		void resetZoom() { mouse_zoom = MIN_ZOOM; }

		// process handle wheel ;
		void resetWheel();
		void setWheel(bool state);
		bool isWheel();

		// process mouse real ;

		void resetMouseReal();
		void setStateMouse(MOUSE::MOUSE_B mousekey, bool state);
		bool getStateMouse(MOUSE::MOUSE_B mousekey);

		// process unique_mouse 

		//void resetMouseUniq();
		bool getStateMouseUniq(MOUSE::MOUSE_B mousekey);
		void setClick(bool isClick);
		void resetClick() { if (is_click) is_click = false; }

	private:
		Mouse();
		static sf::Vector2i pos;
		std::vector<bool> mouse;
		static int mouse_zoom;
		bool is_click;
		bool is_wheel;
	};
};




#endif // !MOUSEMANAGER_H


