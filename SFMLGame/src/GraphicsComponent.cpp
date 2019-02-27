#include "GraphicsComponent.hpp"
#include "AssetManager.hpp"

GraphicsComponent::GraphicsComponent() :
	m_animationSpeed(0),
	m_isAnimated(false),
	m_frameCount(0),
	m_currentFrame(0),
	m_frameWidth(0),
	m_frameHeight(0),
	m_timeDelta(0) {}

void GraphicsComponent::update(GameObject& gameObject, float timeDelta)
{
	m_timeDelta = timeDelta;
}

void GraphicsComponent::Draw(sf::RenderWindow &window, float timeDelta) {
	if (m_isAnimated) {
		m_timeDelta += timeDelta;
		if (m_timeDelta >= (1.f / m_animationSpeed))
		{
			NextFrame();
			m_timeDelta = 0;
		}
	}
	window.draw(m_sprite);
}

bool GraphicsComponent::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed) {
	m_sprite.setTexture(texture);
	m_animationSpeed = frameSpeed;
	m_frameCount = frames;

	sf::Vector2u texSize = m_sprite.getTexture()->getSize();
	m_frameWidth = texSize.x / m_frameCount;
	m_frameHeight = texSize.y;

	if (frames > 1) {
		m_isAnimated = true;
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	}
	else m_isAnimated = false;

	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	return true;
}

void GraphicsComponent::NextFrame() {
	if (m_currentFrame == (m_frameCount - 1)) m_currentFrame = 0;
	else m_currentFrame++;
	m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

sf::Sprite& GraphicsComponent::GetSprite() { return m_sprite; }

int GraphicsComponent::GetFrameCount() const { return m_frameCount; }

bool GraphicsComponent::IsAnimated() { return m_isAnimated; }

int(&GraphicsComponent::GetTextureIDs())[static_cast<int>(ANIMATION_STATE::COUNT)]{ return m_textureIDs; }

int& GraphicsComponent::GetCurrenTextureIndex() { return m_currentTextureIndex; }


void GraphicsComponent::SetAnimated(bool isAnimated) {
	m_isAnimated = isAnimated;

	if (isAnimated) m_currentFrame = 0;
	else m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}



// Constructor.
PlayerGraphicsComponent::PlayerGraphicsComponent(std::string name) : GraphicsComponent()
{

	std::string className;
	className = name;

	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = AssetManager::AddTexture("resources/players/" + className + "/spr_" + className + "_idle_left.png");

	// Set initial sprite.
	SetSprite(AssetManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
	m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));
}

void PlayerGraphicsComponent::update(GameObject& gameObject, float timeDelta)
{
	GraphicsComponent::update(gameObject, timeDelta);

	if (m_currentTextureIndex != static_cast<int>(animState)) {
		m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(AssetManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}
	if (gameObject.GetPhysicsComponent() == nullptr) return;

	sf::Vector2f movement = gameObject.GetPhysicsComponent()->GetVelocity();
	if (movement.x == 0 && movement.y == 0) {
		if (IsAnimated()) {
			m_currentTextureIndex += 4;
			m_sprite.setTexture(AssetManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
			SetAnimated(false);
		}
	}
	else {
		if (!IsAnimated()) {
			m_currentTextureIndex -= 4;
			m_sprite.setTexture(AssetManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
			SetAnimated(true);
		}
	}

	animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);
}

ItemGraphicsComponent::ItemGraphicsComponent(std::string name) : GraphicsComponent()
{
	int textureID = AssetManager::AddTexture(name);
	SetSprite(AssetManager::GetTexture(textureID), false, 5, 12);
}

void ItemGraphicsComponent::update(GameObject& gameObject, float timeDelta)
{
	GraphicsComponent::update(gameObject, timeDelta);
}


// Constructor.
EnemyGraphicsComponent::EnemyGraphicsComponent(std::string name) : GraphicsComponent()
{

	std::string className;
	className = name;

	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = AssetManager::AddTexture("resources/enemies/" + className + "/spr_" + className + "_idle_left.png");

	// Set initial sprite.
	SetSprite(AssetManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);

	m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));
}

void EnemyGraphicsComponent::update(GameObject& gameObject, float timeDelta)
{
	GraphicsComponent::update(gameObject, timeDelta);

	if (m_currentTextureIndex != static_cast<int>(animState)) {
		m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(AssetManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}
	if (gameObject.GetPhysicsComponent() == nullptr) return;

	sf::Vector2f movement = gameObject.GetPhysicsComponent()->GetVelocity();
	if (movement.x == 0 && movement.y == 0) {
		if (IsAnimated()) {
			m_currentTextureIndex += 4;
			m_sprite.setTexture(AssetManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
			SetAnimated(false);
		}
	}
	else {
		if (!IsAnimated()) {
			m_currentTextureIndex -= 4;
			m_sprite.setTexture(AssetManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
			SetAnimated(true);
		}
	}
	animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);
}