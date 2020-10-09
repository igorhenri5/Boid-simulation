#ifndef __SIMULATION__
#define __SIMULATION__

#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include <vector>

#include "../entities/BoidGroup.hpp"
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

    //Chão
        glm::vec4 floorColor;
        glm::mat4 floorPos;

    //Torre
        int towerHeight;

    //Boids
        int numBoids;
        BoidGroup* boids;
        Boid* guide;

        enum GuideModes{
            RANDOM_POSITION,
            CIRCLE,
            FREE_MOTION
        };

        GuideModes guideMode;
        glm::vec3 guideGoal;
        int lastUpdated;

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