#include "initialState.hpp"

// ----------------------------------------------------------------

std::vector<Particle> CircularGaussianDistribution(int numberOfParticles)
{
    std::vector<Particle> state{};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::normal_distribution<double> distPosV(0, 1);
    std::normal_distribution<double> distPosX(0, 5);
    std::normal_distribution<double> distPosY(0, 5);
    std::normal_distribution<double> distMass(1, 2);
    
    std::set<std::pair<double, double>> uniquePositions;

    for (int i = 0; i < numberOfParticles; i++)
    {
        double mass = distMass(rng);
        double xPosition = distPosX(rng);
        double yPosition = distPosY(rng);
        double xVelocity = distPosV(rng);
        double yVelocity = distPosV(rng);
        std::pair<double, double> position;

        while (uniquePositions.find(position) != uniquePositions.end())
        {
            xPosition = distPosX(rng);
            yPosition = distPosY(rng);
            position = {xPosition, yPosition};
        }
        
        uniquePositions.insert(position);
        state.push_back(Particle(mass, xPosition, yPosition, xVelocity, yVelocity));
    }
    
    return state;
}