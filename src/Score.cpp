#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

#include "Score.hpp"

Score::Score() : score(0) 
{
    if (!scoreFont.loadFromFile("resources/fonts/ThaleahFat.ttf"))
    {
        std::cerr << "Error: Could not load ThaleahFat.ttf" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    sf::Color customOutlineColor(0, 0, 0, 255);
    sf::Color customFillColor(237, 177, 117, 255);

    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(35);
    scoreText.setOutlineThickness(3);
    scoreText.setOutlineColor(customOutlineColor);
    scoreText.setFillColor(customFillColor);
    scoreText.setPosition(880, 10);

}

void Score::update(float deltaTime, float speed)
{
    score = static_cast<int>(-speed * deltaTime);
}

int Score::getScore()
{
    return score;
}

void Score::restart()
{
    score = 0;
}

void Score::render(sf::RenderWindow& window) 
{
    std::string pText = "Score: " + std::to_string(score);
    scoreText.setString(pText);
    window.draw(scoreText);
}
