#include "gravitationalForce.hpp"

// ----------------------------------------------------------------

double ComputeDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void ComputeGravitationalForce(const Particle &p1, const Particle &p2, double &forceX,
                               double &forceY)
{
    double G = 0.1;

    double dx = p2.xPosition - p1.xPosition;
    double dy = p2.yPosition - p1.yPosition;

    double distance = ComputeDistance(p1.xPosition, p1.yPosition, p2.xPosition, p2.yPosition);
    double force = G * p1.mass * p2.mass / (distance * distance + 0.1 * 0.1); // smothing infinities

    forceX = force * dx / distance;
    forceY = force * dy / distance;
}

// ----------------------------------------------------------------

void ComputeGravity(TreeNode *node, std::vector<Particle> &bodies, double threshold)
{
    for (int i = 0; i < bodies.size(); i++)
    {
        bodies[i].xForce = 0;
        bodies[i].yForce = 0;
        ComputeForce(node, bodies[i], threshold);
    }
}

void ComputeForce(TreeNode *node, Particle &body, double threshold)
{
    if (!node->nBodies)
        return;

    if (body.xPosition == node->xCenterOfMass && body.yPosition == node->yCenterOfMass)
        return;

    if (node->isLeaf &&
       (body.xPosition != node->xCenterOfMass || body.yPosition != node->yCenterOfMass))
    {
        node->isForceComputation = true;

        double fx = 0;
        double fy = 0;

        Particle pseudoBody = {node->totalMass, node->xCenterOfMass, node->yCenterOfMass, 0, 0};
        ComputeGravitationalForce(body, pseudoBody, fx, fy);
        body.xForce += fx;
        body.yForce += fy;
    }

    else
    {
        double s = node->size;
        double d = ComputeDistance(body.xPosition, body.yPosition, node->xCenterOfMass,
                                   node->yCenterOfMass);

        if (s / d < threshold)
        {
            node->isForceComputation = true;

            double fx = 0;
            double fy = 0;

            Particle pseudoBody = {node->totalMass, node->xCenterOfMass, node->yCenterOfMass, 0, 0};
            ComputeGravitationalForce(body, pseudoBody, fx, fy);
            body.xForce += fx;
            body.yForce += fy;
        }

        else
        {
            ComputeForce(node->firstQuadrant.get(), body, threshold);
            ComputeForce(node->secondQuadrant.get(), body, threshold);
            ComputeForce(node->thirdQuadrant.get(), body, threshold);
            ComputeForce(node->fourthQuadrant.get(), body, threshold);
        }
    }
}

// ------------------------------------------------------------------------------------------------