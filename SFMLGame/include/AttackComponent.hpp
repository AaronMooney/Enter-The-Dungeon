#ifndef AttackComponent_hpp
#define AttackComponent_hpp

#include "Core.hpp"
#include "GameObject.hpp"
class AttackComponent
{
public:
	AttackComponent();
	virtual ~AttackComponent(){}

	void Update(GameObject& gameObject, float timeDelta);


	bool CanAttack();

	void SetMana(float mana);
	float GetMana();

private:

	float m_mana;
	float m_cooldown;
};

#endif
