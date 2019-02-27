#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include <stdio.h>
#include "Core.hpp"
class GameObject;

class PhysicsComponent
{
public:
	PhysicsComponent() {};
	virtual ~PhysicsComponent() {}

	void update(GameObject& gameObejct, float timeDelta);

	void SetVelocity(sf::Vector2f velocity);
	sf::Vector2f GetVelocity();

	void SetDirection(sf::Vector2f direction);
	sf::Vector2f GetDirection();

	sf::Vector2f movementSpeed{ 0.f, 0.f };
	int m_speed;

protected:
	sf::Vector2f m_velocity;
	sf::Vector2f m_targetDirection;
};


#endif
