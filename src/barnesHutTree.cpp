#include "barnesHutTree.hpp"

// ----------------------------------------------------------------

QuadTree::QuadTree(std::vector<Particle>& bodies)
{
    root = std::make_unique<TreeNode>(0, 0, 0, 0, 16384);
    
    for (int i = 0; i < bodies.size(); i++)
        InsertBody(bodies[i]);
}

// ----------------------------------------------------------------

void QuadTree::InsertBody(Particle& body)
{
    InsertBody(root.get(), &body, true);
}

void QuadTree::InsertBody(TreeNode* node, Particle* body, bool newBody)
{
    if (node->isLeaf)
    {
        if (!node->nBodies)
        {
            node->nBodies += 1;
            node->body = body;
            node->totalMass += node->body->mass;
            node->xCenterOfMass = node->body->xPosition;
            node->yCenterOfMass = node->body->yPosition;
        }

        else
        {
            SubdivideNode(node);
            InsertBody(node, node->body, false);
            InsertBody(node, body, true);
        }
    }

    else
    {
        if (newBody)
        {
            node->nBodies += 1;
            node->totalMass += body->mass;
            node->xCenterOfMass =
                (node->xCenterOfMass * node->totalMass + body->xPosition * body->mass) /
                (node->totalMass + body->mass);
            node->yCenterOfMass =
                (node->yCenterOfMass * node->totalMass + body->yPosition * body->mass) /
                (node->totalMass + body->mass);
        }

        if (body->xPosition < node->xNodeCenter && body->yPosition >= node->yNodeCenter)
            InsertBody(node->firstQuadrant.get(), body, newBody);

        else if (body->xPosition >= node->xNodeCenter && body->yPosition >= node->yNodeCenter)
            InsertBody(node->secondQuadrant.get(), body, newBody);

        else if (body->xPosition >= node->xNodeCenter && body->yPosition < node->yNodeCenter)
            InsertBody(node->thirdQuadrant.get(), body, newBody);

        else
            InsertBody(node->fourthQuadrant.get(), body, newBody);
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

// ----------------------------------------------------------------