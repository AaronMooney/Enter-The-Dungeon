#include "Gem.hpp"
#include "AssetManager.hpp"

Gem::Gem() {
	m_graphics = std::make_shared<ItemGraphicsComponent>("resources/loot/gem/spr_pickup_gem.png");
}