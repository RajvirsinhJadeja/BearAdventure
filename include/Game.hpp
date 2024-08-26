#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Ground.hpp"
#include "Score.hpp"
#include "Collision.hpp"
#include "GameAudio.hpp"
#include <vector>

class Game
{
	public:
		Game();
		void run();
		void processEvents();
		void update();
		void restart();
		void render();

	private:
		sf::RenderWindow window;
		sf::Event evnt;

		Ground ground;
		Score score;
		Obstacle obstacle;
		Player player;
		Collision collision;
		GameAudio menuMusic;
		GameAudio gameMusic;
		GameAudio endMusic;
		GameAudio hitLog;

		bool isFading = false;
		bool isGameClockStarted = false;
		bool endMusicPlayed = false;
		int action = 0;

		sf::Clock fadeClock;
		sf::Clock gameClock;

		sf::Font font;
		sf::Text titleText;
		sf::Text controlsText;

		sf::Text gameOverText;
		sf::Text scoreText;
		sf::Text playAgainText;

		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;

		sf::Texture keyTexture;

		sf::Sprite upArrowSprite;
		sf::Sprite downArrowSprite;
		sf::Sprite rSprite;
		sf::Sprite eSprite;

		sf::Texture bearTexture;
		sf::Sprite bearSprite;

		enum GameState
		{
			TitleScreen,
			GameOn,
			GameOver
		};
		GameState gameState;

		void initTitleScreen();
		void fadeTitleScreen();
		void displayGameOver();
};

#endif