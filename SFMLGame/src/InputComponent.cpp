#include "InputComponent.hpp"
#include "GameObject.hpp"
#include "Util.hpp"
#include "Projectile.hpp"
#include <iostream>
InputComponent::InputComponent(std::string type)
{
	m_type = type;
}

void InputComponent::update(GameObject& gameObject)
{

	if (m_type == "player") {

		if (IsKeyPressed(KEY::KEY_LEFT)) {
			gameObject.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_LEFT);
			gameObject.GetPhysicsComponent()->SetVelocity({ -200,0 });
			gameObject.GetPhysicsComponent()->SetDirection({ gameObject.GetPosition().x - 200.f, gameObject.GetPosition().y });
			gameObject.m_direction = "west";
			gameObject.GetGraphicsComponent()->SetAnimated(true);
		}

		if (IsKeyPressed(KEY::KEY_UP)) {
			gameObject.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_UP);
			gameObject.GetPhysicsComponent()->SetVelocity({ 0,-200 });
			gameObject.GetPhysicsComponent()->SetDirection({ gameObject.GetPosition().x, gameObject.GetPosition().y - 200.f });
			gameObject.m_direction = "north";
			gameObject.GetGraphicsComponent()->SetAnimated(true);
		}

		if (IsKeyPressed(KEY::KEY_DOWN)) {
			gameObject.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_DOWN);
			gameObject.GetPhysicsComponent()->SetVelocity({ 0,200 });
			gameObject.GetPhysicsComponent()->SetDirection({ gameObject.GetPosition().x, gameObject.GetPosition().y +  200.f });
			gameObject.m_direction = "south";
			gameObject.GetGraphicsComponent()->SetAnimated(true);
		}

		if (IsKeyPressed(KEY::KEY_RIGHT)) {
			gameObject.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_RIGHT);
			gameObject.GetPhysicsComponent()->SetVelocity({ 200,0 });
			gameObject.GetPhysicsComponent()->SetDirection({ gameObject.GetPosition().x + 200.f, gameObject.GetPosition().y });
			gameObject.m_direction = "east";
			gameObject.GetGraphicsComponent()->SetAnimated(true);
		}

		if (IsKeyPressed(KEY::KEY_ATTACK)) {
			if (gameObject.GetAttackComponent()->GetMana() >= 5) {
				gameObject.SetAttacking(true);
			}
		}
	}
}


bool InputComponent::IsKeyPressed(KEY keycode)
{
	switch (keycode)
	{
	case InputComponent::KEY::KEY_LEFT:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		{
			return true;
		}
		break;

	case InputComponent::KEY::KEY_RIGHT:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		{
			return true;
		}
		break;

	case InputComponent::KEY::KEY_UP:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		{
			return true;
		}
		break;

	case InputComponent::KEY::KEY_DOWN:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
		{
			return true;
		}
		break;

	case InputComponent::KEY::KEY_ATTACK:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
		{
			return true;
		}
		break;

	case InputComponent::KEY::KEY_ESC:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return true;
		}
	}

	return false;
}