#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP

#include "structures.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <vector>

// ----------------------------------------------------------------

Eigen::VectorXd DifferentialFunction(Eigen::VectorXd r, double t);
void ParticleTimeStep(Particle& body, double t, double h);
void AdvanceTime(std::vector<Particle>& bodies, double t, double h);

#endif