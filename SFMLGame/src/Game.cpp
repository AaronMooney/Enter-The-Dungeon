#include "Core.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"
#include "Menu.hpp"

Game::Game() :
	m_window("Enter the Dungeon", sf::Vector2u(1280, 800)),
	m_gameState(GAME_STATE::MAIN_MENU),
	m_isRunning(true),
	m_string(""),
	m_screenSize({ 0, 0 }),
	m_screenCenter({ 0, 0 }),
	m_levelWasGenerated(false)
{
	// Enable VSync.
	m_window.GetRenderWindow()->setVerticalSyncEnabled(true);

	// Hide the mouse cursor.
	m_window.GetRenderWindow()->setMouseCursorVisible(false);

	// Calculate and store the center of the screen.
	m_screenCenter = { m_window.GetRenderWindow()->getSize().x / 2.f, m_window.GetRenderWindow()->getSize().y / 2.f };

	// Create the level object.
	m_level = Level(*m_window.GetRenderWindow());

	// Create the game font.
	m_font.loadFromFile("resources/fonts/ADDSBP__.TTF");

	m_gemSound.setBuffer(AssetManager::GetSoundBuffer(AssetManager::AddSoundBuffer("resources/sounds/snd_gem_pickup.wav")));

	if (m_gameState == GAME_STATE::PLAYING) {
		Initialize();
		Run();
	}

}

// Initializes the game.
void Game::Initialize()
{
	// Get the screen size.
	m_screenSize = m_window.GetRenderWindow()->getSize();

	// Generate a level.
	GenerateLevel();

	// Define the game views.
	m_views[static_cast<int>(VIEW::MAIN)] = m_window.GetRenderWindow()->getDefaultView();
	m_views[static_cast<int>(VIEW::MAIN)].zoom(0.5f);
	m_views[static_cast<int>(VIEW::UI)] = m_window.GetRenderWindow()->getDefaultView();


	// Set the position of the player.
	m_player.SetPosition(sf::Vector2f(m_screenCenter.x + 197.f, m_screenCenter.y + 410.f));
}

// Generates a new level.
void Game::GenerateLevel()
{
	// Generate a new level.
	m_level.GenerateLevel();

	m_torches.clear();
	SpawnTorches(5);

	// Get all torches from the level.
	auto torches = GetTorches();

	// If there are torches.
	if (!torches->empty())
	{
		// sound for each torch
		for (std::shared_ptr<Torch> torch : *torches)
		{
			torch->GetAudioComponent()->m_sound.play();
			torch->GetAudioComponent()->m_sound.setLoop(true);
		}
	}

	// Add a key to the level.
	SpawnItem("Key", m_level.GetRandomSpawnLocation());
	
	for (auto i = 0; i < 10; ++i) {
		SpawnItem("enemy" , m_level.GetRandomSpawnLocation());
	}

	for (int i = 0; i < 30; i++) {
		SpawnItem("Gem", m_level.GetRandomSpawnLocation());
	}

	// Moves the player to the start.
	m_player.SetPosition(m_level.SpawnLocation());
}

// Spawns the given number of torches in the level.
void Game::SpawnTorches(int torchCount)
{
	// List of used tiles.
	std::vector<Tile*> usedTiles;

	bool tileFound;

	// For each torch.
	for (int i = 0; i < torchCount; i++)
	{
		tileFound = false;

		// Loop until we find a valid tile.
		while (!tileFound)
		{
			// Find a random tile.
			int columnIndex = std::rand() % (GRID_WIDTH - 2) + 1;
			int rowIndex = std::rand() % (GRID_HEIGHT - 2) + 1;

			Tile* tile = &m_level.m_grid[columnIndex][rowIndex];

			if (tile->type == TILE::WALL_TOP)
			{
				if (std::find(usedTiles.begin(), usedTiles.end(), tile) == usedTiles.end())
				{
					std::shared_ptr<Torch> torch = std::make_shared<Torch>();
					torch->SetPosition(m_level.GetActualTileLocation(columnIndex, rowIndex));
					m_torches.push_back(torch);
					tileFound = true;
				}
			}
		}
	}
}

