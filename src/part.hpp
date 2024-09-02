#pragma once
#include <SFML/System/Vector2.hpp>

struct pt{
    float mass = 1000000000000.0f;//(kg)
    float size = 1.0f;//size
    sf::Vector2f po;//ai said double is better for precision so maybe in future?
    sf::Vector2f ve;//velocity (m/s)
    sf::Vector2f fo;//force(s)(future optimizaion)
};