#include "render.hpp"

// ----------------------------------------------------------------

void render(std::vector<Particle> &bodies)
{
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "Barnes-Hut Simulation");

    const float scale = 0.5;
    const float centerX = 0;
    const float centerY = 0;

    const float windowCenterX = window.getSize().x / 2.0f;
    const float windowCenterY = window.getSize().y / 2.0f;

    while (window.isOpen()) 
    {
        sf::Event event;
        
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        QuadTree tree(bodies);
        ComputeGravity(tree.root.get(), bodies, 0.5);
        AdvanceTime(bodies, 0, 0.125);

        for (const auto& body : bodies) 
        {
            double particleRadius = 2*std::sqrt(body.mass);
            particleRadius = 2;
            sf::CircleShape shape(particleRadius*scale); // Particle radius
            // Translate particle position to be centered around (-64, 64)
            float scaledX = (body.xPosition - centerX - particleRadius / 2) * scale + windowCenterX; 
            float scaledY = (body.yPosition - centerY - particleRadius / 2) * scale + windowCenterY;
            shape.setPosition(scaledX, scaledY);
            window.draw(shape);
        }

        window.display();
    }
}