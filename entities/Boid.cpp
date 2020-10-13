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
        // glColor4f(1.0, 1.0, 0.0, 0.0);
        glColor3f(this->color.x+0.1, this->color.y+0.1, this->color.z+0.1);

        norm =
        glm::cross(glm::vec3(-neckSize/2, neckSize/2, headHeight),
                   glm::vec3(neckSize/2, neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(-neckSize/2, -neckSize/2, headHeight),
                   glm::vec3(-neckSize/2, neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(neckSize/2, neckSize/2, headHeight),
                   glm::vec3(neckSize/2, -neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(neckSize/2, -neckSize/2, headHeight),
                   glm::vec3(-neckSize/2, -neckSize/2, headHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0, 0.0,-(1.0));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));
    glEnd();

    // Draw Body
    glBegin(GL_TRIANGLES);
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(1.0, 1.0, 0.0);

        norm =
        glm::cross(glm::vec3(neckSize/2, neckSize/2, -bodyHeight),
                   glm::vec3(-neckSize/2, neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(0.0, 0.0, 1.0);
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(1.0, 1.0, 0.0);

        norm =
        glm::cross(glm::vec3(-neckSize/2, -neckSize/2, -bodyHeight),
                   glm::vec3(neckSize/2, -neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(-neckSize/2, neckSize/2, -bodyHeight),
                   glm::vec3(-neckSize/2, -neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(-neckSize/2,-neckSize/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(neckSize/2, neckSize/2, -bodyHeight),
                   glm::vec3(neckSize/2, -neckSize/2, -bodyHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(neckSize/2,neckSize/2,-(1-headHeight));
        glVertex3f(neckSize/2,-neckSize/2,-(1-headHeight));
    glEnd();


    // Draw Tail
    glBegin(GL_TRIANGLES);
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(1.0, 0.5, 0.0);

        norm =
        glm::cross(glm::vec3(-tailLength/2, tailWidth/2, tailHeight),
                   glm::vec3(tailLength/2, tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

        norm =
        glm::cross(glm::vec3(tailLength/2, tailWidth/2, tailHeight),
                   glm::vec3(tailLength/2, -tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

        norm =
        glm::cross(glm::vec3(tailLength/2, -tailWidth/2, tailHeight),
                   glm::vec3(-tailLength/2, -tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(-tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

        norm =
        glm::cross(glm::vec3(-tailLength/2, -tailWidth/2, tailHeight),
                   glm::vec3(-tailLength/2, tailWidth/2, tailHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(-tailLength/2,-tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));
        glVertex3f(-tailLength/2,tailWidth/2,-(1-headHeight-bodyHeight-tailHeight));

    glEnd();

    // Draw Right Wing
    glBegin(GL_TRIANGLES);
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(0.2, 1.0, 0.0);

        norm =
        glm::cross(glm::vec3(neckSize/2-wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                   glm::vec3(neckSize/2-wingTipFlapX, wingWidth/2-wingTipFlapZ,-bodyHeight+wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(neckSize/2,-wingWidth/2,-(1-headHeight));
        glVertex3f(neckSize/2,wingWidth/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(-wingTipFlapX, -wingTipFlapZ, wingTipHeight),
                   glm::vec3(neckSize/2-wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
        glVertex3f(neckSize/2,-wingWidth/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(neckSize/2-wingTipFlapX, wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                   glm::vec3(-wingTipFlapX, -wingTipFlapZ, wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(neckSize/2,wingWidth/2,-(1-headHeight));
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));
    glEnd();

    // Draw Left Wing
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(this->color.x, this->color.y, this->color.z);
        //glColor3f(0.2, 1.0, 0.0);

        norm =
        glm::cross(glm::vec3(-neckSize/2+wingTipFlapX, wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                   glm::vec3(-neckSize/2+wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(-wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(-neckSize/2,wingWidth/2,-(1-headHeight));
        glVertex3f(-neckSize/2,-wingWidth/2,-(1-headHeight));

        norm =
        glm::cross(glm::vec3(-neckSize/2+wingTipFlapX, -wingWidth/2-wingTipFlapZ, -bodyHeight+wingTipHeight),
                   glm::vec3(wingTipFlapX, -wingTipFlapZ, wingTipHeight));
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(-wingTipFlapX,wingTipFlapZ,-(1-headHeight-bodyHeight+wingTipHeight));
        glVertex3f(-neckSize/2,-wingWidth/2,-(1-headHeight));
        glVertex3f(0.0,0.0,-(1.0-headHeight-bodyHeight));

        norm =
        glm::cross(glm::vec3(wingTipFlapX, -wingTipFlapZ, wingTipHeight),
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
    // double MaxSpeed = 10.0;
    double MaxSpeed = 5.0 / 60;
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

    // When not in a steep curve, flap the wings
    if(glm::abs(curveAngle) < 60.0){
        // flapTick += 2*PI / (s_FPS);
        flapTick += 2*PI / 60;
    }

    // Update the wing tip position
    float angleVariation = glm::cos(flapFactor*flapTick + flapPhase);
    float currAngle = 30.0/180*PI * angleVariation;
    wingTipFlapX = wingLength * glm::cos(currAngle);
    wingTipFlapZ = wingLength * glm::sin(currAngle);
}
