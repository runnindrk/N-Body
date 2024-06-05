#ifndef RENDER_HPP
#define RENDER_HPP

#include "structures.hpp"
#include "barnesHutTree.hpp"
#include "gravitationalForce.hpp"
#include "rungeKutta.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <chrono>

// ----------------------------------------------------------------

void render(std::vector<Particle> &bodies);

#endif