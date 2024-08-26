#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Ground.hpp"
#include "Score.hpp"
#include "Collision.hpp"
#include "GameAudio.hpp"


Game::Game() : window(sf::VideoMode(1080, 900), "Bear Adventure", sf::Style::Titlebar | sf::Style::Close)
{
    gameState = TitleScreen;
    window.setFramerateLimit(60);
    initTitleScreen();
}

void Game::initTitleScreen()
{
    if (!backgroundTexture.loadFromFile("resources/images/background.png"))
    {
        std::cerr << "Error: Could not load background.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    backgroundSprite.setTexture(backgroundTexture);

    if (!keyTexture.loadFromFile("resources/images/keys.png"))
    {
        std::cerr << "Error: Could not load keys.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    upArrowSprite.setTexture(keyTexture);
    upArrowSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    upArrowSprite.setScale(7, 7);
    upArrowSprite.setPosition(400, 395);

    downArrowSprite.setTexture(keyTexture);
    downArrowSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
    downArrowSprite.setScale(7, 7);
    downArrowSprite.setPosition(400, 545);

    upArrowSprite.setColor(sf::Color(255, 255, 255, 255));
    downArrowSprite.setColor(sf::Color(255, 255, 255, 255));

    if (!font.loadFromFile("resources/fonts/ThaleahFat.ttf"))
    {
        std::cerr << "Error: Could not load ThaleahFat.ttf" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    sf::Color customOutlineColor(0, 0, 0, 255);
    sf::Color customFillColor(237, 177, 117, 255);

    titleText.setString("Bear Adventure");
    titleText.setFont(font);
    titleText.setCharacterSize(130);
    titleText.setOutlineThickness(10.0f);
    titleText.setOutlineColor(customOutlineColor);
    titleText.setFillColor(customFillColor);
    titleText.setPosition((float)(window.getSize().x - titleText.getLocalBounds().width) / 2.0f, 125.0f);

    controlsText.setString("Jump\n\nDuck");
    controlsText.setFont(font);
    controlsText.setCharacterSize(75);
    controlsText.setOutlineThickness(5.77f);
    controlsText.setOutlineColor(customOutlineColor);
    controlsText.setFillColor(customFillColor);
    controlsText.setPosition(540, 388.5f);

    if (!bearTexture.loadFromFile("resources/images/bearStanding.png"))
    {
        std::cerr << "Error: Could not load bearStanding.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    bearSprite.setTexture(bearTexture);
    bearSprite.setScale(6, 6);
    bearSprite.setPosition(75, 834 - (bearSprite.getGlobalBounds().height));

    if (!menuMusic.loadMusic("resources/audio/menuMusic.ogg"))
    {
        std::cerr << "Error: Could not load menuMusic.ogg" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    menuMusic.setLoop(true);
    menuMusic.setMusicVolume(30);
    menuMusic.playMusic();
    endMusic.stopMusic();

    if (!gameMusic.loadMusic("resources/audio/gameMusic.ogg"))
    {
        std::cerr << "Error: Could not load gameMusic.ogg" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    gameMusic.setLoop(true);
    gameMusic.setMusicVolume(30);

    if (!hitLog.loadSound("resources/audio/hitLog.wav"))
    {
        std::cerr << "Error: Could not load hitLog.wav" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    hitLog.setSoundVolume(5);
}

void Game::run()
{
    while(window.isOpen()) 
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (window.pollEvent(evnt))
    {
        if (evnt.type == sf::Event::Closed)
        {
            window.close();
        }

        action = 0;

        if (evnt.type == sf::Event::KeyPressed)
        {
            if (evnt.key.code == sf::Keyboard::Up || evnt.key.code == sf::Keyboard::Down)
            {
                if (gameState == TitleScreen && isFading == false)
                {
                    isFading = true;
                    fadeClock.restart();
                }
                if (gameState == GameOn)
                {
                    if (evnt.key.code == sf::Keyboard::Up)
                    {
                        action = 1;
                    }
                    else if (evnt.key.code == sf::Keyboard::Down)
                    {
                        action = 2;
                    }
                }
            }
            if (evnt.key.code == sf::Keyboard::R || evnt.key.code == sf::Keyboard::E)
            {
                if (gameState == GameOver)
                {
                    if (evnt.key.code == sf::Keyboard::R)
                    {
                        Game::restart();
                        gameState = TitleScreen;
                        Game::initTitleScreen();
                    }
                    else if (evnt.key.code == sf::Keyboard::E)
                    {
                        window.close();
                    }
                }
            }
        }
    }
}

void Game::update()
{
    if (isFading)
    {
        fadeTitleScreen();
    }
    else if (gameState == GameOn)
    {
        if (isGameClockStarted == false)
        {
            gameClock.restart();
            isGameClockStarted = true;
        }
        float deltaTime = gameClock.getElapsedTime().asSeconds();
        ground.update(deltaTime);
        score.update(deltaTime, ground.getSpeed());
        obstacle.update(ground.getSpeed());
        player.update(action);

        if (collision.pixelPerfectCollision(player.getSprite(), obstacle.getSprite()) == true)
        {
            hitLog.playSound();
            gameState = GameOver;
        }
    }
    else if (gameState == GameOver)
    {
        gameMusic.stopMusic();
        Game::displayGameOver();
    }
}

void Game::fadeTitleScreen()
{
    float fadeDuration = 2.0f;
    float elapsed = fadeClock.getElapsedTime().asSeconds();
    float fadeColor = 255.0f * (1.0f - elapsed / fadeDuration);
    float fadeVolume = 30.0f * (1.0f - elapsed / fadeDuration);

    if (fadeColor < 0)
    {
        fadeColor = 0;

    }
    if (fadeVolume < 0)
    {
        fadeVolume = 0;
    }

    titleText.setOutlineColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeColor)));
    controlsText.setOutlineColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeColor)));

    titleText.setFillColor(sf::Color(237, 177, 117, static_cast<sf::Uint8>(fadeColor)));
    controlsText.setFillColor(sf::Color(237, 177, 117, static_cast<sf::Uint8>(fadeColor)));

    upArrowSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(fadeColor)));
    downArrowSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(fadeColor)));

    menuMusic.setMusicVolume(fadeVolume);

    if (fadeColor == 0 && fadeVolume == 0)
    {
        menuMusic.stopMusic();
        gameMusic.playMusic();
        gameState = GameOn;
        isFading = false;
    }
}

