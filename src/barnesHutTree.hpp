#ifndef BARNES_HUT_TREE_HPP
#define BARNES_HUT_TREE_HPP

#include "structures.hpp"
#include <iostream>
#include <vector>
#include <omp.h>

// ----------------------------------------------------------------

class QuadTree
{
    public:

    QuadTree();
    QuadTree(double xNodeCenter, double yNodeCenter, double size, std::vector<Particle>& bodies);

    private:

    void InsertBody(Particle& body);
    void InsertBody(TreeNode* node, Particle* body, int depth, bool newBody);
    void SubdivideNode(TreeNode* node);
    void Collision(TreeNode *node, Particle *body);

    public:

    std::unique_ptr<TreeNode> root;
    uint64_t numberOfNodes{};
};

class ParallelQuadTree
{
    public:

    ParallelQuadTree(int numThreads, double xNodeCenter, double yNodeCenter, double size, std::vector<Particle>& bodies);

    private: 


};

#endif