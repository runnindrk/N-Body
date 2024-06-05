#include "render.hpp"

// ----------------------------------------------------------------

void render(std::vector<Particle> &bodies)
{
    sf::RenderWindow window(sf::VideoMode(1500, 1500), "Barnes-Hut Simulation");

    const float scale = 0.1;
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
        int numberBodies = 0;
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

        // Measure time for each step and the total time
        auto start = std::chrono::high_resolution_clock::now();

        auto t1_start = start;
        QuadTree tree(bodies);
        auto t1_end = std::chrono::high_resolution_clock::now();

        auto t2_start = t1_end;
        ComputeGravity(tree.root.get(), bodies, 0.5);
        auto t2_end = std::chrono::high_resolution_clock::now();

        auto t3_start = t2_end;
        AdvanceTime(bodies, 0, 0.250);
        auto t3_end = std::chrono::high_resolution_clock::now();

        auto t4_start = t3_end;

        for (const auto& body : bodies) 
        {
            if (!body.isCollided)
            {
                numberBodies += 1;
                sf::CircleShape shape;
                shape.setRadius(body.radius*radiusScale);
                shape.setFillColor(sf::Color(255, 255, 255));

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

        sf::Text bodiesText;
        bodiesText.setFont(font);
        bodiesText.setCharacterSize(24);
        bodiesText.setFillColor(sf::Color::White);
        bodiesText.setPosition(10, 40);
        bodiesText.setString("Bodies: " + std::to_string(numberBodies));
        window.draw(bodiesText);

        window.display();

        auto t4_end = std::chrono::high_resolution_clock::now();
        auto end = t4_end;
        // ----------------------------------------------------------------------------------------------

        // Calculate durations
        auto t1_duration = std::chrono::duration_cast<std::chrono::microseconds>(t1_end - t1_start);
        auto t2_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2_end - t2_start);
        auto t3_duration = std::chrono::duration_cast<std::chrono::microseconds>(t3_end - t3_start);
        auto t4_duration = std::chrono::duration_cast<std::chrono::microseconds>(t4_end - t4_start);
        auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        // Calculate percentages
        double t1_percentage = (t1_duration.count() / static_cast<double>(totalDuration.count())) * 100.0;
        double t2_percentage = (t2_duration.count() / static_cast<double>(totalDuration.count())) * 100.0;
        double t3_percentage = (t3_duration.count() / static_cast<double>(totalDuration.count())) * 100.0;
        double t4_percentage = (t4_duration.count() / static_cast<double>(totalDuration.count())) * 100.0;

        if (frameCount % 30 == 0) 
        {
            system("clear");
            std::cout << "QuadTree time: " << t1_duration.count() << " us (" << t1_percentage << "%)\n";
            std::cout << "ComputeGravity time: " << t2_duration.count() << " us (" << t2_percentage << "%)\n";
            std::cout << "AdvanceTime time: " << t3_duration.count() << " us (" << t3_percentage << "%)\n";
            std::cout << "Render time: " << t4_duration.count() << " us (" << t4_percentage << "%)\n";
            std::cout << "Total Frame time: " << totalDuration.count() << " us\n";
        }
    }
}