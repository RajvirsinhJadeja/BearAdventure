#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "GameAudio.hpp"

class Player
{
	public:
		Player();
		void update(int action);
		sf::Sprite getSprite();
		void restart();
		void render(sf::RenderWindow &window);

	private:
		sf::Texture bearRunningTexture;
		sf::Sprite bearRunningSprite;

		sf::Texture bearDuckingTexture;
		sf::Sprite bearDuckingSprite;

		sf::Texture bearJumpingTexture;
		sf::Sprite bearJumpingSprite;

		sf::Clock bearAnimationClock;
		sf::Clock jumpClock;

		int cycle;
		int action;
		bool isJumping;
		float jumpSpeed;

		GameAudio runSound;
		GameAudio jumpSound;
		GameAudio landingSound;
};

#endif