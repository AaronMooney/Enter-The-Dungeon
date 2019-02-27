#ifndef Player_hpp
#define Player_hpp

#include "GameObject.hpp"
#include "Level.hpp"
#include "Projectile.hpp"


class Player : public GameObject
{
public:
	Player();
	void Update(float timeDelta, Level& level);
};
#endif