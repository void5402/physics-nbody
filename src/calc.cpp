#include "calc.hpp"
#include "configuration.hpp"

bool stop = false;
void calculations(std::vector<pt>& pts){
    uint32_t const size = pts.size();
    for(uint32_t i = 0; i<size; i++)
    {
        pt& part = pts[i];
        //size
        part.size = log10f(part.mass)/2/zoom;
        if(stop){continue;}
        //calc totall force f = g*m1*m2*(1/r^2)
        sf::Vector2f tottalforce = {0.f,0.f};
        for (uint32_t j = i+1; j<size; j++)
        {
            pt& part2 = pts[j];
            sf::Vector2f distancev = part2.po - part.po;
            float distance = hypot(distancev.x,distancev.y);
            //if (distance == 0){continue;}
            float force = conf::G * part.mass * part2.mass / pow(distance,2);
            sf::Vector2f normal = {distancev.x/distance,distancev.y/distance};
            tottalforce += force * normal;
            part2.fo -= force * normal;
        }
        //calc asseleration a = F/m
        sf::Vector2f acceleration = (tottalforce+part.fo)/part.mass;
        //add asseleration to velocity
        part.ve += acceleration;
        //add velocity to x and y
        part.po += part.ve;
    }
}