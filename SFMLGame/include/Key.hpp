#ifndef Key_hpp
#define Key_hpp

#include "GameObject.hpp"

class Key : public GameObject
{
public:
	Key();

	void Update(float timeDelta);
};
#endif