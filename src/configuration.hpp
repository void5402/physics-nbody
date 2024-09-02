#pragma once
//#include <SFML/Window.hpp>

extern float zoom;
extern sf::Vector2f viewlocation;
extern sf::Vector2f newpt;
extern bool stop;

namespace conf
{
sf::Vector2u const window_size = {1366u, 768u};
sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
uint32_t const max_framerate = 30;
float const dt = 1.0f / static_cast<float>(max_framerate);
uint32_t const start_count = 4000;
float const G = 6.67430*1e-11f;
float const mv = 5.0f;

}