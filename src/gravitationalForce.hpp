#ifndef GRAVITATIONAL_FORCE_HPP
#define GRAVITATIONAL_FORCE_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include "structures.hpp"

// ----------------------------------------------------------------

void ComputeGravity(TreeNode *node, std::vector<Particle> &bodies, double threshold);
void ComputeForce(TreeNode *node, Particle &body, double threshold);

#endif