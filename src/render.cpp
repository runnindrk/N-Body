#include "render.hpp"

// ----------------------------------------------------------------

void render(std::vector<Particle> &bodies)
{
    sf::RenderWindow window(sf::VideoMode(1500, 1500), "Barnes-Hut Simulation");

    const float scale = 0.25;
    const float radiusScale = 1;
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
            if (!body.isCollided)
            {
                sf::CircleShape shape(body.radius*radiusScale); // Particle radius

                float scaledX = (body.xPosition - centerX) * scale + windowCenterX - shape.getRadius(); 
                float scaledY = (body.yPosition - centerY) * scale + windowCenterY - shape.getRadius();
                shape.setPosition(scaledX, scaledY);
                window.draw(shape);
            }
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