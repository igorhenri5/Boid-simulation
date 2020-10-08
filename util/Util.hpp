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

}

#endif 
