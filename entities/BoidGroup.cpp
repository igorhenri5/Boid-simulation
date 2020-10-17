#include "BoidGroup.hpp"
#include <iostream>

BoidGroup::BoidGroup(int numBoids){
    this->numBoids = 0;
    for(int i=0; i<numBoids; i++){
        addBoid();        
    }
};

void BoidGroup::update(glm::vec3 target){
    glm::vec3 separation;
    glm::vec3 boidGroupHeading = calcBoidGroupHeading();
    glm::vec3 center = calcBoidGroupCenter();

    for(auto boid = boids.begin(); boid != boids.end(); boid++){
        separation = calcBoidSeparation(boid);
        (*boid)->update(separation, boidGroupHeading, center, target);
    }
}

void BoidGroup::draw(){
    for (std::vector<Boid*>::iterator it = boids.begin(); it != boids.end(); ++it) {
        (*it)->draw();
    }
}

//Calculo da separação entre os boids do grupo
glm::vec3 BoidGroup::calcBoidSeparation(std::vector<Boid*>::iterator it){
    glm::vec3 separation(0,0,0);
    for(auto boid = boids.begin(); boid != boids.end(); boid++){
        if(boid == it) continue;
        separation += (*it)->computeSeparation(*boid);
    }
    return separation;
}

//Tira a média entre a direção+sentido dos boids do grupo
glm::vec3 BoidGroup::calcBoidGroupHeading(){
    glm::vec3 heading(0,0,0);
    for (auto boid = boids.begin(); boid != boids.end(); boid++){
        heading += (*boid)->getHeading();
    }
    heading /= boids.size();
    return heading;
}

//Define o ponto central do grupo
glm::vec3 BoidGroup::calcBoidGroupCenter(){
    glm::vec3 center(0,0,0);
    for (auto boid = boids.begin(); boid != boids.end(); boid++){
        center += (*boid)->position;
    }
    center /= boids.size();
    return center;
}

void BoidGroup::addBoid(){
    boids.push_back(new Boid(glm::vec3(int(Util::getRandom() * 100), int(Util::getRandom() * 100), int(Util::getRandom() * 100)), 
                             glm::vec3(Util::getRandom(), Util::getRandom(), Util::getRandom())));
    // std::cout<< "ADDBD :: " << Util::getRandom() << std::endl;
    this->numBoids++;
}

void BoidGroup::removeBoid(){
    if(this->numBoids <= 0) return;
    unsigned int idx = int(Util::getRandom() * this->numBoids);
    if(idx >= this->numBoids) idx--;
    std::cout<< "RMBD :: idx " << idx << "  nb " << numBoids << std::endl;
    this->boids.erase( boids.begin() + idx);
    this->numBoids--;

}

