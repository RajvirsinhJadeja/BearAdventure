#pragma once

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <queue>

class Obstacle
{
	public:
		Obstacle();
		void update(float speed);
		sf::Sprite getSprite();
		void restart();
		void render(sf::RenderWindow &window);

	private:
		sf::Clock birdAnimationClock;

		sf::Texture logTexture;
		sf::Texture logDoubleTexture;
		sf::Texture birdTexture;

		std::queue<sf::Sprite> obstacles;

		int randNum;
		int cycle = 0;
};

#endif