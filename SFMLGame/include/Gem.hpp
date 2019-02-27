#ifndef Gem_hpp
#define Gem_hpp

#include "GameObject.hpp"
#include "Core.hpp"

class Gem : public GameObject
{
public:
	Gem();

	float m_health = 10.f;
	float m_mana = 10.f;
};
#endif

