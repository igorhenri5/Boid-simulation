#include <iostream>
#include <vector>
#include <string>
#include <GL/freeglut.h>

#include "simulation/Simulation.hpp"

#define WIDTHPX  1280
#define HEIGHTPX 720

Simulation* simulation;

void activeMouse(int button, int state, int x, int y){
	simulation->onActiveMouse(button, state, x, y);
}

void passiveMouse(int x, int y){
    // simulation.passiveMouse(x, y);
}

void activeKeyboard(unsigned char key, int x, int y){
	simulation->onActiveKeyboard(key, x, y);
}

void specialActiveKeyboard(int key, int x, int y){
	simulation->onSpecialKeyboard(key, x, y);
}

void screenReshape(int width, int height){
    simulation->onReshape(width, height);
}

void draw(){
    simulation->draw();
}

void update(){
    simulation->update();
}

void mainloop(){
    update();
    draw();
}

void initOpenGLEnvironment(int width, int height){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GLUT_MULTISAMPLE);

    glShadeModel(GL_SMOOTH);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.9, 0.9, 0.95, 1.0);

    glViewport(0, 0, width, height);
}

int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

    glutInitWindowSize(WIDTHPX,HEIGHTPX);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Boid Simulation");

    initOpenGLEnvironment(WIDTHPX,HEIGHTPX);
    simulation = new Simulation(WIDTHPX,HEIGHTPX);

    glutDisplayFunc(draw);
    glutMouseFunc(activeMouse);
    glutPassiveMotionFunc(passiveMouse);
	glutKeyboardFunc(activeKeyboard);
	glutSpecialFunc(specialActiveKeyboard);
    glutReshapeFunc(screenReshape);

    std::cout << "Starting Main Loop." << std::endl;
    glutIdleFunc(mainloop);
    // glutCloseFunc(onClose);

    glutMainLoop();

    return 0;
}
