#include "Core.hpp"
#include "AudioComponent.hpp"
#include "AssetManager.hpp"

std::map<std::string, std::pair<int, std::unique_ptr<sf::SoundBuffer>>> AudioComponent::m_soundBuffers;
int AudioComponent::m_currentId = 0;

// Default Constructor.
AudioComponent::AudioComponent(GameObject& gameObject, std::string type)
{
	if (type == "music") {
		// seed rand
		srand(time(NULL));

		// Setup the main game music.
		int trackIndex = std::rand() % static_cast<int>(MUSIC_TRACK::COUNT) + 1;


		// Load the music track.
		gameObject.m_music.openFromFile("resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav");

		gameObject.m_music.play();

		gameObject.m_music.setVolume(10);
	}
}

AudioComponent::AudioComponent(GameObject& gameObject, int soundBufferId):
	m_sound(AssetManager::GetSoundBuffer(soundBufferId))
{
	m_sound.setMinDistance(50.0f);
	m_sound.setAttenuation(10.0f);
}

void AudioComponent::Update(GameObject& gameObject, float timeDelta)
{
	m_sound.setVolume(100.0f);
	if (m_sound.getLoop() && m_sound.getStatus() != m_sound.Playing) m_sound.play();

	if (gameObject.m_name != "Key") {
		sf::Vector2f pos = gameObject.GetPosition();
		m_sound.setPosition(pos.x, 0, pos.y);
	}
}
