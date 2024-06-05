#include "main.hpp"

// ----------------------------------------------------------------

int main()
{
    std::cout << "N-Body\n";

    // ------------------------------------------------------------
    // Build Particles

    // std::vector<Particle> bodies = {{100, 0, 0, 0, 0}, 
    //                                 {1, 0, 10, -1, 0}};

    // std::vector<Particle> bodies = {{1, 0, 0, 0, 0}, 
    //                                {1, 0, 10, -1, 0},
    //                                {1, 0, -10, -1, 0},
    //                                {1, 10, 0, -1, 0},
    //                                {1, -10, 0, -1, 0}};

    // std::vector<Particle> bodies = CircularGaussianDistribution(2500);
    std::vector<Particle> bodies = MassiveCentralObjectAndRing(20000);
    // std::vector<Particle> bodies = SunEarthMoonSystem();
    
    // A bug exists when particles are at the same place while constructing the tree, 
    // possible infinite recursion?
    // ------------------------------------------------------------
    // Simulation example

    /* std::ofstream outFileSimulation("test/simulation/simulation.dat");

    if (outFileSimulation.is_open())
    {
        std::cout << "File is open.\n";
    }

    else
    {
        std::cerr << "Unable to open file.\n";
    }

    double h = 0.125;
    double t_initial = 0;
    double t_final = 100;
    unsigned int sizeLoop = static_cast<unsigned int>((t_final - t_initial)/h);

    double t = 0;

    for (int i = 0; i < sizeLoop; i++)
    {
        QuadTree tree(bodies);
        ComputeGravity(tree.root.get(), bodies, 0.5);
        AdvanceTime(bodies, t, h);
        PrintSimulationTimeStep(outFileSimulation, bodies, t);
        t += h;
    }

    outFileSimulation.close(); */

    // ------------------------------------------------------------
    // Benchmark one frame

    // QuadTree tree(bodies);
    // ComputeGravity(tree.root.get(), bodies, 0.5);
    // AdvanceTime(bodies, 0, 0.125);

    // std::cout << tree.numberOfNodes << "    " << a << "\n";

    render(bodies);

    // Abandon matplotlib and learn a live graphics library for C++
    // Update tree size with maximums of distances of the bodies

    /* // ------------------------------------------------------------
    // Build Tree

    QuadTree exampleTree(bodies);

    // ------------------------------------------------------------
    // Compute Gravity

    ComputeGravity(exampleTree.root.get(), bodies, 0.5);
    // ComputeForce(exampleTree.root.get(), bodies[0], 0.5);

    // ------------------------------------------------------------
    // Output Bodies

    std::ofstream outFileBodies("test/tree/bodies.dat");

    if (outFileBodies.is_open())
    {
        PrintBodies(outFileBodies, bodies);
        outFileBodies.close();
    }

    else
    {
        std::cerr << "Unable to open file.\n";
    }

    // ------------------------------------------------------------
    // Output Tree

    std::ofstream outFileTree("test/tree/tree.dat");

    if (outFileTree.is_open())
    {
        PrintTree(outFileTree, exampleTree.root.get());
        outFileTree.close();
    }

    else
    {
        std::cerr << "Unable to open file.\n";
    }

    // ------------------------------------------------------------
 */
    return 0;
}