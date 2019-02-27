#ifndef Enemy_hpp
#define Enemy_hpp

#include "Core.hpp"
#include "Level.hpp"
#include "GameObject.hpp"

class Enemy : public GameObject {
public:
	Enemy();
	void Update(float timeDelta, Level& level);

protected:
	sf::Vector2f m_currentTarget;
};

#endif

