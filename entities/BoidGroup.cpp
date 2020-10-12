#include "BoidGroup.hpp"

BoidGroup::BoidGroup(int numBoids){
    for(int i=0; i<numBoids; i++){
        addBoid();
        this->numBoids++;
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
    boids.push_back(new Boid(glm::vec3(int(Util::getRandom() * 100), int(Util::getRandom() * 100), int(Util::getRandom() * 100))));
}

void BoidGroup::removeBoid(){

}

