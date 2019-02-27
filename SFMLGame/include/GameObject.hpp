#ifndef GameObject_hpp
#define GameObject_hpp

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;
class AudioComponent;
class AIComponent;
class AttackComponent;
#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "AudioComponent.hpp"
#include "AIComponent.hpp"
#include "HealthComponent.hpp"
#include "AttackComponent.hpp"
#include "Level.hpp"

class GameObject
{
public:
	GameObject();
	void Update(float timeDelta);
	virtual void Draw(sf::RenderWindow &window, float timeDelta);
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() const;

	void SetAttacking(bool attacking);
	bool IsAttacking();


	void SetInputComponent(std::shared_ptr<InputComponent> input) { m_input = input; }
	void SetPhysicsComponent(std::shared_ptr<PhysicsComponent> physics) { m_physics = physics; }
	void SetGraphicsComponent(std::shared_ptr<GraphicsComponent> graphics) { m_graphics = graphics; }
	void SetAudioComponent(std::shared_ptr<AudioComponent> audio) { m_audio = audio; }
	void SetAiComponent(std::shared_ptr<AIComponent> ai) { m_ai = ai; }
	void SetAiComponent(std::shared_ptr<HealthComponent> health) { m_health = health; }
	void SetAiComponent(std::shared_ptr<AttackComponent> attack) { m_attack = attack; }

	std::shared_ptr<InputComponent> GetInputComponent() { return m_input; }
	std::shared_ptr<PhysicsComponent> GetPhysicsComponent() { return m_physics; }
	std::shared_ptr<GraphicsComponent> GetGraphicsComponent() { return m_graphics; }
	std::shared_ptr<AudioComponent> GetAudioComponent() { return m_audio; }
	std::shared_ptr<AIComponent> GetAIComponent() { return m_ai; }
	std::shared_ptr<HealthComponent> GetHealthComponent() { return m_health; }
	std::shared_ptr<AttackComponent> GetAttackComponent() { return m_attack; }

	bool CausesCollision(sf::Vector2f movement, Level& level);

	float m_timeDelta;
	float m_speed = 200;
	std::string m_direction;

	sf::Vector2f movementSpeed;
	sf::Vector2f m_position;
	sf::Vector2f previousPosition;

	sf::Music m_music;

	ITEM m_type;
	std::string m_name;




protected:

	std::shared_ptr<InputComponent> m_input;
	std::shared_ptr<PhysicsComponent> m_physics;
	std::shared_ptr<GraphicsComponent> m_graphics;
	std::shared_ptr<AudioComponent> m_audio;
	std::shared_ptr<AIComponent> m_ai;
	std::shared_ptr<HealthComponent> m_health;
	std::shared_ptr<AttackComponent> m_attack;


	void SetItemName(std::string name);

	bool m_attacking;

};
#endif