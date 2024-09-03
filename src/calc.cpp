#include "calc.hpp"
#include "configuration.hpp"
bool stop = false;
//barness hut algorithem in future/ Fast Multipole Method/quadtree or an octree/verlet integeration


void calculationsv1(std::vector<pt>& pts){
    uint32_t const size = pts.size();
    for(uint32_t i = 0; i<size; i++)
    {
        pt& part = pts[i];
        part.size = log10f(part.mass)/2/zoom;
        if(stop){continue;}
        sf::Vector2f tottalforce = {0.f,0.f};
        for (uint32_t j = i+1; j<size; j++)
        {
            pt& part2 = pts[j];
            sf::Vector2f distancev = part2.po - part.po;
            float distance = distancev.x * distancev.x + distancev.y * distancev.y;
            float force = conf::G * part.mass * part2.mass / distance;
            sf::Vector2f normal = { distancev.x / sqrtf(distance), distancev.y / sqrtf(distance) };
            tottalforce += force * normal;
            part2.fo -= force * normal;
        }
        sf::Vector2f acceleration = (tottalforce+part.fo)/part.mass;
        part.ve += acceleration;
        part.po += part.ve;
    }
}


calculations_func calculations = calculationsv1;