#include "KeyboardManager.h"


namespace KEYBOARD {

	Keyboard::Keyboard()
	{
		for (auto i = 0; i < KEYBOARD::COUNT_KEY_B; i++) {
			this->keyboard.push_back(false);
		}
		this->is_press = false;
	}

	Keyboard::~Keyboard()
	{
	}

	void Keyboard::setPress(bool isPress)
	{
		is_press = isPress;
	}

	bool Keyboard::getStateKeyBoardUniq(KEYBOARD::KEY_B key)
	{
		if (is_press) {
			return this->keyboard[static_cast<int>(key)];
		}
		return false;
	}

	void Keyboard::setStateKeyboard(KEYBOARD::KEY_B key, bool state)
	{
		this->keyboard[static_cast<int>(key)] = state;
	}

	bool Keyboard::getStateKeyBoard(KEYBOARD::KEY_B  key)
	{
		return this->keyboard[static_cast<int>(key)];
	}

	void Keyboard::resetReal()
	{
		for (auto i = 0; i < KEYBOARD::COUNT_KEY_B; i++) {
			this->keyboard[i] = false;
		}
	}

	void Keyboard::show()
	{
		std::cout << "Keyboard map : ";
		for (auto i = 0; i < KEYBOARD::COUNT_KEY_B; i++) {
			std::cout << keyboard[i];
		}
		std::cout << std::endl;
	}


}