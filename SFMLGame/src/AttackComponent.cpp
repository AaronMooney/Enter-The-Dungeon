#include "AttackComponent.hpp"
#include "AssetManager.hpp"

AttackComponent::AttackComponent()
{
	m_cooldown = 0;
	m_mana = 100.f;
}

void AttackComponent::Update(GameObject & gameObject, float timeDelta)
{
	m_cooldown += timeDelta;

	if (m_mana >= 100.f) {
		m_mana = 100.f;
	}
	if (m_mana <= 0) {
		m_mana = 0;
	}
	
}

bool AttackComponent::CanAttack() {
	if (m_cooldown < 0.5f) { 
		return false; 
	}
	m_cooldown = 0.f;
	return true;
}

void AttackComponent::SetMana(float mana) {
	m_mana = mana;
}

float AttackComponent::GetMana() {
	return m_mana;
}
