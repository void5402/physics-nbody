#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "events.hpp"
#include "configuration.hpp"
#include "part.hpp"
#include "calc.hpp"
#include <stdint.h>
#ifndef _Float32
typedef float _Float32;
#endif


using namespace std;

float zoom = 2.5f;
sf::Vector2f viewlocation = conf::window_size_f * 0.5f;
sf::Vector2f newpt = {0.f,0.f};
vector<pt> createpoints(uint32_t count)
{
    vector<pt> pts;
    pts.reserve(count);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<_Float32> dis(0.f,1.f);
    for(uint32_t i{count};i--;){
        pt part;
        float const x = (dis(gen)-0.5f)*conf::window_size_f.x;
        float const y = (dis(gen)-0.5f)*conf::window_size_f.y;
        part.po.x = x;
        part.po.y = y;
        pts.push_back(part);
    }
    return pts;
};


int main(){
    
    vector<pt> pts = createpoints(conf::start_count);
    
    sf::RenderWindow window( {conf::window_size.x,conf::window_size.y}, "SFML Project" );
    window.setFramerateLimit(conf::max_framerate);
    sf::Vector2f ve = {1.f,1.f};

    while (window.isOpen())
    {
        proccessevents(window);
        if(newpt.x != 0.f){pt part; part.po = newpt; pts.push_back(part); newpt = {0.f,0.f};}
        calculations(pts);
        window.clear(sf::Color::Black);
        sf::RectangleShape c;
        
        for(pt const& part : pts)
        {
	        c.setSize(max(part.size,1.5f)*ve*2.f);
            c.setOrigin(part.size,part.size);
            c.setPosition(part.po/zoom + viewlocation);
	        window.draw(c);
        }
        window.display();
    }
}
