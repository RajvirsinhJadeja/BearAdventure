#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player() : cycle(0), action(0), isJumping(false), jumpSpeed(0.0f)
{
    if (!bearRunningTexture.loadFromFile("resources/images/bearRunning.png"))
    {
        std::cerr << "Error: Could not load bearRunning.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    bearRunningSprite.setTexture(bearRunningTexture);
    bearRunningSprite.setScale(6, 6);
    bearRunningSprite.setPosition(75, 834 - (bearRunningSprite.getGlobalBounds().height));
    bearRunningSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    if (!bearDuckingTexture.loadFromFile("resources/images/bearDucking.png"))
    {
        std::cerr << "Error: Could not load bearDucking.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    bearDuckingSprite.setTexture(bearDuckingTexture);
    bearDuckingSprite.setScale(5.5, 5.5);
    bearDuckingSprite.setPosition(90, 834 - (bearDuckingSprite.getGlobalBounds().height));
    bearDuckingSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    if (!bearJumpingTexture.loadFromFile("resources/images/bearJumping.png"))
    {
        std::cerr << "Error: Could not load bearJumping.png" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    bearJumpingSprite.setTexture(bearJumpingTexture);
    bearJumpingSprite.setScale(6, 6);
    bearJumpingSprite.setPosition(75, 834 - (bearJumpingSprite.getGlobalBounds().height));
    bearJumpingSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));

    if (!runSound.loadSound("resources/audio/runSound.wav"))
    {
        std::cerr << "Error: Could not load runSound.wav" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    runSound.setSoundVolume(30);

    if (!jumpSound.loadSound("resources/audio/jumpSound.wav"))
    {
        std::cerr << "Error: Could not load jumpSound.wav" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    jumpSound.setSoundVolume(100);

    if (!landingSound.loadSound("resources/audio/landingSound.wav"))
    {
        std::cerr << "Error: Could not load landingSound.wav" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    landingSound.setSoundVolume(12);
}

void Player::update(int action)
{
    this->action = action;
    float frameTime = bearAnimationClock.getElapsedTime().asSeconds();

    const float jumpHeight = -15.0f;
    const float gravity = 1.0f;

    if (action == 1 && isJumping == false)
    {
        isJumping = true;
        jumpSpeed = jumpHeight;
        bearJumpingSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
        jumpSound.playSound();
    }

    if (isJumping)
    {
        bearJumpingSprite.move(0, jumpSpeed);
        jumpSpeed += gravity;

        if (jumpSpeed > 0)
        {
            bearJumpingSprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
        }

        if (bearJumpingSprite.getPosition().y > 660)
        {
            bearJumpingSprite.setPosition(75, 660);
            isJumping = false;
            landingSound.playSound();
        }
    }
    else
    {
        if (frameTime >= 1.0f / 12.0f)
        {
            bearAnimationClock.restart();
            if (cycle % 2 == 0)
                runSound.playSound();

            if (action == 0)
            {
                bearRunningSprite.setTextureRect(sf::IntRect(32 * cycle, 0, 32, 32));
                cycle = (cycle + 1) % 4;
            }
            else if (action == 2)
            {
                bearDuckingSprite.setTextureRect(sf::IntRect(32 * cycle, 0, 32, 32));
                cycle = (cycle + 1) % 4;
            }
            
        }
    }
}

sf::Sprite Player::getSprite()
{
    if (isJumping)
    {
        return bearJumpingSprite;
    }
    else
    {
        if (action == 0)
            return bearRunningSprite;
        if (action == 2)
            return bearDuckingSprite;
    }

    return sf::Sprite();
}

void Player::restart()
{
    cycle = 0;
    action = 0;

    isJumping = false;
    jumpSpeed = 0.0f;

    bearRunningSprite.setPosition(75, 834 - (bearRunningSprite.getGlobalBounds().height));
    bearRunningSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    bearDuckingSprite.setPosition(90, 834 - (bearDuckingSprite.getGlobalBounds().height));
    bearDuckingSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    bearJumpingSprite.setPosition(75, 834 - (bearJumpingSprite.getGlobalBounds().height));
    bearJumpingSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));

    bearAnimationClock.restart();
}

void Player::render(sf::RenderWindow& window)
{
    if (isJumping)
    {
        window.draw(bearJumpingSprite);
    }
    else
    {
        if (action == 0)
            window.draw(bearRunningSprite);
        if (action == 2)
            window.draw(bearDuckingSprite);
    }
}