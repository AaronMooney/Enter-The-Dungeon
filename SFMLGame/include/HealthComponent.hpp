#ifndef HealthComponent_hpp
#define HealthComponent_hpp

#include "Core.hpp"

class HealthComponent {
public:
	HealthComponent(float health);
	virtual ~HealthComponent() {}
	void Update(float TimeDelta);

	float GetHealth();
	void SetHealth(float amount);
	float GetMaxHealth();
	void SetMaxHealth(float amount);

	void TakeDamage(float amount);
	bool IsDead();

	bool CanTakeDamage();

private:
	float m_health;
	float m_maxHealth;
	float m_cooldown;
};

#endif 
