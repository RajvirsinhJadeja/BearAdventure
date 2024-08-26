#include "Ground.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>

Ground::Ground() : tileWidth(32.0f * 3.0f), speed(-0.1f), specialTile(0)
{
    if (!tileTexture.loadFromFile("resources/images/Tiles.png"))
    {
        std::cerr << "Error: Could not load Tiles.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int numTiles = 1080 / static_cast<int>(tileWidth) + 2;

    for (int i = -2; i < numTiles; i++)
    {
        sf::Sprite tile(tileTexture);
        tile.setScale(3, 3);
        tile.setTextureRect(sf::IntRect(0, 0, 32, 32));
        tile.setPosition(i * tileWidth, 804);
        tiles.push_back(tile);
    }
}

void Ground::update(float deltaTime)
{
    if (deltaTime < 30)
    {
        speed = (-(1.0f/3.0f) * deltaTime) - 15;
    }
    else
    {
        speed = -25;
    }
    for (sf::Sprite& tile : tiles)
    {
        tile.move(speed, 0.0);
    }

    if (tiles.front().getPosition().x + tileWidth < (tileWidth * -1))
    {
        specialTile = specialTile + 1;

        float newX = tiles.back().getPosition().x + tileWidth;
        sf::Sprite newTile(tileTexture);
        newTile.setPosition(newX, 804);
        newTile.setScale(3, 3);
        tiles.push_back(newTile);

        tiles.erase(tiles.begin());
        tiles.shrink_to_fit();

        if (specialTile == 7)
        {
            int index = (rand() % 3) + 1;
            switch (index)
            {
            case 1:
                tiles.back().setTextureRect(sf::IntRect(32, 0, 32, 32));
                specialTile = 0;
                break;
            case 2:
                tiles.back().setTextureRect(sf::IntRect(64, 0, 32, 32));
                specialTile = 0;
                break;
            case 3:
                tiles.back().setTextureRect(sf::IntRect(96, 0, 32, 32));
                specialTile = 0;
                break;
            }
        }
        else
        {
            tiles.back().setTextureRect(sf::IntRect(0, 0, 32, 32));
        }
    }
}

float& Ground::getSpeed()
{
    return speed;
}

void Ground::restart()
{
    tiles.clear();

    speed = -0.1f;
    specialTile = 0;

    int numTiles = 1080 / static_cast<int>(tileWidth) + 2;

    for (int i = -2; i < numTiles; i++)
    {
        sf::Sprite tile(tileTexture);
        tile.setScale(3, 3);
        tile.setTextureRect(sf::IntRect(0, 0, 32, 32));
        tile.setPosition(i * tileWidth, 804);
        tiles.push_back(tile);
    }
}


void Ground::render(sf::RenderWindow &window)
{
    for (const sf::Sprite &tile : tiles)
    {
        window.draw(tile);
    }
}
