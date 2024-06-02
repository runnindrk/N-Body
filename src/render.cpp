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

    int frameCount = 0;
    sf::Clock fpsClock;
    float fpsUpdateTime = 0.5; // Update FPS every 0.5 seconds

    while (window.isOpen()) 
    {
        float deltaTime = 0.0;
        sf::Event event;
        
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // FPS Calculation and Display
        deltaTime = fpsClock.restart().asSeconds();
        frameCount++;

        QuadTree tree(bodies);
        ComputeGravity(tree.root.get(), bodies, 0.5);
        AdvanceTime(bodies, 0, 0.250);

        for (const auto& body : bodies) 
        {
            double particleRadius = 2*std::sqrt(body.mass);
            particleRadius = 2;
            sf::CircleShape shape(particleRadius*scale); // Particle radius
            
            float scaledX = (body.xPosition - centerX - particleRadius / 2) * scale + windowCenterX; 
            float scaledY = (body.yPosition - centerY - particleRadius / 2) * scale + windowCenterY;
            shape.setPosition(scaledX, scaledY);
            window.draw(shape);
        }

        // Draw FPS on the window
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cerr << "Font not found.\n";
        }
        
        sf::Text fpsText;
        fpsText.setFont(font);
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(sf::Color::White);
        fpsText.setPosition(10, 10);
        
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(1 / deltaTime)));

        window.draw(fpsText);

        window.display();
    }
}