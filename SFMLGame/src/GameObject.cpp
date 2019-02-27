#include "Core.hpp"
#include "GameObject.hpp"

// Default constructor.
GameObject::GameObject()
{
	m_attacking = false;
	m_direction = "";
}

void GameObject::Update(float timeDelta)
{

	if (m_input != nullptr) { m_input->update(*this); }
	if (m_physics != nullptr) { m_physics->update(*this, timeDelta); }
	if (m_graphics != nullptr) { m_graphics->update(*this, timeDelta); }
	if (m_audio != nullptr) { m_audio->Update(*this, timeDelta); }
	if (m_ai != nullptr) { m_ai->Update(*this, timeDelta); }
	if (m_health != nullptr) { m_health->Update(timeDelta); }
	if (m_attack != nullptr) { m_attack->Update(*this, timeDelta); }

	m_timeDelta = timeDelta;
}

// Sets the position of the object.
void GameObject::SetPosition(sf::Vector2f position)
{
	m_position = position;
	if (m_graphics != nullptr) m_graphics->GetSprite().setPosition(position);
}

// Returns the position of the object.
sf::Vector2f GameObject::GetPosition() const
{
	return m_position;
}

// Draws the object to the given render window.
void GameObject::Draw(sf::RenderWindow &window, float timeDelta)
{
	if (m_graphics != nullptr ) m_graphics->Draw(window, timeDelta);
}

// Sets the item name.
void GameObject::SetItemName(std::string name)
{
	// Store new name.
	m_name = name;

	// Set the item name.
	std::ostringstream ss;
	ss << m_name;
	std::string str(ss.str());
}

// Checks is the given movement will result in a collision.
bool GameObject::CausesCollision(sf::Vector2f movement, Level& level)
{
	// Get the tiles that the four corners other player are overlapping with.
	Tile* overlappingTiles[4];
	sf::Vector2f newPosition = m_position + movement;

	// Top left.
	overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

	// Top right.
	overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

	// Bottom left.
	overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

	// Bottom right.
	overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

	// If any of the overlapping tiles are solid there was a collision.
	for (int i = 0; i < 4; i++)
	{
		if (level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
			return true;
	}

	// If we've not returned yet no collisions were found.
	return false;
}

bool GameObject::IsAttacking() {
	if (m_attacking) {
		m_attacking = false;
		return true;
	}
	else {
		return false;
	}
}

void GameObject::SetAttacking(bool attacking) {
	m_attacking = attacking;
}