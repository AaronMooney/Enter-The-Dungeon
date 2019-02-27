#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "Core.hpp"
#include "GameObject.hpp"
#include "Level.hpp"

class GameObject;
class AIComponent;

class AIComponent {
public:
	AIComponent();
	virtual ~AIComponent() {}

	void Update(GameObject& gameObject, float timeDelta);
	void UpdatePathFinding(GameObject& gameObject, Level& level, sf::Vector2f playerPosition);

private:

	sf::Vector2f m_position;

	Level* m_level;
	sf::Vector2f m_destination;
	std::shared_ptr<GameObject> m_target;
	std::vector<sf::Vector2f> m_targetPositions;
};
#endif

