#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "structures.hpp"

// ----------------------------------------------------------------

void PrintTree(std::ostream& out, TreeNode* node, int depth = 0);
void PrintBodies(std::ostream& out, std::vector<Particle>& bodies);
void PrintSimulationTimeStep(std::ostream& out, std::vector<Particle>& bodies, double t);

#endif