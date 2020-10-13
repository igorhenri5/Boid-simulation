#ifndef __BOID__
#define __BOID__

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "../util/Util.hpp"

class Boid{
    public:
        Boid();

        Boid(glm::vec3, glm::vec3);
        ~Boid();

        glm::vec3 position;
        glm::vec3 color;
        
        void update();
        void update(glm::vec3);
        void update(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

        void draw();

        float speed;
        float angleX;
        float angleY;
        float angleZ;

        glm::vec3 getHeading();
        glm::vec3 computeSeparation(Boid*);

        void rotateYaw(double);
        void rotatePitch(double);
        void myStep(glm::vec3 separationComp, glm::vec3 alignmentComp, glm::vec3 cohesionComp, glm::vec3 targetComp, glm::vec3 floorComp, glm::vec3 towerComp);

};

#endif