// Returns the running state of the game.
bool Game::IsRunning()
{
	return m_isRunning;
}

// Main game loop.
void Game::Run()
{
	float currentTime = m_timestepClock.restart().asSeconds();
	float timeDelta = 0.f;
	// Loop until there is a quite message from the window or the user pressed escape.
	while (m_isRunning)
	{
		m_window.Update();

		float newTime = m_timestepClock.getElapsedTime().asSeconds();
		float frameTime = std::max(0.f, newTime - currentTime);
		currentTime = newTime;

		// Update all items in the level.
		if (!m_levelWasGenerated)
		{
			Update(frameTime);

			// Draw all items in the level.
			Draw(frameTime);
		}
		else
		{
			m_levelWasGenerated = false;
		}

		if (m_window.IsDone()) {
			m_isRunning = false;
		}
	}
}

// Updates the game.
void Game::Update(float timeDelta)
{
	// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::PLAYING:
	{
		// First check if the player is at the exit. If so there's no need to update anything.
		Tile& playerTile = *m_level.GetTile(m_player.GetPosition());

		if (playerTile.type == TILE::WALL_DOOR_UNLOCKED)
		{
			// Clear all current items.
			m_items.clear();

			// Clear all current enemies.
			m_enemies.clear();

			// Generate a new room.
			GenerateLevel();

		}
		else
		{
			// Update the player.
			m_player.Update(timeDelta, m_level);

			// Store the player position as it's used many times.
			sf::Vector2f playerPosition = m_player.GetPosition();

			// If the player is attacking create a projectile.
			if (m_player.IsAttacking())
			{

				if (m_player.GetAttackComponent()->GetMana() >= 5 && m_player.GetAttackComponent()->CanAttack())
				{
					std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(m_player.GetPosition(), m_player.m_direction);
					m_projectiles.push_back(std::move(proj));
					m_player.GetAttackComponent()->SetMana(m_player.GetAttackComponent()->GetMana() - 5);
				}
			}

			// Update all items.
			UpdateItems(playerPosition);

			// Update all enemies.
			UpdateEnemies(playerPosition, timeDelta);

			// Update all projectiles.
			UpdateProjectiles(timeDelta);

			sf::Listener::setPosition(playerPosition.x, 0.0f, playerPosition.y);

			// Get all torches from the level.
			auto torches = GetTorches();

			// If there are torches.
			if (!torches->empty())
			{
				for (std::shared_ptr<Torch> torch : *torches)
				{
					torch->Update(timeDelta);
				}
			}

			// Check if the player has moved grid square.
			Tile* playerCurrentTile = m_level.GetTile(playerPosition);

			if (m_playerPreviousTile != playerCurrentTile)
			{
				// Store the new tile.
				m_playerPreviousTile = playerCurrentTile;

				// Update path finding for all enemies if within range of the player.
				for (auto& enemy : m_enemies)
				{
					enemy->GetAIComponent()->UpdatePathFinding(*enemy, m_level, m_level.GetRandomSpawnLocation());
					if (DistanceBetweenPoints(enemy->GetPosition(), playerPosition) < 200.0f)
					{
						enemy->GetAIComponent()->UpdatePathFinding(*enemy ,m_level, playerPosition);
					}
				}
			}

			m_key.Update(timeDelta);

			// Venter the view.
			m_views[static_cast<int>(VIEW::MAIN)].setCenter(playerPosition);
		}
	}
	break;

	case GAME_STATE::GAME_OVER:
		m_enemies.clear();
		m_items.clear();
		m_player.GetAttackComponent()->SetMana(100.f);
		m_player.GetHealthComponent()->SetHealth(100.f);
		m_isRunning = false;
		break;
	}
}

