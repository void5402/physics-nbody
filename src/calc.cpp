#include "calc.hpp"
#include "configuration.hpp"
bool stop = false;
//barness hut algorithem in future/ Fast Multipole Method/quadtree or an octree/verlet integeration


void calculationsv1(std::vector<pt>& pts){
    uint32_t const size = pts.size();
    for(uint32_t i = 0; i<size; i++)
    {
        pt& part = pts[i];
        if(stop){continue;}
        sf::Vector2f tottalforce = {0.f,0.f};
        for (uint32_t j = i+1; j<size; j++)
        {
            pt& part2 = pts[j];
            sf::Vector2f distancev = part2.po - part.po;
            float distance = distancev.x * distancev.x + distancev.y * distancev.y;
            float distancesq = sqrtf(distance);
            float force = conf::G * part.mass * part2.mass / distance;
            sf::Vector2f normal = { distancev.x / distancesq, distancev.y / distancesq};
            tottalforce += force * normal;
            part2.fo -= force * normal;
        }
        sf::Vector2f acceleration = (tottalforce+part.fo)/part.mass;
        part.ve += acceleration;
        part.po += part.ve;
    }
}

void calcv2loop1(uint32_t const start, uint32_t const end, std::vector<pt>& pts, uint32_t const size){  
    for(uint32_t i = start; i<end; i++)
    {
        pt& part = pts[i];
        if(stop){continue;}
        sf::Vector2f tottalforce = {0.f,0.f};
        for (uint32_t j = i+1; j<size; j++)
        {
            pt& part2 = pts[j];
            sf::Vector2f distancev = part2.po - part.po;
            float distance = distancev.x * distancev.x + distancev.y * distancev.y;
            float distancesq = sqrtf(distance);
            float force = conf::G * part.mass * part2.mass / distance;
            sf::Vector2f normal = { distancev.x / distancesq, distancev.y / distancesq};
            part.fo += force * normal;
            part2.fo -= force * normal;
        }
    }
}

void calcv2loop2(uint32_t const start, uint32_t const end, std::vector<pt>& pts){
    for(uint32_t i = start; i<end; i++)
    {
        pt& part = pts[i];
        sf::Vector2f acceleration = (part.fo)/part.mass;
        part.ve += acceleration;
        part.po += part.ve;
    }
}

void calculationsv2(std::vector<pt>& pts) {
    uint32_t const size = pts.size();
    uint32_t const numThreads = std::thread::hardware_concurrency();
    uint32_t const chunkSize = size / numThreads;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        uint32_t start = i * chunkSize;
        uint32_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        threads.emplace_back([start, end, &pts, &size](){
            calcv2loop1(start, end, pts, size);});
    }
    
    if(stop){
    for (std::thread& thread : threads) {
        thread.join();
    }return;}

    for (int i = 0; i < numThreads; i++) {
        uint32_t start = i * chunkSize;
        uint32_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        threads.emplace_back([start, end, &pts](){
            calcv2loop2(start, end, pts);});
    }
    for (std::thread& thread : threads) {
        thread.join();
    }
}





