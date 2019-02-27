#include "HealthComponent.hpp"

HealthComponent::HealthComponent(float health)
{
	m_health = health;
	m_maxHealth = health;
	m_cooldown = 0;
}

void HealthComponent::Update(float timeDelta)
{
	m_cooldown += timeDelta;

	if (m_health >= m_maxHealth) {
		m_health = m_maxHealth;
	}
	if (IsDead()) {
		m_health = 0;
	}
}

float HealthComponent::GetHealth()
{
	return m_health;
}

void HealthComponent::SetHealth(float amount)
{
	m_health = amount;
}

float HealthComponent::GetMaxHealth()
{
	return m_maxHealth;
}

void HealthComponent::SetMaxHealth(float amount)
{
	m_maxHealth = amount;
}

void HealthComponent::TakeDamage(float amount)
{
	m_health -= amount;
}

bool HealthComponent::IsDead() {
	return m_health <= 0;
}

bool HealthComponent::CanTakeDamage() {
	if (m_cooldown < 0.5f) {
		return false;
	}
	m_cooldown = 0.f;
	return true;
}



