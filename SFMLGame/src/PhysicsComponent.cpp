#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"

void PhysicsComponent::update(GameObject& gameObejct, float timeDelta)
{
	gameObejct.SetPosition(gameObejct.GetPosition() + (m_velocity * timeDelta));
	m_velocity = { 0,0 };
}

void PhysicsComponent::SetVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

void PhysicsComponent::SetDirection(sf::Vector2f direction)
{
	m_targetDirection = direction;
}

sf::Vector2f PhysicsComponent::GetDirection()
{
	return m_targetDirection;
}

sf::Vector2f PhysicsComponent::GetVelocity() {
	return m_velocity;
}
