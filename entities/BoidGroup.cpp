#include "BoidGroup.hpp"
#include <iostream>

BoidGroup::BoidGroup(int numBoids){
    for(int i=0; i<numBoids; i++){
        addBoid();        
    }
};

void BoidGroup::update(glm::vec3 target){
    for (std::vector<Boid*>::iterator it = boids.begin(); it != boids.end(); ++it) {
        (*it)->update(target);
    }
}

void BoidGroup::draw(){
    for (std::vector<Boid*>::iterator it = boids.begin(); it != boids.end(); ++it) {
        (*it)->draw();
    }
}

glm::vec3 BoidGroup::calcBoidSeparation(std::vector<Boid>::iterator currBoid){

}

glm::vec3 BoidGroup::calcBoidGroupVelocity(){

}

glm::vec3 BoidGroup::calcBoidGroupHeading(){

}

glm::vec3 BoidGroup::calcBoidGroupCenter(){

}

void BoidGroup::addBoid(){
    // boids.push_back(new Boid(glm::vec3(int(Util::getRandom() * 100), int(Util::getRandom() * 100), int(Util::getRandom() * 100)), glm::vec3(2.0f,2.0f,2.0f)));
    boids.push_back(new Boid(glm::vec3(int(Util::getRandom() * 100), int(Util::getRandom() * 100), int(Util::getRandom() * 100)), 
                             glm::vec3(Util::getRandom(), Util::getRandom(), Util::getRandom())));
    std::cout<< "ADDBD :: " << Util::getRandom() << std::endl;
    this->numBoids++;
}

void BoidGroup::removeBoid(){
    if(this->numBoids <= 0) return;

    unsigned int idx = int(Util::getRandom() * numBoids);
    if(idx == numBoids) idx--;
    boids.erase( boids.begin() + idx);

    std::cout<< "RMBD :: idx " << idx << "  nb " << numBoids << std::endl;
    this->numBoids--;
    
}

