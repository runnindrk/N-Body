#include "initialState.hpp"

// ----------------------------------------------------------------

std::vector<Particle> CircularGaussianDistribution(int numberOfParticles)
{
    std::vector<Particle> state{};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::normal_distribution<double> distPosV(0, 1);
    std::normal_distribution<double> distPosX(0, 25);
    std::normal_distribution<double> distPosY(0, 25);
    std::normal_distribution<double> distMass(1, 0.1);
    
    std::set<std::pair<double, double>> uniquePositions;

    for (int i = 0; i < numberOfParticles; i++)
    {
        double mass = distMass(rng);
        double xPosition = distPosX(rng);
        double yPosition = distPosY(rng);
        std::pair<double, double> position;

        while (uniquePositions.find(position) != uniquePositions.end())
        {
            xPosition = distPosX(rng);
            yPosition = distPosY(rng);
            position = {xPosition, yPosition};
        }
        
        // Tangential speed
        double particleMass = 1;
        double distance = std::sqrt(xPosition * xPosition + yPosition * yPosition);
        double massIntegral = numberOfParticles * particleMass * (std::sqrt(M_PI) / 2) * std::erf(distance);
        double speed = std::sqrt((GRAVITATIONAL_CONSTANT * massIntegral) / distance);
        double xVelocity = -yPosition * speed / distance;
        double yVelocity = xPosition * speed / distance;

        uniquePositions.insert(position);
        state.push_back(Particle(mass, xPosition, yPosition, xVelocity, yVelocity));
    }
    
    return state;
}

std::vector<Particle> MassiveCentralObjectAndRing(int numberOfParticles)
{
    std::vector<Particle> state{};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::normal_distribution<double> distVelocity(0, 1);
    std::uniform_real_distribution<double> distY(-6144, 6144);
    std::uniform_real_distribution<double> distX(-6144, 6144);
    std::uniform_real_distribution<double> distAngle(0.0, 2 * M_PI);
    std::normal_distribution<double> distMass(1, 0.1);
    
    double massCentral = 1000000;
    state.push_back(Particle(massCentral, 0, 0, 0, 0));

    std::set<std::pair<double, double>> uniquePositions;

    for (int i = 0; i < numberOfParticles - 1; i++)
    {
        double mass = distMass(rng);
        double xPosition = distX(rng);
        double yPosition = distY(rng);
        double rPosition = std::sqrt(pow(xPosition, 2) + pow(yPosition, 2));

        while (rPosition < 512 || rPosition > 6144)
        {
            xPosition = distX(rng);
            yPosition = distY(rng);
            rPosition = std::sqrt(pow(xPosition, 2) + pow(yPosition, 2));
        }
        
        // Tangential speed
        double speed = std::sqrt((GRAVITATIONAL_CONSTANT * massCentral) / rPosition);
        double xVelocity = -yPosition * speed / rPosition;
        double yVelocity = xPosition * speed / rPosition;

        state.push_back(Particle(mass, xPosition, yPosition, xVelocity, yVelocity));
    }

    return state;
}

std::vector<Particle> SunEarthMoonSystem()
{
    std::vector<Particle> state{};
    
    state.push_back(Particle(100000, 0, 0, 0, 0));
    state.push_back(Particle(100, 0, 1024, 3.125, 0));
    state.push_back(Particle(1, 0, 1034, 3.125 + 1, 0));

    return state;
}