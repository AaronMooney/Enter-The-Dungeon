#ifndef Game_hpp
#define Game_hpp

#include "Player.hpp"
#include "Level.hpp"
#include "Window.hpp"
#include "MusicListener.hpp"
#include "Enemy.hpp"
#include "Torch.hpp"
#include "Projectile.hpp"
#include "Key.hpp"
#include "Gem.hpp"

class Game
{
public:
	Game();
	void Initialize();
	void Run();
	bool IsRunning();
	void Update(float timeDelta);
	void Draw(float timeDelta);

	Window* GetWindow() { return &m_window; }

	std::vector<std::shared_ptr<Torch>>* GetTorches() { return &m_torches; }
	void SpawnTorches(int torchCount);

	GAME_STATE m_gameState;
	bool m_isRunning;

private:

	void GenerateLevel();
	float DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2);
	void DrawString(std::string text, sf::Vector2f position, unsigned int size = 10);
	void UpdateItems(sf::Vector2f playerPosition);
	void UpdateEnemies(sf::Vector2f playerPosition, float timeDelta);
	void UpdateProjectiles(float timeDelta);

	void Game::SpawnItem(std::string type, sf::Vector2f position);

	Key m_key;
	std::vector<std::shared_ptr<Torch>> m_torches;
	Window m_window;
	sf::View m_views[static_cast<int>(VIEW::COUNT)];
	sf::Clock m_timestepClock;
	sf::Font m_font;

	std::vector<std::unique_ptr<GameObject>> m_items;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Projectile>> m_projectiles;

	Tile* m_playerPreviousTile;
	Level m_level;
	Player m_player;

	std::ostringstream m_stringStream;
	std::string m_string;
	sf::Text m_text;
	sf::Vector2u m_screenSize;
	sf::Vector2f m_screenCenter;
	bool m_levelWasGenerated;

	MusicListener music;

	sf::SoundBuffer buffer;
	sf::Sound m_gemSound;
};
#endif