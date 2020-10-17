#include "Boid.hpp"

Boid::Boid(glm::vec3 position, glm::vec3 color){   
    this->position = position;
    this->color = color;

    this->angleX = 0;
    this->angleY = 0;
    this->angleZ = 0; 

    this->neckSize = 0.3 * 2;
    this->headHeight = 0.3 * 2;
    this->bodyHeight = 0.5 * 2;
    this->tailHeight = 0.2 * 2;
    this->tailWidth = 0.05 * 2;
    this->tailLength = 0.3 * 2;
    this->wingWidth = 0.05 * 2;
    this->wingLength = 0.7 * 2;
    this->wingTipHeight = 0.2 * 2;
    this->wingTipFlapX = 0.7 * 2;
    this->wingTipFlapZ = 0;
    this->flapPhase = Util::getRandom()*PI;
    this->flapFactor = 1 + Util::getRandom();
    this->flapTick = 0;
}

void Boid::draw(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(angleX * 180 / PI, 1, 0, 0);
    glRotatef(-angleY * 180 / PI, 0, 1, 0);
    glRotatef(angleZ * 180 / PI, 0, 0, 1);

    float boidSpec[] = {0.1, 0.1, 0.1, 1.0};
    float boidEmis[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, boidSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, boidEmis);
    glm::vec3 norm;

    // Draw Head
    glBegin(GL_TRIANGLES);
        glColor3f(this->color.x+0.1, this->color.y+0.1, this->color.z+0.1);

        norm =  glm::cross(glm::vec3(-neckSize/2, neckSize/2, headHeight),
                           glm::vec3(neckSize/2, neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(-neckSize/2, -neckSize/2, headHeight),
                           glm::vec3(-neckSize/2, neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(neckSize/2, neckSize/2, headHeight),
                           glm::vec3(neckSize/2, -neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(neckSize/2, -neckSize/2, headHeight),
                           glm::vec3(-neckSize/2, -neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));
    glEnd();

    // Draw Body
    glBegin(GL_TRIANGLES);
        glColor3f(this->color.x, this->color.y, this->color.z);

        norm =  glm::cross(glm::vec3(neckSize/2, neckSize/2, -bodyHeight),
                           glm::vec3(-neckSize/2, neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(0.0, 0.0, 1.0);
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(1.0, 1.0, 0.0);

        norm =  glm::cross(glm::vec3(-neckSize/2, -neckSize/2, -bodyHeight),
                           glm::vec3(neckSize/2, -neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(-neckSize/2, neckSize/2, -bodyHeight),
                           glm::vec3(-neckSize/2, -neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(neckSize/2, neckSize/2, -bodyHeight),
                           glm::vec3(neckSize/2, -neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));
    glEnd();


    // Draw Tail
    glBegin(GL_TRIANGLES);
        glColor3f(this->color.x, this->color.y, this->color.z);

        norm =  glm::cross(glm::vec3(-tailLength/2, tailWidth/2, tailHeight),
                           glm::vec3(tailLength/2, tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

        norm =  glm::cross(glm::vec3(tailLength/2, tailWidth/2, tailHeight),
                           glm::vec3(tailLength/2, -tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

        norm =  glm::cross(glm::vec3(tailLength/2, -tailWidth/2, tailHeight),
                           glm::vec3(-tailLength/2, -tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(-tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

        norm =  glm::cross(glm::vec3(-tailLength/2, -tailWidth/2, tailHeight),
                           glm::vec3(-tailLength/2, tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(-tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

    glEnd();

    // Draw Right Wing
    glBegin(GL_TRIANGLES);
        glColor3f(this->color.x, this->color.y, this->color.z);

        norm =  glm::cross(glm::vec3(neckSize/2-wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                           glm::vec3(neckSize/2-wingTipFlapX, wingWidth/2-wingTipFlapZ,-bodyHeight+wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(neckSize/2,-wingWidth/2,-(1-headHeight));
        glVertex3f(neckSize/2,wingWidth/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(-wingTipFlapX, -wingTipFlapZ, wingTipHeight),
                           glm::vec3(neckSize/2-wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(neckSize/2,-wingWidth/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(neckSize/2-wingTipFlapX, wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                           glm::vec3(-wingTipFlapX, -wingTipFlapZ, wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(neckSize/2,wingWidth/2,-(1-headHeight));
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
    glEnd();

    // Draw Left Wing
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(this->color.x, this->color.y, this->color.z);

        norm =  glm::cross(glm::vec3(-neckSize/2+wingTipFlapX, wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                           glm::vec3(-neckSize/2+wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(-wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(-neckSize/2,wingWidth/2,-(1-headHeight));
        glVertex3f(-neckSize/2,-wingWidth/2,-(1-headHeight));

        norm =  glm::cross(glm::vec3(-neckSize/2+wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                           glm::vec3(wingTipFlapX, -wingTipFlapZ, wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(-wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(-neckSize/2,-wingWidth/2,-(1-headHeight));
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));

        norm =  glm::cross(glm::vec3(wingTipFlapX, -wingTipFlapZ, wingTipHeight),
                           glm::vec3(-neckSize/2+wingTipFlapX, wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(-wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-neckSize/2,wingWidth/2,-(1-headHeight));
    glEnd();

    glPopMatrix();
}


glm::vec3 Boid::getHeading(){
    glm::vec3 heading;
    heading.x = glm::cos(angleX)*glm::sin(angleY);
    heading.y = glm::sin(angleX);
    heading.z = -glm::cos(angleX)*glm::cos(angleY);
    return (heading);
}

glm::vec3 Boid::computeSeparation(Boid* boid){
    // Calcula e normaliza a separação para um outro bodi
    glm::vec3 sep = (boid->position - this->position);
    return -(Util::normalizeNeg(sep, 2.5));
}

//Mecanismos de Banking
void Boid::rotatePitch(double degrees){
    this->angleX += degrees/180*PI;
    if (this->angleX > PI/2) this->angleX = PI/2;
    if (this->angleX < -PI/2) this->angleX = -PI/2;
}

void Boid::rotateYaw(double degrees){
    this->angleY += degrees/180*PI;
    if (this->angleY > PI*2) this->angleY -= 2*PI;
    if (this->angleY < 0) this->angleY += 2*PI;
}

void Boid::rotateRoll(double degrees){
    this->angleZ = degrees / 180 * 90; 
    this->angleZ = this->angleZ/180*PI;
}


void Boid::update(){
    //objetivo
    glm::vec3 target = getHeading();
    target *= speed;

    moveStep(
        glm::vec3(0,0,0), // Separation Component
        glm::vec3(0,0,0), // Alignment Component
        glm::vec3(0,0,0), // Cohesion Component
        target,           // Target Component
        glm::vec3(0,0,0), // Floor Component
        glm::vec3(0,0,0)  // Tower Component
    );
}

void Boid::update(glm::vec3 target){
    //objetivo
    glm::vec3 targetComp = (target - position);
    targetComp = Util::normalize(targetComp, 1.5);

    moveStep(
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
   
   // Lida com as 3 regras principais
    // alinhamento
    glm::vec3 heading = getHeading();
    glm::vec3 alignmentComp = (boidGroupVelocity - heading);

    // coesão
    glm::vec3 cohesionComp = (center - position);
    cohesionComp = Util::normalize(cohesionComp, 2.5);

    // separação
    glm::vec3 separationComp = separation;

   // Lida com o objetivo e outros objetos do mundo
    // objetivo
    glm::vec3 targetComp = (target - position);
    targetComp = Util::normalize(targetComp, 1.5);

    // chão
    glm::vec3 floorComp = glm::vec3(0, 1, 0);
    floorComp *= Util::normNegSigmoid(position.y, 1.5);

    // torre
    glm::vec3 towerComp(0,0,0);
    if(position.y < 25){
        towerComp = position - glm::vec3(0, position.y, 0);
        towerComp *= Util::normalizeNeg(towerComp, 5);
        towerComp *= 10;
    }

    moveStep(separationComp, alignmentComp, cohesionComp, targetComp, floorComp, towerComp);
}

void Boid::moveStep(glm::vec3 separationComp, glm::vec3 alignmentComp, glm::vec3 cohesionComp, glm::vec3 targetComp, glm::vec3 floorComp, glm::vec3 towerComp){
    // Passo para caminhar em direção ao objetivo

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
    if (glm::length(  glm::cross(heading, velocity)) < 0.0001) velocity += 0.0001;
        glm::vec3 newHeading = Util::normalize(heading + Util::normalize(velocity));

    // Ensure Max Speed
    double MaxSpeed = 5.0 / 60;
    if (speed > MaxSpeed) speed = MaxSpeed;

    // Update position
    glm::vec3 step = newHeading;
    step *= speed;
    position += step;

    // Compute angleX
    angleX = glm::asin(newHeading.y);
// rotateYaw(turnAngle)

    // Compute angleY
    glm::vec3 newHeadProjXZ = newHeading * glm::vec3(1,0,1);
    glm::vec3 headProjXZ = heading * glm::vec3(1,0,1);
    if(glm::length(  glm::cross(newHeadProjXZ, headProjXZ)) < 0.0001){
        headProjXZ.x += 0.0001;
        headProjXZ.z += 0.0001;
    }

    double turnAngle = Util::computeAngle(newHeadProjXZ, headProjXZ);
// rotateYaw(turnAngle)
    if(glm::cross(newHeadProjXZ, headProjXZ).y < 0)
        angleY -= turnAngle* PI / 180;
    else
        angleY += turnAngle* PI / 180;  
          
    if(angleY > 2*PI) angleY -= 2*PI;
    if(angleY < 0) angleY += 2*PI;

    // Compute Z Axis Rotation Angle (Roll or bank)
    double curveAngle = turnAngle * 10;
// rotateRoll(curveAngle);
    angleZ = curveAngle / 180 * 90; // Cap max roll at 90 degrees
    angleZ = angleZ/180*PI;

    // Wing animation
    if(glm::abs(curveAngle) < 60.0){
        flapTick += 2*PI / 60;
    }

    float angleVariation = glm::cos(flapFactor*flapTick + flapPhase);
    float currAngle = 30.0/180*PI * angleVariation;
    wingTipFlapX = wingLength * glm::cos(currAngle);
    wingTipFlapZ = wingLength * glm::sin(currAngle);
}
