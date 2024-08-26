#include "Collision.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

std::vector<std::vector<bool>> Collision::getPixelMask(const sf::Sprite& sprite)
{
	const sf::Texture* texture = sprite.getTexture();
	sf::Image image = texture->copyToImage();
	sf::IntRect textureRect = sprite.getTextureRect();

	std::vector<std::vector<bool>> mask(textureRect.width, std::vector<bool>(textureRect.height, false));

	for (int x = 0; x < textureRect.width; ++x)
	{
		for (int y = 0; y < textureRect.height; ++y)
		{
			sf::Color pixelColor = image.getPixel(textureRect.left + x, textureRect.top + y);

			if (pixelColor.a > 0)
			{
				mask[x][y] = true;
			}
		}
	}

	return mask;
}

bool Collision::pixelPerfectCollision(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    sf::FloatRect intersection;
    if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds(), intersection))
    {
        std::vector<std::vector<bool>> mask1 = getPixelMask(sprite1);
        std::vector<std::vector<bool>> mask2 = getPixelMask(sprite2);

        sf::Vector2f pos1 = sprite1.getPosition();
        sf::Vector2f pos2 = sprite2.getPosition();

        sf::Vector2f scale1 = sprite1.getScale();
        sf::Vector2f scale2 = sprite2.getScale();

        int startX = static_cast<int>(intersection.left);
        int startY = static_cast<int>(intersection.top);
        int endX = static_cast<int>(intersection.left + intersection.width);
        int endY = static_cast<int>(intersection.top + intersection.height);

        for (int x = startX; x < endX; ++x)
        {
            for (int y = startY; y < endY; ++y)
            {
                int x1 = static_cast<int>((x - pos1.x) / scale1.x);
                int y1 = static_cast<int>((y - pos1.y) / scale1.y);
                int x2 = static_cast<int>((x - pos2.x) / scale2.x);
                int y2 = static_cast<int>((y - pos2.y) / scale2.y);

                if (x1 >= 0 && y1 >= 0 && x1 < mask1.size() && y1 < mask1[0].size() && x2 >= 0 && y2 >= 0 && x2 < mask2.size() && y2 < mask2[0].size())
                {
                    if (mask1[x1][y1] && mask2[x2][y2])
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}