// Updates all items in the level.
void Game::UpdateItems(sf::Vector2f playerPosition)
{
	// Update all items.
	auto itemIterator = m_items.begin();
	while (itemIterator != m_items.end())
	{
		// Get the item from the iterator.
		GameObject& item = **itemIterator;

		// Check if the player is within pickup range of the item.
		if (DistanceBetweenPoints(item.GetPosition(), playerPosition) < 40.f)
		{
			// Check what type of object it was.
			switch (item.m_type)
			{

			case ITEM::GEM:
			{
				// Get the score of the gem.
				m_player.GetHealthComponent()->SetHealth(m_player.GetHealthComponent()->GetHealth() + dynamic_cast<Gem&>(item).m_health);
				m_player.GetAttackComponent()->SetMana(m_player.GetAttackComponent()->GetMana() + dynamic_cast<Gem&>(item).m_mana);

				m_gemSound.setRelativeToListener(true);
				m_gemSound.play();
			}
			break;

			case ITEM::KEY:
			{
				// Unlock the door.
				m_level.UnlockDoor();

				// Set the key as collected.
				//m_keyUiSprite->setColor(sf::Color::White);

				m_key.GetAudioComponent()->m_sound.play();
				m_key.GetAudioComponent()->m_sound.setPosition(playerPosition.x, 0.0f, playerPosition.y);
			}
			break;
			}

			// Finally, delete the object.
			itemIterator = m_items.erase(itemIterator);
		}
		else
		{
			// Increment iterator.
			++itemIterator;
		}
	}
}

// Updates all enemies in the level.
void Game::UpdateEnemies(sf::Vector2f playerPosition, float timeDelta)
{
	// Store player tile.
	Tile* playerTile = m_level.GetTile(m_player.GetPosition());

	auto enemyIterator = m_enemies.begin();
	while (enemyIterator != m_enemies.end())
	{
		// Create a bool so we can check if an enemy was deleted.
		bool enemyWasDeleted = false;

		// Get the enemy object from the iterator.
		Enemy& enemy = **enemyIterator;

		// Get the tile that the enemy is on.
		Tile* enemyTile = m_level.GetTile(enemy.GetPosition());

		// Check for collisions with projectiles.
		auto projectilesIterator = m_projectiles.begin();
		while (projectilesIterator != m_projectiles.end())
		{
			// Get the projectile object from the iterator.
			Projectile& projectile = **projectilesIterator;

			// If the enemy and projectile occupy the same tile they have collided.
			if (enemyTile == m_level.GetTile(projectile.GetPosition()))
			{
				// Delete the projectile.
				projectilesIterator = m_projectiles.erase(projectilesIterator);

				// Damage the enemy.
				enemy.GetHealthComponent()->TakeDamage(25);

				// If the enemy is dead remove it.
				if (enemy.GetHealthComponent()->IsDead())
				{

				// Delete enemy.
				enemyIterator = m_enemies.erase(enemyIterator);
				enemyWasDeleted = true;

				// Since the enemy is dead we no longer need to check projectiles.
				projectilesIterator = m_projectiles.end();
			}
		}
		else
		{
			// Move to the next projectile.
			++projectilesIterator;
			}
		}

		// If the enemy was not deleted, update it and increment the iterator.
		if (!enemyWasDeleted)
		{
			enemy.Update(timeDelta, m_level);
			++enemyIterator;
		}

		// Check for collision with player.
		if (enemyTile == playerTile)
		{
			if (m_player.GetHealthComponent()->CanTakeDamage()) {
					m_player.GetHealthComponent()->TakeDamage(10);
					m_player.GetAudioComponent()->m_sound.play();
					if (m_player.GetHealthComponent()->IsDead()) {
						m_gameState = GAME_STATE::GAME_OVER;
					}
			}
		}
	}
}

