#ifndef GRAVITATIONAL_FORCE_HPP
#define GRAVITATIONAL_FORCE_HPP

#include "structures.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <omp.h>

#define GRAVITATIONAL_CONSTANT 1
#define SMOOTHING_FACTOR (0.1 * 0.1)
// ----------------------------------------------------------------

int ComputeGravity(TreeNode *node, std::vector<Particle> &bodies, double threshold);
void ComputeForce(TreeNode *node, Particle &body, double threshold, int &gravityNodesUsed);

#endif