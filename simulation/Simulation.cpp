#include "Simulation.hpp"
#include <iostream>

Simulation::Simulation(int width, int height){   
    aspectRatio = (float) width / (float) height;
    this->init();
}

void Simulation::init(){

    towerHeight = 50;
    cameraPreset = TOP_VIEW;
    cameraOffset = 0;

    this->floorColor =  glm::vec4(1.0, 1.0, 0.0, 1.0);
    this->floorPos   =  glm::mat4(
                                    -10.0, 0.0, 10.0, 1.0,
                                    -10.0, 0.0, -10.0, 1.0,
                                    10.0, 0.0, -10.0, 1.0,
                                    10.0, 0.0, 10.0, 1.0
                                 );

}
void Simulation::update(){

    if(cameraPreset == ABOVE_TOWER){
        eye = glm::vec3(0, towerHeight + cameraOffset, 0);
        up = glm::vec3(0,1,0);
        center = glm::vec3(0, 0, 0);
    }
    else if(cameraPreset == BEHIND_BOIDS){
            eye = glm::vec3(80+cameraOffset, 25, 0);
            up = glm::vec3(0,1,0);
            center = glm::vec3(0, 25, 0);
    }
    else if(cameraPreset == PERPENDICULAR_SPEED){
            eye = glm::vec3(100+cameraOffset, 10, 0);
            up = glm::vec3(0,1,0);
            center = glm::vec3(0, 5, 0);
    }
    else if(cameraPreset == TOP_VIEW){
        eye = glm::vec3(0, towerHeight + 10 + cameraOffset, 0);
        up = glm::vec3(0,0,-1);
        center = glm::vec3(0, 0, 0);
    }
}

void Simulation::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

    //Luz
    GLfloat lightPos[] = {5.0, 5.0, 5.0, 1.0f};
    GLfloat ltAmbColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat ltDifColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat ltSpeColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ltAmbColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ltDifColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ltSpeColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    //Projecao perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(60.0, this->aspectRatio, 1.6, 100);
    gluPerspective(60.0, this->aspectRatio, 1.6, 500);
    glMatrixMode(GL_MODELVIEW);

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

    // Chão
    glBegin(GL_QUADS);
        glColor4f(.1f, 0.75f, 0.1f, 1.0);
        glNormal3f(0, 1, 0);
        glVertex3f(eye.x-500, 0, eye.z+500);
        glVertex3f(eye.x-500, 0, eye.z-500);
        glVertex3f(eye.x+500, 0, eye.z-500);
        glVertex3f(eye.x+500, 0, eye.z+500);
    glEnd();

    unsigned int GridSizeX = 64;
	unsigned int GridSizeZ = 64;
	unsigned int SizeX = 2;
	unsigned int SizeZ = 2;

    glutSwapBuffers();
}

void Simulation::onReshape(int width, int height){
    std::cout << "reshape event" << std::endl;
    glViewport(0,0, width, height);
    this->aspectRatio = (float) width / (float) height;
}

void Simulation::onActiveKeyboard(int key, int x, int  y){
    std::cout << "Key pressed:: " << key << std::endl;
    switch(key){
        case '1':
            std::cout << "Camera mode changed AT" << std::endl;
            cameraPreset = ABOVE_TOWER;
            break;
        case '2':
            std::cout << "Camera mode changed BB" << std::endl;
            cameraPreset = BEHIND_BOIDS;
            break;
        case '3':
            std::cout << "Camera mode changed PS" << std::endl;
            cameraPreset = PERPENDICULAR_SPEED;
            break;
        case '4':
            std::cout << "Camera mode changed TV" << std::endl;
            cameraPreset = TOP_VIEW;
            break;
        case 'q':
        case 'Q':
            //quit
            exit(1);
        case 'r':
        case 'R':
            //reset
            // init();
        break;
    default:
        break;
    }
}

void Simulation::onActiveMouse(int button, int state, int x, int y){
    std::cout << "OAM :: " << button << " "<< state << std::endl;
    if(button == 3){
        // if(cameraOffset > -100)
        cameraOffset-=2;
    }else if(button == 4){
        // if(cameraOffset < 100)
        cameraOffset+=2;
    }
}