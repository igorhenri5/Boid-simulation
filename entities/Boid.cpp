#include "Boid.hpp"

Boid::Boid(glm::vec3 position){   
    this->position = position;
    // this->color = glm::vec3(1.0f,.5f,1.0f);
}

void Boid::draw(){
    //o pombo é um cubo mesmo
    glBegin(GL_QUADS);
        // top
        glColor3f(2.0f,2.0f,2.0f);
        glNormal3f(0.0f + this->position.x, 1.0f + this->position.y, 0.0f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // front
        glColor3f(2.0f,2.0f,2.0f);
        glNormal3f(0.0f + this->position.x, 0.0f + this->position.y, 1.0f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // right
        glColor3f(2.0f,2.0f,2.0f);
        glNormal3f(1.0f + this->position.x, 0.0f + this->position.y, 0.0f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // left
        glColor3f(2.0f,2.0f,2.0f);
        glNormal3f(-1.0f + this->position.x, 0.0f + this->position.y, 0.0f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // bottom
        glColor3f(2.0f,2.0f,2.0f);
        glNormal3f(0.0f + this->position.x, -1.0f + this->position.y, 0.0f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // back
        glColor3f(2.0f,2.0f,2.0f);
        glNormal3f(0.0f + this->position.x, 0.0f + this->position.y, -1.0f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
	glEnd();
}

glm::vec3 Boid::getHeading(){
    glm::vec3 heading;
    heading.x = glm::cos(angleX)*glm::sin(angleY);
    heading.y = glm::sin(angleX);
    heading.z = -glm::cos(angleX)*glm::cos(angleY);
    return (heading);
}

glm::vec3 Boid::computeSeparation(Boid* boid){
    // Compute the separation between the two boids
    glm::vec3 sep = (boid->position - this->position);

    // Normalize it by a distance factor
    sep = Util::normalizeNeg(sep, 2.5);

    // Normalize it and return
    return -sep;
}

void Boid::rotatePitch(double degrees){
    angleX += degrees/180*PI;
    if (angleX > PI/2) angleX = PI/2;
    if (angleX < -PI/2) angleX = -PI/2;
}

void Boid::rotateYaw(double degrees){
    angleY += degrees/180*PI;
    if (angleX > PI*2) angleX -= 2*PI;
    if (angleX < 0) angleX += 2*PI;
}

void Boid::update(){
    glm::vec3 target = getHeading();
    target *= speed;

    myStep(
        glm::vec3(0,0,0), // Separation Component
        glm::vec3(0,0,0), // Alignment Component
        glm::vec3(0,0,0), // Cohesion Component
        target,           // Target Component
        glm::vec3(0,0,0), // Floor Component
        glm::vec3(0,0,0)  // Tower Component
    );
}

void Boid::myStep(glm::vec3 separationComp, glm::vec3 alignmentComp, glm::vec3 cohesionComp, glm::vec3 targetComp, glm::vec3 floorComp, glm::vec3 towerComp){

}
