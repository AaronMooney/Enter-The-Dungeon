#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"
#include "Core.hpp"
#include "Util.hpp"

class GraphicsComponent
{
public:
	GraphicsComponent();
	virtual ~GraphicsComponent() {}
	virtual void update(GameObject& gameObject, float timeDelta);
	virtual void Draw(sf::RenderWindow &window, float timeDelta);
	virtual void SetAnimationState(ANIMATION_STATE state) = 0;


	bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
	sf::Sprite& GetSprite();
	int GetFrameCount() const;
	bool IsAnimated();
	void SetAnimated(bool isAnimated);
	int(&GetTextureIDs())[static_cast<int>(ANIMATION_STATE::COUNT)];
	int& GetCurrenTextureIndex();

	float m_timeDelta;
	int m_animationSpeed;
	void NextFrame();

protected:

	sf::Sprite m_sprite;

	int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

	int m_currentTextureIndex;

private:


	bool m_isAnimated;
	int m_frameCount;
	int m_currentFrame;
	int m_frameWidth;
	int m_frameHeight;

};





class PlayerGraphicsComponent : public GraphicsComponent
{
public:
	PlayerGraphicsComponent(std::string name);
	virtual void update(GameObject& gameObject, float timeDelta);

	void SetAnimationState(ANIMATION_STATE state) { animState = state; }
	ANIMATION_STATE GetAnimationState() { return animState; }
private:
	ANIMATION_STATE animState = ANIMATION_STATE::WALK_DOWN;

};

class ItemGraphicsComponent : public GraphicsComponent
{
public:
	ItemGraphicsComponent(std::string name);
	virtual void update(GameObject& gameObject, float timeDelta);

	void SetAnimationState(ANIMATION_STATE state) { animState = state; }
	ANIMATION_STATE GetAnimationState() { return animState; }
private:
	ANIMATION_STATE animState;
};

class EnemyGraphicsComponent : public GraphicsComponent
{
public:
	EnemyGraphicsComponent(std::string name);
	virtual void update(GameObject& gameObject, float timeDelta);

	void SetAnimationState(ANIMATION_STATE state) { animState = state; }
	ANIMATION_STATE GetAnimationState() { return animState; }
private:
	ANIMATION_STATE animState = ANIMATION_STATE::WALK_DOWN;

};



#endif
