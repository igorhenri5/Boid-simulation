#ifndef __BOIDGROUP__
#define __BOIDGROUP__

#include <glm/glm.hpp>
#include <vector>

#include "../entities/Boid.hpp"

class BoidGroup{
    public:
        BoidGroup(int);
        ~BoidGroup();

        int numBoids;
        std::vector<Boid*> boids;

        void update(glm::vec3 target);
        void draw();

        glm::vec3 calcBoidGroupCenter();
        glm::vec3 calcBoidGroupHeading();
        glm::vec3 calcBoidSeparation(std::vector<Boid*>::iterator);

        void addBoid();
        void removeBoid();
};

#endif