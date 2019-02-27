#include "Projectile.hpp"
#include "AssetManager.hpp"
#include "Util.hpp"

Projectile::Projectile(sf::Vector2f spawn, std::string direction) {
	m_graphics = std::make_shared<ItemGraphicsComponent>("resources/projectiles/spr_magic_ball.png");
	m_physics = std::make_shared<PhysicsComponent>();
	m_direction = direction;
	SetPosition(spawn);
	sf::Vector2f vel = { 0.f,0.f };
}

void Projectile::Update(float timeDelta)
{
	timeToDie += timeDelta;
	sf::Vector2f vel = { 0.f,0.f };
	if (m_direction == "north") {
		vel = { 0.f,-200.f };
	}
	else if (m_direction == "south") {
		vel = { 0.f,200.f };
	}
	else if (m_direction == "west") {
		vel = { -200.f,0.f };
	}
	else {
		vel = { 200.f,0.f };
	}
	m_physics->SetVelocity(vel);

	m_graphics->GetSprite().setRotation(m_graphics->GetSprite().getRotation() + (400.f * timeDelta));

	SetPosition(sf::Vector2f(GetPosition().x + (m_physics->GetVelocity().x * timeDelta), GetPosition().y + (m_physics->GetVelocity().y * timeDelta)));
}
