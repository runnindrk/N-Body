#ifndef INITIAL_STATE_HPP
#define INITIAL_STATE_HPP

#include "structures.hpp"
#include <vector>
#include <random>
#include <cmath>
#include <set>

// ----------------------------------------------------------------

std::vector<Particle> CircularGaussianDistribution(int numberOfParticles);
std::vector<Particle> MassiveCentralObjectAndRing(int numberOfParticles);
std::vector<Particle> SunEarthMoonSystem();

#endif