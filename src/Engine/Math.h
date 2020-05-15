//
// Created by javier on 5/12/20.
//

#ifndef GIGAENGINE_MATH_H
#define GIGAENGINE_MATH_H

//use SIMD instructions if we can
#if __AVX2__
#define GLM_FORCE_AVX2
#define GLM_FORCE_ALIGNED
#endif

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <ext.hpp>
#endif //GIGAENGINE_MATH_H
