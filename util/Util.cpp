#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Util.hpp"

namespace Util {

    double normNegSigmoid(double val, double limit){
        // Compute a normalization factor based on a sigmoid function.
        // When val -> limit,  fac -> 0,
        // when val -> 0,      fac -> 1
        double fac = 1/(1 + glm::exp(-9/limit*(limit/2-val)));
        return fac;
    }

    double normSigmoid(double val, double limit){
        // Compute a normalization factor based on a sigmoid function.
        // When val -> limit,  fac -> 1,
        // when val -> 0,      fac -> 0
        double fac = 1/(1 + glm::exp(9/limit*(limit/2-val)));
        return fac;
    }

    glm::vec3 normalize(glm::vec3 in){
        in /= glm::length(in) + 0.000001;
        return in;
    }

    glm::vec3 normalize(glm::vec3 vec, double limit){
        // Compute the length of the vector
        double length = glm::length(vec);

        // Compute a normalization factor based on a sigmoid function.
        // When length -> limit,  fac -> 1,
        // when length -> 0,      fac -> 0
        double fac = Util::normSigmoid(length, limit);

        // Return the vector normalized by the factor above
        vec /= length + 0.000001;
        vec *= fac;

        return vec;
    }

    glm::vec3 normalizeNeg(glm::vec3 vec, double limit){
        // Compute the length of the vector
        double length = glm::length(vec);

        // Compute a normalization factor based on a sigmoid function.
        // When length -> limit,  fac -> 0,
        // when length -> 0,      fac -> 1
        double fac = Util::normNegSigmoid(length, limit);

        // Return the vector normalized by the factor above
        vec /= length + 0.000001;
        vec *= fac;

        return vec;
    }

}