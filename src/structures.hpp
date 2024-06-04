#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <memory>
#include <cmath>

// ----------------------------------------------------------------

struct Particle
{
    bool isCollided;
    double mass;
    double radius;
    double xPosition;
    double yPosition;
    double xVelocity;
    double yVelocity;
    double xForce;
    double yForce;

    Particle(double mass, 
             double xPosition, 
             double yPosition, 
             double xVelocity, 
             double yVelocity) :
    
    isCollided(false),
    mass(mass),
    radius(pow(mass, 1.0/3.7)),
    xPosition(xPosition),
    yPosition(yPosition),
    xVelocity(xVelocity),
    yVelocity(yVelocity),
    xForce(0),
    yForce(0)
    {}
};

struct TreeNode 
{
    bool isForceComputation;
    bool isLeaf;
    int nBodies;
    double size;
    double totalMass;
    double xCenterOfMass;
    double yCenterOfMass;
    double xNodeCenter;
    double yNodeCenter;

    Particle* body;
    std::unique_ptr<TreeNode> firstQuadrant;
    std::unique_ptr<TreeNode> secondQuadrant;
    std::unique_ptr<TreeNode> thirdQuadrant;
    std::unique_ptr<TreeNode> fourthQuadrant;

    TreeNode(double xNodeCenter, double yNodeCenter, double xCenterOfMass, double yCenterOfMass, double size) : 
    isForceComputation(false),
    isLeaf(true),
    nBodies(0),
    size(size),
    totalMass(0),
    xNodeCenter(xNodeCenter),
    yNodeCenter(yNodeCenter),
    xCenterOfMass(xCenterOfMass), 
    yCenterOfMass(yCenterOfMass)
    {}
};

#endif
