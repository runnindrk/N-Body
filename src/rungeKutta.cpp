#include "rungeKutta.hpp"

// ----------------------------------------------------------------

Eigen::VectorXd DifferentialFunction(Eigen::VectorXd r, double t)
{
    Eigen::VectorXd f(4);

    f[0] = r[0];
    f[1] = r[1];
    f[2] = r[2];
    f[3] = r[3];
    
    return f;
}

void ParticleTimeStep(Particle& body, double t, double h) 
{
    Eigen::VectorXd r(4);
    Eigen::MatrixXd k(4, 4);
    
    r[0] = body.xVelocity;
    r[1] = body.xForce/body.mass;
    r[2] = body.yVelocity;
    r[3] = body.yForce/body.mass;

    k.col(0) = h*DifferentialFunction(r, t);
    k.col(1) = h*DifferentialFunction(r + 0.5*k.col(0), t + 0.5);
    k.col(2) = h*DifferentialFunction(r + 0.5*k.col(1), t + 0.5);
    k.col(3) = h*DifferentialFunction(r + k.col(2), t);
    
    Eigen::VectorXd update = 1.0/6.0*(k.col(0) + 2*k.col(1) + 2*k.col(2) + k.col(3));

    body.xPosition += update[0];
    body.xVelocity += update[1];
    body.yPosition += update[2];
    body.yVelocity += update[3];
}

void AdvanceTime(std::vector<Particle>& bodies, double t, double h)
{
    omp_set_num_threads(16);
    #pragma omp parallel for
    for (int i = 0; i < bodies.size(); i++)
        if (!bodies[i].isCollided)
            ParticleTimeStep(bodies[i], t, h); 
}