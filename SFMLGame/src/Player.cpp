#include "Core.hpp"
#include "Player.hpp"
#include "AssetManager.hpp"
#include <iostream>

// Constructor.
Player::Player()
{
	m_graphics = std::make_shared<PlayerGraphicsComponent>("mage");
	m_physics = std::make_shared<PhysicsComponent>();
	m_input = std::make_shared<InputComponent>("player");
	m_health = std::make_shared<HealthComponent>(100.f);
	m_attack = std::make_shared<AttackComponent>();
	m_audio = std::make_shared<AudioComponent>(*this, AssetManager::AddSoundBuffer("resources/sounds/snd_player_hit.wav"));

	m_name = "player";
}

// Updates the player object.
void Player::Update(float timeDelta, Level& level)
{
	GameObject::Update(timeDelta);

	if (CausesCollision(sf::Vector2f(m_physics->GetVelocity().x, 0.0f), level))
	{
		m_position.x = previousPosition.x;
	}
	else
	{
		m_position.x += m_physics->GetVelocity().x;
	}

	if (CausesCollision(sf::Vector2f(0.0f, m_physics->GetVelocity().y), level))
	{
		m_position.y = previousPosition.y;
	}
	else
	{
		m_position.y += m_physics->GetVelocity().y;
	}
	previousPosition = m_position;
}