void Game::render()
{
    window.clear(sf::Color::White);

    if(gameState == TitleScreen)
    {
        window.draw(backgroundSprite);
        window.draw(upArrowSprite);
        window.draw(downArrowSprite);
        window.draw(titleText);
        window.draw(controlsText);
        ground.render(window);
        window.draw(bearSprite);
    }
    else if(gameState == GameOn)
    {
        window.draw(backgroundSprite);
        ground.render(window);
        score.render(window);
        obstacle.render(window);
        player.render(window);
    }
    else if(gameState == GameOver)
    {
        window.draw(backgroundSprite);
        ground.render(window);
        obstacle.render(window);
        player.render(window);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(rSprite);
        window.draw(eSprite);
        window.draw(playAgainText);
    }

    window.display();
}

void Game::displayGameOver()
{
    sf::Color customOutlineColor(0, 0, 0, 255);
    sf::Color customFillColor(237, 177, 117, 255);

    gameOverText.setString("Game Over!");
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(170);
    gameOverText.setOutlineThickness(10);
    gameOverText.setOutlineColor(customOutlineColor);
    gameOverText.setFillColor(customFillColor);
    gameOverText.setPosition((float)(window.getSize().x - gameOverText.getLocalBounds().width) / 2.0f, 50);

    std::string printScore = "Score: " + std::to_string(score.getScore());
    scoreText.setString(printScore);
    scoreText.setFont(font);
    scoreText.setCharacterSize(75);
    scoreText.setOutlineThickness(5.77f);
    scoreText.setOutlineColor(customOutlineColor);
    scoreText.setFillColor(customFillColor);
    scoreText.setPosition((float)(window.getSize().x - scoreText.getLocalBounds().width) / 2.0f, 260);

    rSprite.setTexture(keyTexture);
    rSprite.setTextureRect(sf::IntRect(16, 16 * 4, 16, 16));
    rSprite.setScale(7, 7);
    rSprite.setPosition(400, 420);

    eSprite.setTexture(keyTexture);
    eSprite.setTextureRect(sf::IntRect(16 * 4, 16 * 2, 16, 16));
    eSprite.setScale(7, 7);
    eSprite.setPosition(400, 570);

    rSprite.setColor(sf::Color(255, 255, 255, 255));
    eSprite.setColor(sf::Color(255, 255, 255, 255));

    playAgainText.setString("Play Again\n\nExit");
    playAgainText.setFont(font);
    playAgainText.setCharacterSize(75);
    playAgainText.setOutlineThickness(5.77f);
    playAgainText.setOutlineColor(customOutlineColor);
    playAgainText.setFillColor(customFillColor);
    playAgainText.setPosition(540, 420);

    if (!endMusicPlayed)
    {
        if (!endMusic.loadMusic("resources/audio/endMusic.ogg"))
        {
            std::cerr << "Error: Could not load endMusic.ogg" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        endMusic.setLoop(true);
        endMusic.setMusicVolume(30);
        endMusic.playMusic();
        endMusicPlayed = true;
    }
}

void Game::restart()
{
    score.restart();
    ground.restart();
    obstacle.restart();
    player.restart();
    gameClock.restart();
    isGameClockStarted = false;
    endMusicPlayed = false;
}
