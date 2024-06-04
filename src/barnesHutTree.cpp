#include "barnesHutTree.hpp"

// ----------------------------------------------------------------

QuadTree::QuadTree(std::vector<Particle>& bodies)
{
    root = std::make_unique<TreeNode>(0, 0, 0, 0, 16384);
    
    for (int i = 0; i < bodies.size(); i++)
        if (!bodies[i].isCollided)
            InsertBody(bodies[i]);
}

// ----------------------------------------------------------------

void QuadTree::InsertBody(Particle& body)
{
    InsertBody(root.get(), &body, 0, true);
}

void QuadTree::InsertBody(TreeNode* node, Particle* body, int depth, bool newBody)
{
    if (node->isLeaf)
    {
        if (!node->nBodies)
        {
            numberOfNodes += 1;
            node->nBodies += 1;
            node->body = body;
            node->totalMass = node->body->mass;
            node->xCenterOfMass = node->body->xPosition;
            node->yCenterOfMass = node->body->yPosition;
        }

        else
        {
            if (16384.0 / (pow(2, depth)) <= 0.4 * (node->body->radius + body->radius))
                Collision(node, body);

            else 
            {
                SubdivideNode(node);
                InsertBody(node, node->body, depth + 1, false);
                InsertBody(node, body, depth + 1, true);
            }
        }
    }

    else
    {
        if (newBody)
        {
            node->nBodies += 1;
            node->xCenterOfMass =
                (node->xCenterOfMass * node->totalMass + body->xPosition * body->mass) /
                (node->totalMass + body->mass);
            node->yCenterOfMass =
                (node->yCenterOfMass * node->totalMass + body->yPosition * body->mass) /
                (node->totalMass + body->mass);
            node->totalMass += body->mass;
        }

        if (body->xPosition < node->xNodeCenter && body->yPosition >= node->yNodeCenter)
            InsertBody(node->firstQuadrant.get(), body, depth + 1, newBody);

        else if (body->xPosition >= node->xNodeCenter && body->yPosition >= node->yNodeCenter)
            InsertBody(node->secondQuadrant.get(), body, depth + 1, newBody);

        else if (body->xPosition >= node->xNodeCenter && body->yPosition < node->yNodeCenter)
            InsertBody(node->thirdQuadrant.get(), body, depth + 1, newBody);

        else
            InsertBody(node->fourthQuadrant.get(), body, depth + 1, newBody);
    }
}

void QuadTree::SubdivideNode(TreeNode *node)
{
    double halfSize = node->size / 2.0;
    node->firstQuadrant = std::make_unique<TreeNode>(
        node->xNodeCenter - halfSize / 2.0, node->yNodeCenter + halfSize / 2.0, 0, 0, halfSize);
    node->secondQuadrant = std::make_unique<TreeNode>(
        node->xNodeCenter + halfSize / 2.0, node->yNodeCenter + halfSize / 2.0, 0, 0, halfSize);
    node->thirdQuadrant = std::make_unique<TreeNode>(
        node->xNodeCenter + halfSize / 2.0, node->yNodeCenter - halfSize / 2.0, 0, 0, halfSize);
    node->fourthQuadrant = std::make_unique<TreeNode>(
        node->xNodeCenter - halfSize / 2.0, node->yNodeCenter - halfSize / 2.0, 0, 0, halfSize);
    node->isLeaf = false;
}

void QuadTree::Collision(TreeNode *node, Particle *body)
{
    // This only happens when there is only one particle in the node.
    
    body->isCollided = true;

    node->xCenterOfMass =
        (node->xCenterOfMass * (node->totalMass + body->mass)) /
        (node->totalMass + body->mass);
    node->yCenterOfMass =
        (node->yCenterOfMass * (node->totalMass + body->mass)) /
        (node->totalMass + body->mass);
    node->totalMass += body->mass;

    node->body->xVelocity = (node->body->mass * node->body->xVelocity + body->mass * body->xVelocity) /
                            (node->body->mass + body->mass);
    node->body->yVelocity = (node->body->mass * node->body->yVelocity + body->mass * body->yVelocity) /
                            (node->body->mass + body->mass);
    node->body->mass += body->mass;
    node->body->radius = pow(node->body->mass, 1.0/3.7);
}
// ----------------------------------------------------------------