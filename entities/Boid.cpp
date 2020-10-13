#include "Boid.hpp"

Boid::Boid(glm::vec3 position, glm::vec3 color){   
    this->position = position;
    this->color = color;
        // this->color*=1.5f;
}

void Boid::draw(){
    //o pombo é um cubo mesmo
    glBegin(GL_QUADS);
        // top
        glColor3f(this->color.x, this->color.y, this->color.z);
        // glNormal3f(0.0f + this->position.x, 1.0f + this->position.y, 0.0f + this->position.z);
        glNormal3f(0, 1, 0);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // front
        glColor3f(this->color.x, this->color.y, this->color.z);
        // glNormal3f(0.0f + this->position.x, 0.0f + this->position.y, 1.0f + this->position.z);
        glNormal3f(1, 0, 0);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // right
        glColor3f(this->color.x, this->color.y, this->color.z);
        // glNormal3f(1.0f + this->position.x, 0.0f + this->position.y, 0.0f + this->position.z);
        glNormal3f(0, 0, 1);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // left
        glColor3f(this->color.x, this->color.y, this->color.z);
        // glNormal3f(-1.0f + this->position.x, 0.0f + this->position.y, 0.0f + this->position.z);
        glNormal3f(0, 1, -1);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, 0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // bottom
        glColor3f(this->color.x, this->color.y, this->color.z);
        // glNormal3f(0.0f + this->position.x, -1.0f + this->position.y, 0.0f + this->position.z);
        glNormal3f(0, -1, 0);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, 0.5f + this->position.z);
        glVertex3f(-0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
        glVertex3f(0.5f + this->position.x, -0.5f + this->position.y, -0.5f + this->position.z);
    glEnd();
        
    glBegin(GL_QUADS);
        // back
        glColor3f(this->color.x, this->color.y, this->color.z);
        // glNormal3f(0.0f + this->position.x, 0.0f + this->position.y, -1.0f + this->position.z);
        glNormal3f(-1, 0, 0);
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

void Boid::update(glm::vec3 target){
    // Compute target component
    glm::vec3 targetComp = (target - position);
    targetComp = Util::normalize(targetComp, 1.5);

    myStep(
        glm::vec3(0,0,0), // Separation Component
        glm::vec3(0,0,0), // Alignment Component
        glm::vec3(0,0,0), // Cohesion Component
        targetComp,       // Target Component
        glm::vec3(0,0,0), // Floor Component
        glm::vec3(0,0,0)  // Tower Component
    );
}


void Boid::update(glm::vec3 separation, glm::vec3 boidGroupVelocity,
                  glm::vec3 center, glm::vec3 target){
    // Compute alignment component
    glm::vec3 heading = getHeading();
    glm::vec3 alignmentComp = (boidGroupVelocity - heading);

    // Compute cohesion component
    glm::vec3 cohesionComp = (center - position);
    cohesionComp = Util::normalize(cohesionComp, 2.5);

    // Compute separation component
    glm::vec3 separationComp = separation;

    // Compute target component
    glm::vec3 targetComp = (target - position);
    targetComp = Util::normalize(targetComp, 1.5);

    // Compute floor component
    glm::vec3 floorComp = glm::vec3(0, 1, 0);
    floorComp *= Util::normNegSigmoid(position.y, 1.5);

    // Compute tower component
    glm::vec3 towerComp(0,0,0);
    if(position.y < 25){
        towerComp = position - glm::vec3(0, position.y, 0);
        towerComp *= Util::normalizeNeg(towerComp, 5);
        towerComp *= 10;
    }

    // Step in
    myStep(separationComp, alignmentComp, cohesionComp, targetComp, floorComp, towerComp);
}


void Boid::myStep(glm::vec3 separationComp, glm::vec3 alignmentComp, glm::vec3 cohesionComp, glm::vec3 targetComp, glm::vec3 floorComp, glm::vec3 towerComp){

    glm::vec3 heading = getHeading();

    // Some factors
    float alignmentFactor = 1;
    float cohesionFactor = 1;
    float separationFactor = 1;
    float targetFactor = 1;
    float floorFactor = 1;
    float towerFactor = 1;
    float sumOfFactors = (
        alignmentFactor + cohesionFactor + separationFactor +
        targetFactor + floorFactor + towerFactor
    );

    // Apply factors the the components
    alignmentComp *= alignmentFactor;
    cohesionComp *= cohesionFactor;
    separationComp *= separationFactor;
    targetComp *= targetFactor;
    floorComp *= floorFactor;
    towerComp *= towerFactor;

    // Compute resulting Velocity and speed
    glm::vec3 velocity = separationComp + alignmentComp + cohesionComp + targetComp + floorComp + towerComp;
    velocity /= sumOfFactors;
    speed = glm::length(velocity);

    // Update the heading
    // H' = <H + <V>>
    if (glm::length(glm::cross(heading, velocity)) < 0.0001) velocity += 0.0001;
    glm::vec3 newHeading = Util::normalize(heading + Util::normalize(velocity));

    // Ensure Max Speed
    double MaxSpeed = 10.0;
    // double MaxSpeed = 5.0 / 60;
    // double MaxSpeed = 5.0 / s_FPS;
    if (speed > MaxSpeed) speed = MaxSpeed;

    // Update position
    glm::vec3 step = newHeading;
    step *= speed;
    position += step;

    // Compute angleX
    angleX = glm::asin(newHeading.y);

    // Compute angleY
    glm::vec3 newHeadProjXZ = newHeading * glm::vec3(1,0,1);
    glm::vec3 headProjXZ = heading * glm::vec3(1,0,1);
    if (glm::length(glm::cross(newHeadProjXZ, headProjXZ)) < 0.0001){
        headProjXZ.x += 0.0001;
        headProjXZ.z += 0.0001;
    }

    double turnAngle = Util::computeAngle(newHeadProjXZ, headProjXZ);
    
    if (glm::cross(newHeadProjXZ, headProjXZ).y < 0){
        angleY -= turnAngle* PI / 180;
    }
    else{
        angleY += turnAngle* PI / 180;
    }
    if (angleY > 2*PI) angleY -= 2*PI;
    if (angleY < 0) angleY += 2*PI;

    // Compute Z Axis Rotation Angle (Roll or bank)
    double curveAngle = turnAngle * 10;
    angleZ = curveAngle / 180 * 90; // Cap max roll at 90 degrees
    angleZ = angleZ/180*PI;

}
