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
        double G = 0.1;
        double particleMass = 1;
        double distance = std::sqrt(xPosition * xPosition + yPosition * yPosition);
        double massIntegral = numberOfParticles * particleMass * (std::sqrt(M_PI) / 2) * std::erf(distance);
        double speed = std::sqrt((G * massIntegral) / distance);
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
    std::normal_distribution<double> distRadius(1000, 20);
    std::uniform_real_distribution<double> distAngle(0.0, 2 * M_PI);
    std::normal_distribution<double> distMass(1, 0.1);
    
    double massCentral = 1000000;
    Particle centralMass = Particle(massCentral, 0, 0, 0, 0);
    centralMass.density *= 25000;
    centralMass.radius = std::sqrt(centralMass.mass/(centralMass.density * M_PI));
    state.push_back(centralMass);

    std::set<std::pair<double, double>> uniquePositions;

    for (int i = 0; i < numberOfParticles - 1; i++)
    {
        double mass = distMass(rng);
        double rPosition = distRadius(rng);
        double anglePosition = distAngle(rng);
        std::pair<double, double> position;

        while (uniquePositions.find(position) != uniquePositions.end())
        {
            rPosition = distRadius(rng);
            anglePosition = distAngle(rng);
            position = {rPosition, anglePosition};
        }
        
        // Convert to cartesian
        double xPosition = rPosition * std::cos(anglePosition);
        double yPosition = rPosition * std::sin(anglePosition);

        // Tangential speed
        double G = 0.1;
        double speed = std::sqrt((G * massCentral) / rPosition);
        double xVelocity = -yPosition * speed / rPosition;
        double yVelocity = xPosition * speed / rPosition;

        uniquePositions.insert(position);
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