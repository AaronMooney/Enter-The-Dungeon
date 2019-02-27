#ifndef AssetManager_hpp
#define AssetManager_hpp

#include "Core.hpp"

class AssetManager {
public:
	AssetManager();
	static int AddTexture(std::string filePath);
	static int AddSoundBuffer(std::string filePath);
	static void RemoveTexture(int textureID);
	static void RemoveSoundBuffer(int soundID);
	static sf::Texture& GetTexture(int textureId);
	static sf::SoundBuffer& GetSoundBuffer(int soundID);

private:
	static std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> m_textures;
	static std::map<std::string, std::pair<int, std::unique_ptr<sf::SoundBuffer>>> m_soundBuffers;
	static int m_currentTextureId;
	static int m_currentSoundId;
};
#endif