#ifndef BARNES_HUT_TREE_HPP
#define BARNES_HUT_TREE_HPP

#include <iostream>
#include <vector>
#include "structures.hpp"

// ----------------------------------------------------------------

class QuadTree
{
    public:

    QuadTree(std::vector<Particle>& bodies);

    private:

    void InsertBody(Particle& body);
    void InsertBody(TreeNode* node, Particle* body, int depth, bool newBody);
    void SubdivideNode(TreeNode* node);
    void Collision(TreeNode *node, Particle *body);

    public:

    std::unique_ptr<TreeNode> root;
    uint64_t numberOfNodes{};
};

#endif