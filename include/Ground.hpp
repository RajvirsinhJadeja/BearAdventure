#pragma once

#ifndef GROUND_HPP
#define GROUND_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Ground
{
	public:
		Ground();
		void update(float deltaTime);
		float& getSpeed();
		void restart();
		void render(sf::RenderWindow &window);

	private:
		sf::Texture tileTexture;
		std::vector<sf::Sprite> tiles;
		sf::Clock fadeClock;
		float elapsedTime;
		float tileWidth;
		float speed;
		int specialTile;
};

#endif