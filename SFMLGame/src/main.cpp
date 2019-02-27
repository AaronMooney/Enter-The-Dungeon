#include "Core.hpp"
#include "Game.hpp"
#include "Menu.hpp"

// Entry point of the application.
int main()
{
	// Set a random seed.
	srand(static_cast<unsigned int>(time(nullptr)));

	Game game;

	Menu menu(game.GetWindow()->GetWindowSize().x, game.GetWindow()->GetWindowSize().y);
	game.GetWindow()->GetRenderWindow()->clear();

	while (!game.GetWindow()->IsDone()) {
		if (game.m_gameState == GAME_STATE::MAIN_MENU || game.m_gameState == GAME_STATE::GAME_OVER) {
			game.m_isRunning = true;
			sf::Event event;

			while (game.GetWindow()->GetRenderWindow()->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							game.m_gameState = GAME_STATE::PLAYING;
							break;
						case 1:
							game.GetWindow()->SetDone(true);
							break;
						}
						break;
					case sf::Event::Closed:
						game.GetWindow()->SetDone(true);

						break;

					case sf::Keyboard::Escape:
						game.GetWindow()->SetDone(true);
						break;
					}

				}

				menu.draw(*game.GetWindow()->GetRenderWindow());

				game.GetWindow()->GetRenderWindow()->display();

			}
			if (game.m_gameState == GAME_STATE::PLAYING) {
				game.Initialize();
				game.Run();
			}
		}
	}

	// Exit the application.
	return 0;
}