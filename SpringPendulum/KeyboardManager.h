#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Convert.h"


constexpr auto BEGIN_KEYBOARD = __LINE__;
namespace KEYBOARD
{
	enum class KEY_B
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		CONTROL,
		SHIFT,
	};
	constexpr static auto COUNT_KEY_B = __LINE__ - BEGIN_KEYBOARD - 4;

	enum class KEY_E
	{
		COUNT
	};

	class Keyboard
	{
	public:
		~Keyboard();

		static Keyboard& getIntance()
		{
			static std::unique_ptr<Keyboard> instance = std::unique_ptr<Keyboard>(new Keyboard());
			return *instance;
		}

		// using for keyboard real_time 
		void setStateKeyboard(KEYBOARD::KEY_B key, bool state);
		bool getStateKeyBoard(KEYBOARD::KEY_B key);
		void resetReal();


		//using for keyboard one click
		void setPress(bool isPress);
		bool getStateKeyBoardUniq(KEYBOARD::KEY_B key);
		void resetPress() { if (is_press) is_press = false; };

		// function test

		void show();

	private:
		Keyboard();
		std::vector<bool> keyboard;
		bool is_press;
	};
}




#endif // !KEYBOARDMANAGER_H


