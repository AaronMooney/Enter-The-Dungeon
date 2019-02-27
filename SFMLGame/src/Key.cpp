#include "Core.hpp"
#include "Key.hpp"
#include "AssetManager.hpp"

// Default constructor.
Key::Key()
{
	m_graphics = std::make_shared<ItemGraphicsComponent>("resources/loot/key/spr_pickup_key.png");
	m_audio = std::make_shared<AudioComponent>(*this, AssetManager::AddSoundBuffer("resources/sounds/snd_key_pickup.wav"));

	// Set item name.
	SetItemName("Key");

	// Set item type.
	m_type = ITEM::KEY;

}

void Key::Update(float timeDelta)
{
	GameObject::Update(timeDelta);
	
}