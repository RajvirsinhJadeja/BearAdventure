#pragma once

#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>
#include "Ground.hpp"

class Score
{
	public:
		Score();
		void update(float deltaTime, float speed);
		int getScore();
		void restart();
		void render(sf::RenderWindow &window);
	
	private:
		int score;
		sf::Font scoreFont;
		sf::Text scoreText;
};

#endif 