// Updates all projectiles in the level.
void Game::UpdateProjectiles(float timeDelta)
{
	for (std::vector<std::unique_ptr<Projectile>>::iterator it = m_projectiles.begin(); it != m_projectiles.end();) {
		(*it)->Update(timeDelta);
		if ((*it)->timeToDie >= 2.f) {
			it = m_projectiles.erase(it);
		}
		else {
			++it;
		}
	}
}

// Calculates the distance between two given points.
float Game::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
{
	return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
}

// Spawns a given object type at a random location within the map. Has the option to explicitly set a spawn location.
void Game::SpawnItem(std::string type, sf::Vector2f position)
{
	std::unique_ptr<GameObject> item;
	std::unique_ptr<Enemy> enemy;

	int objectIndex = 0;

	// Choose a random, unused spawn location.
	sf::Vector2f spawnLocation;

	if ((position.x >= 0.f) || (position.y >= 0.f))
		spawnLocation = position;
	else
		spawnLocation = m_level.GetRandomSpawnLocation();

	if (type == "enemy") {
		enemy = std::make_unique<Enemy>();
		enemy->SetPosition(spawnLocation);
		m_enemies.push_back(std::move(enemy));
	}
	else if (type == "Key") {
		item = std::make_unique<Key>();
		item->SetPosition(spawnLocation);
		m_items.push_back(std::move(item));
	}
	else {
		item = std::make_unique<Gem>();
		item->SetPosition(spawnLocation);
		m_items.push_back(std::move(item));
	}
}

// Draw the given string at the given position.
void Game::DrawString(std::string text, sf::Vector2f position, unsigned int size)
{
	// Clear the old data.
	m_stringStream.str(std::string());
	m_string.clear();

	m_stringStream << text;
	m_string = m_stringStream.str();

	m_text.setString(m_string);
	m_text.setFont(m_font);
	m_text.setCharacterSize(size);
	m_text.setPosition(position.x - (m_text.getLocalBounds().width / 2.f), position.y - (m_text.getLocalBounds().height / 2.f));

	m_window.GetRenderWindow()->draw(m_text);
}

// Draw the current game scene.
void Game::Draw(float timeDelta)
{
	// Clear the screen.
	m_window.GetRenderWindow()->clear(sf::Color(3, 3, 3, 225));		// Gray

													// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::PLAYING:
	{
		// Set the main game view.
		m_window.GetRenderWindow()->setView(m_views[static_cast<int>(VIEW::MAIN)]);

		// Draw the level.
		m_level.Draw(*m_window.GetRenderWindow(), timeDelta);

		// Draw all torches.
		for (auto& torch : m_torches)
		{
			torch->Draw(*m_window.GetRenderWindow(), timeDelta);
		}

		// Draw all objects.
		for (const auto& item : m_items)
		{
			item->Draw(*m_window.GetRenderWindow(), timeDelta);
		}

		// Draw all enemies.
		for (const auto& enemy : m_enemies)
		{
			enemy->Draw(*m_window.GetRenderWindow(), timeDelta);
		}

		// Draw all projectiles
		for (const auto& proj : m_projectiles)
		{
			//m_window.GetRenderWindow()->draw(proj->GetGraphicsComponent()->GetSprite());
			proj->Draw(*m_window.GetRenderWindow(), timeDelta);
		}

		// Draw the player.
		m_player.Draw(*m_window.GetRenderWindow(), timeDelta);

		// Switch to UI view.
		m_window.GetRenderWindow()->setView(m_views[static_cast<int>(VIEW::UI)]);

		// Draw the current room and floor.
		DrawString("Health: " + std::to_string(static_cast<int>(m_player.GetHealthComponent()->GetHealth())), sf::Vector2f(150.f, m_screenSize.y - 65.f), 25);
		DrawString("Mana: " + std::to_string(static_cast<int>(m_player.GetAttackComponent()->GetMana())), sf::Vector2f(150.f, m_screenSize.y - 30.f), 25);
	}
	break;
	}

	// Present the back-buffer to the screen.
	m_window.GetRenderWindow()->display();
}