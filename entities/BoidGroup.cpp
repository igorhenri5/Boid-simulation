#include "BoidGroup.hpp"

BoidGroup::BoidGroup(int numBoids){
    for(int i=0; i<numBoids; i++){
        addBoid();
        this->numBoids++;
    }
};

void BoidGroup::update(glm::vec3 target){

}

void BoidGroup::draw(){

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

}

void BoidGroup::removeBoid(){

}

