#include "MusicListener.hpp"

MusicListener::MusicListener() {
	m_audio = std::make_shared<AudioComponent>(*this,"music");
}

void MusicListener::Update(float timeDelta)
{
	GameObject::Update(timeDelta);
}
