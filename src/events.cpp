#include "events.hpp"


void proccessevents(sf::Window& window)
{
    for (auto event = sf::Event{}; window.pollEvent(event);)//event handeling
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
		else if  (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
            if (event.key.code == sf::Keyboard::Space)
			{
				stop = !stop;
			}
		}
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            float mouseX = (event.mouseWheelScroll.x - viewlocation.x) * zoom;
            float mouseY = (event.mouseWheelScroll.y - viewlocation.y) * zoom;
            zoom += (zoom/10)*event.mouseWheelScroll.delta*-1;
            viewlocation.x = event.mouseWheelScroll.x - mouseX / zoom;
            viewlocation.y = event.mouseWheelScroll.y - mouseY / zoom;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f ml = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                newpt = (ml-viewlocation)*zoom;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        viewlocation.y += conf::mv;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        viewlocation.y -= conf::mv;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        viewlocation.x += conf::mv;//yes this is correct
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        viewlocation.x -= conf::mv;
    }
}