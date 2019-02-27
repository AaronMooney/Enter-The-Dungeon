#ifndef Projectile_hpp
#define Projectile_hpp

#include "GameObject.hpp"
#include "Core.hpp"

class Projectile : public GameObject
{
public:
	Projectile(sf::Vector2f spawn, std::string direction);
	void Update(float timeDelta);

	float timeToDie;

};
#endif

