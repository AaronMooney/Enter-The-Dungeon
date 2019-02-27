#ifndef AudioComponent_hpp
#define AudioComponent_hpp


#include "GameObject.hpp"
#include "Core.hpp"

class AudioComponent {
public:
	AudioComponent(GameObject& obj, int soundBufferId);
	AudioComponent(GameObject& obj, std::string type);

	void Update(GameObject& obj, float timeDelta);


	sf::Sound m_sound;

private:
	static std::map<std::string, std::pair<int, std::unique_ptr<sf::SoundBuffer>>> m_soundBuffers;

	static int m_currentId;
};

#endif