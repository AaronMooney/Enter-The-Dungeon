#include "Enemy.hpp"

Enemy::Enemy() {
	m_currentTarget = { 0.f,0.f };
	
	m_speed = rand() % 51 + 150;

	SetItemName("enemy");

	m_graphics = std::make_shared<EnemyGraphicsComponent>("skeleton");
	m_physics = std::make_shared<PhysicsComponent>();
	m_ai = std::make_shared<AIComponent>();
	m_health = std::make_shared<HealthComponent>(100.f);
	m_attack = std::make_shared<AttackComponent>();
}

void Enemy::Update(float timeDelta, Level& level) {
	GameObject::Update(timeDelta);

	if (m_health->GetHealth() <= 75.f) {
		m_graphics->GetSprite().setColor(sf::Color(255,128,128));
	}
	if (m_health->GetHealth() <= 50.f) {
		m_graphics->GetSprite().setColor(sf::Color(255, 0, 0));
	}
	if (m_health->GetHealth() <= 25.f) {
		m_graphics->GetSprite().setColor(sf::Color(128, 0, 0));
	}
}