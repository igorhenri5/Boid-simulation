#include "Simulation.hpp"
#include <iostream>

Simulation::Simulation(int width, int height){   
    aspectRatio = (float) width / (float) height;
    this->init();
}

void Simulation::init(){
    towerHeight = 50;
    cameraPreset = ABOVE_TOWER;
    cameraOffset = 0;

    guide = new Boid(glm::vec3(100,20,100), glm::vec3(2.0f,0.2f,1.5f));
    boids = new BoidGroup(5);

    //Guide inicia em trajetória circular ao redor da torre
    guideMode = CIRCLE;
    lastUpdated = 0;
}

void Simulation::update(){
    //camera
    if(cameraPreset == ABOVE_TOWER){
        eye = glm::vec3(0, towerHeight + cameraOffset, 0);
        up = glm::vec3(0,1,0);
        center = guide->position;
    }
    else if(cameraPreset == BEHIND_BOIDS){
        up = glm::vec3(0,1,0);
        glm::vec3 dist = boids->calcBoidGroupHeading();
        dist *= 5+(cameraOffset/10);
        eye = boids->calcBoidGroupCenter() - dist;
        center = boids->calcBoidGroupCenter();
    }
    else if(cameraPreset == PERPENDICULAR_SPEED){
        up = glm::vec3(0,1,0);
        glm::vec3 vetor = glm::cross(up, boids->calcBoidGroupHeading());
        vetor /= glm::length(vetor);
        vetor *= 15+(cameraOffset/10);
        eye = boids->calcBoidGroupCenter() - vetor;
        center = boids->calcBoidGroupCenter();

    }
    else if(cameraPreset == TOP_VIEW){
        eye = glm::vec3(0, towerHeight + 10 + cameraOffset, 0);
        up = glm::vec3(0,0,-1);
        center = glm::vec3(0, 0, 0);
    }

    if(isPaused) return;

    //boids
    if(guideMode == RANDOM_POSITION){
        int current = (int) glutGet(GLUT_ELAPSED_TIME)/1000;
        if(lastUpdated != current && current % 10 == 0){
            guideGoal.x = Util::getRandom() * 40 - 20;
            guideGoal.y = Util::getRandom() * 20;
            guideGoal.z = Util::getRandom() * 40 - 20;
            lastUpdated = current;
        }
        guide->update(guideGoal);
    }
    else if(guideMode == CIRCLE){
        guideGoal = glm::vec3(50, 10, 50);
        guideGoal.x *= glm::cos(glutGet(GLUT_ELAPSED_TIME)/1000 * PI / 10);
        guideGoal.z *= -glm::sin(glutGet(GLUT_ELAPSED_TIME)/1000 * PI / 10);
        guide->update(guideGoal);
    }
    else{
        guide->update();
    }

    glm::vec3 guideHeading = guide->getHeading();
    guideHeading *= 5;
    boids->update(guide->position - guideHeading);
}

void Simulation::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

    //Projecao perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, this->aspectRatio, 1.6, FAR);
    glMatrixMode(GL_MODELVIEW);

    //Boid guia
    guide->draw();

    //Grupo de Boids
    boids->draw();

    //Torre
    glBegin(GL_TRIANGLE_FAN);
        glColor4f(.2f, .1f, 1.0f, 1.0f);
        glNormal3f(0, 1, 0);
        glVertex3f(0, towerHeight, 0);

        int sides = 64;
        float anglePerSide = 2*PI/(float)sides;
        for(int i=0; i <= sides; i++){
            float angle = i*anglePerSide;
            glm::vec3 pos (glm::cos(angle)*2, 0, -glm::sin(angle)*2);
            glNormal3f(pos.x, 0, pos.z);
            glVertex3f(pos.x, pos.y, pos.z);
        }
    glEnd();

    //Chão
    glBegin(GL_QUADS);
        glColor4f(.1f, 0.75f, 0.1f, 1.0);
        glNormal3f(0, 1, 0);
        glVertex3f(eye.x-FAR, 0, eye.z+FAR);
        glVertex3f(eye.x-FAR, 0, eye.z-FAR);
        glVertex3f(eye.x+FAR, 0, eye.z-FAR);
        glVertex3f(eye.x+FAR, 0, eye.z+FAR);
    glEnd();

    unsigned int GridSizeX = 64;
	unsigned int GridSizeZ = 64;
	unsigned int SizeX = 2;
	unsigned int SizeZ = 2;

    glutSwapBuffers();
}

void Simulation::onReshape(int width, int height){
    // std::cout << "reshape event" << std::endl;
    glViewport(0,0, width, height);
    this->aspectRatio = (float) width / (float) height;
}

void Simulation::onActiveKeyboard(int key, int x, int  y){
    // std::cout << "Key pressed:: " << key << std::endl;
    switch(key){
        case '1':
            std::cout << "Camera mode changed Above-Tower" << std::endl;
            cameraPreset = ABOVE_TOWER;
            break;
        case '2':
            std::cout << "Camera mode changed Behind-Boids" << std::endl;
            cameraPreset = BEHIND_BOIDS;
            break;
        case '3':
            std::cout << "Camera mode changed Perpendicular-Speed" << std::endl;
            cameraPreset = PERPENDICULAR_SPEED;
            break;
        case '4':
            std::cout << "Camera mode changed Top-View" << std::endl;
            cameraPreset = TOP_VIEW;
            break;
        case '+':
            std::cout << "Add Boid" << std::endl;
            boids->addBoid();
            break;
        case '-':
            std::cout << "Remove Boid" << std::endl;
            boids->removeBoid();
            break;        
        case 'q':
        case 'Q':
            //quit
            exit(1);
        case 'r':
            std::cout << int(Util::getRandom()*100) << std::endl;
            break;
        case 'p':
        case 'P':
            if(isPaused) isPaused = false;
            else isPaused = true;
            break;
        default:
            break;
    }
}

void Simulation::onSpecialKeyboard(int key, int x, int y){
    const float DELTA_ANGLE = PI / 36;
    // std::cout << "SPECIAL KEY " << key << std::endl;
    switch(key){
        case GLUT_KEY_F1:
            guideMode = RANDOM_POSITION;
            std::cout << "Guide movement mode changed to RANDOM_POSITION" << std::endl;
            break;
        case GLUT_KEY_F2:
            guideMode = CIRCLE;
            std::cout << "Guide movement mode changed to CIRCLE" << std::endl;
            break;
        default:
        break;
    }
}

void Simulation::onActiveMouse(int button, int state, int x, int y){
    // std::cout << "OAM :: " << button << " "<< state << std::endl;
    if(button == 3){
        cameraOffset-=2;
    }else if(button == 4){
        cameraOffset+=2;
    }
}