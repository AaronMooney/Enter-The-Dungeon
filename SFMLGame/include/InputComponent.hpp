#ifndef InputComponent_hpp
#define InputComponent_hpp
class GameObject;
#include "Util.hpp"

#include <stdio.h>
#include "GameObject.hpp"
#include "Core.hpp"

class InputComponent
{
public:
	/**
	* An enum denoting all possible input keys.
	*/
	enum class KEY
	{
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_E_LEFT,
		KEY_E_RIGHT,
		KEY_E_UP,
		KEY_E_DOWN,
		KEY_ATTACK,
		KEY_ESC
	};

	std::string m_type;

	static bool IsKeyPressed(KEY keycode);

	void update(GameObject& GameObject);
	InputComponent(std::string type);
	std::string m_direction;
};

#endif
