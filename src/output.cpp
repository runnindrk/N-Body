#include "output.hpp"

// ----------------------------------------------------------------

void PrintTree(std::ostream &out, TreeNode *node, int depth)
{
    // clang-format off
    out << depth << " " 
        << node->xNodeCenter << " " 
        << node->yNodeCenter << " "
        << node->xCenterOfMass << " " 
        << node->yCenterOfMass << " " 
        << node->totalMass << " " 
        << node->size << "\n";
    // clang-format on

    if (node->isLeaf)
        return;
    
    PrintTree(out, node->firstQuadrant.get(), depth + 1);
    PrintTree(out, node->secondQuadrant.get(), depth + 1);
    PrintTree(out, node->thirdQuadrant.get(), depth + 1);
    PrintTree(out, node->fourthQuadrant.get(), depth + 1);
}

void PrintBodies(std::ostream& out, std::vector<Particle>& bodies)
{
    for (int i = 0; i < bodies.size(); i++)
    {
        // clang-format off
        out << bodies[i].mass << "  "
            << bodies[i].xPosition << "  "
            << bodies[i].yPosition << "  "
            << bodies[i].xVelocity << "  "
            << bodies[i].yVelocity << "  "
            << bodies[i].xForce << "  "
            << bodies[i].yForce << "\n";
        // clang-format on
    }
}

void PrintSimulationTimeStep(std::ostream& out, std::vector<Particle>& bodies, double t)
{
    out << t << "   ";

    for (int i = 0; i < bodies.size(); i++)
    {
        // clang-format off
        out << bodies[i].mass << "  "
            << bodies[i].xPosition << "  "
            << bodies[i].yPosition << "  "
            << bodies[i].xVelocity << "  "
            << bodies[i].yVelocity << "  "
            << bodies[i].xForce << "  "
            << bodies[i].yForce << "    ";
        // clang-format on
    }

    out << "\n";
}