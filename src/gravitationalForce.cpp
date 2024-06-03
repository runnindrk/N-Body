#include "gravitationalForce.hpp"

// ----------------------------------------------------------------

inline double ComputeDistanceSquared(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return dx * dx + dy * dy;
}

inline void ComputeGravitationalForce(const Particle &p1, const Particle &p2, double &forceX,
                                      double &forceY)
{
    constexpr double G = 0.1;
    constexpr double smoothingFactor = 0.1 * 0.1;

    double dx = p2.xPosition - p1.xPosition;
    double dy = p2.yPosition - p1.yPosition;

    double distanceSquared = dx * dx + dy * dy + smoothingFactor;
    double distance = std::sqrt(distanceSquared);
    double force = G * p1.mass * p2.mass / distanceSquared;

    forceX = force * dx / distance;
    forceY = force * dy / distance;
}

// ----------------------------------------------------------------

int ComputeGravity(TreeNode *node, std::vector<Particle> &bodies, double threshold)
{
    int gravityNodesUsed = 0;

    for (Particle &body : bodies)
    {
        if (!body.isCollided)
        {
            body.xForce = 0;
            body.yForce = 0;
            ComputeForce(node, body, threshold, gravityNodesUsed);
        }
    }

    return gravityNodesUsed;
}

void ComputeForce(TreeNode *node, Particle &body, double threshold, int &gravityNodesUsed)
{
    if (node->nBodies == 0)
        return;

    if (body.xPosition == node->xCenterOfMass && body.yPosition == node->yCenterOfMass)
        return;

    double s = node->size;
    double dSquared = ComputeDistanceSquared(body.xPosition, body.yPosition, node->xCenterOfMass, node->yCenterOfMass);
    double d = std::sqrt(dSquared);

    if ((node->isLeaf &&
         (body.xPosition != node->xCenterOfMass || body.yPosition != node->yCenterOfMass)) ||
        (s / d < threshold))
    {
        gravityNodesUsed += 1;
        node->isForceComputation = true;

        Particle pseudoBody = {node->totalMass, node->xCenterOfMass, node->yCenterOfMass, 0, 0};
        double fx = 0, fy = 0;
        ComputeGravitationalForce(body, pseudoBody, fx, fy);
        body.xForce += fx;
        body.yForce += fy;
    }

    else
    {
        ComputeForce(node->firstQuadrant.get(), body, threshold, gravityNodesUsed);
        ComputeForce(node->secondQuadrant.get(), body, threshold, gravityNodesUsed);
        ComputeForce(node->thirdQuadrant.get(), body, threshold, gravityNodesUsed);
        ComputeForce(node->fourthQuadrant.get(), body, threshold, gravityNodesUsed);
    }
}

// ------------------------------------------------------------------------------------------------