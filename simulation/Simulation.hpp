#ifndef __SIMULATION__
#define __SIMULATION__

#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include <vector>

#include "../entities/Boid.hpp"
#include "../util/Util.hpp"

#define FRAMETIME 1000/60

class Simulation{
    public:
        Simulation(int, int);
    
    //Camera e visão
        enum CameraPresets{
            ABOVE_TOWER,
            BEHIND_BOIDS,
            PERPENDICULAR_SPEED,
            TOP_VIEW
        };

        CameraPresets cameraPreset;
        
        glm::vec3 center;
        glm::vec3 up;
        glm::vec3 eye;

        float aspectRatio;
        int cameraOffset;
        // const float DELTA_ANGLE = Util::PI / 36;

    //Chão
        glm::vec4 floorColor;
        glm::mat4 floorPos;

    //Torre
        int towerHeight;

    //Boids
        int numBoids;
        std::vector<Boid*> boids;
        Boid* leader;

    //Status
        bool isPaused = false;

        void init();
        void update();
        void draw();

        void onReshape(int, int);
        void onActiveKeyboard(int, int, int);
        void onActiveMouse(int, int, int, int);
};


#endif