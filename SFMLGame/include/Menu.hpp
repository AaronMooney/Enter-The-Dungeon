#ifndef Menu_hpp
#define Menu_hpp
#include "Core.hpp"

#define MAX_NUMBER_OF_ITEMS 2

class Menu
{
public:
	Menu(float width, float height);
	~Menu() {}

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
private:
	int selectedItemIndex;
	sf::Text title;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};
#endif 

