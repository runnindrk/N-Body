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
    void InsertBody(TreeNode* node, Particle* body, bool newBody);
    void SubdivideNode(TreeNode* node);

    public:

    std::unique_ptr<TreeNode> root;
};

#endif