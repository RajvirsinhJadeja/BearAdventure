#include <SFML/Graphics.hpp>
#include <queue>
#include <cmath>
#include <iostream>

#include "Obstacle.hpp"

Obstacle::Obstacle() 
{
    if (!logTexture.loadFromFile("resources/images/log.png"))
    {
        std::cerr << "Error: Could not load log.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if (!logDoubleTexture.loadFromFile("resources/images/log2x.png"))
    {
        std::cerr << "Error: Could not load log2x.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if (!birdTexture.loadFromFile("resources/images/bird.png"))
    {
        std::cerr << "Error: Could not load bird.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    sf::Sprite logSprite;
    logSprite.setTexture(logTexture);
    logSprite.setScale(3, 3);
    logSprite.setPosition(1176, 738);

    obstacles.push(logSprite);
}

void Obstacle::update(float speed)
{
    if (obstacles.front().getPosition().x < -192)
    {
        obstacles.pop();

        randNum = (rand() % 3) + 1;

        sf::Sprite logSprite;
        sf::Sprite logDoubleSprite;
        sf::Sprite birdSprite;

        switch (randNum)
        {
        case 1:
            logSprite.setTexture(logTexture);
            logSprite.setScale(3, 3);
            logSprite.setPosition(1176, 738);
            obstacles.push(logSprite);
            break;
        case 2:
            logDoubleSprite.setTexture(logDoubleTexture);
            logDoubleSprite.setScale(3, 3);
            logDoubleSprite.setPosition(1176, 738);
            obstacles.push(logDoubleSprite);
            break;
        case 3:
            birdSprite.setTexture(birdTexture);
            birdSprite.setScale(5, 5);
            birdSprite.setPosition(1176, 607);
            birdSprite.setTextureRect(sf::IntRect(32 * 0, 0, 32, 32));
            obstacles.push(birdSprite);
            break;
        }
    }

    if (randNum == 3)
    {
        float frameTime = birdAnimationClock.getElapsedTime().asSeconds();

        if (frameTime >= 1.0f/12.0f)
        {
            birdAnimationClock.restart();

            obstacles.front().setTextureRect(sf::IntRect(32 * cycle, 0, 32, 32));

            cycle = (cycle + 1) % 4;
        }
    }

    if (!obstacles.empty())
        obstacles.front().move(speed, 0);
}

sf::Sprite Obstacle::getSprite()
{
    return obstacles.front();
}

void Obstacle::restart()
{
    while (!obstacles.empty())
    {
        obstacles.pop();
    }

    randNum = 0;
    cycle = 0;
    birdAnimationClock.restart();

    sf::Sprite logSprite;
    logSprite.setTexture(logTexture);
    logSprite.setScale(3, 3);
    logSprite.setPosition(1176, 738);
    obstacles.push(logSprite);
}

void Obstacle::render(sf::RenderWindow &window) 
{
    window.draw(obstacles.front());
}
