#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <glm/glm.hpp>

#define PI  3.14592653589793

namespace Util{

    double normSigmoid(double val, double limit);
    double normNegSigmoid(double val, double limit);
    glm::vec3 normalize(glm::vec3 in);
    glm::vec3 normalize(glm::vec3 vec, double limit);
    glm::vec3 normalizeNeg(glm::vec3 vec, double limit);
    double getRandom();

    double computeAngle(glm::vec3 vec1, glm::vec3 vec2);
    glm::vec3 sphericalToCartesian(glm::vec3 point);
    glm::vec3 cartesianToSpherical(glm::vec3 point);
    glm::vec3 rotateAtPhi(glm::vec3 cartesian, double degrees);
    glm::vec3 rotateAtTheta(glm::vec3 cartesian, double degrees);
}

#endif 
