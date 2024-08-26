#pragma once

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class Obstacle;

class Collision
{
public:
    static std::vector<std::vector<bool>> getPixelMask(const sf::Sprite &sprite);

    static bool pixelPerfectCollision(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
    
};

#endif