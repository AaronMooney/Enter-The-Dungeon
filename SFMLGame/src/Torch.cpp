#include "Core.hpp"
#include "Torch.hpp"
#include <iostream>
#include "AssetManager.hpp"

// Default constructor.
Torch::Torch() :
	m_brightness(1.f)
{
	m_graphics = std::make_shared<ItemGraphicsComponent>("resources/spr_torch.png");
	m_audio = std::make_shared<AudioComponent>(*this, AssetManager::AddSoundBuffer("resources/sounds/snd_fire.wav"));

}

// Update the brightness of the torch.
void Torch::Update(float timeDelta)
{
	GameObject::Update(timeDelta);
	// Generate a random number between 80 and 120, divide by 100 and store as float between .8 and 1.2.
	m_brightness = (std::rand() % 41 + 80) / 100.f;
}

// Returns the brightness of the torch.
float Torch::GetBrightness()
{
	return m_brightness;
}