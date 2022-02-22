#include <SFML\Graphics.hpp>
#include "Simulation.h"
#include "InputManager.h"
#include "Time.h"

int main() {
    sf::VideoMode videoMode;
    const char* title = "When You Wish Upon A*";
    InputManager input;

    const uint32_t width = 1000;
    const uint32_t height = width;
    const uint32_t columns = 30;
    const uint32_t rows = 30;
    const uint32_t tileSize = width / columns;

    Simulation* sim = new Simulation(width,
                                     height,
                                     columns,
                                     rows,
                                     tileSize);
    sf::RenderWindow window(sf::VideoMode(width, height), title);

    sf::Clock clock;
    sf::Time delta;
    float hertz = 60.0f;
    float frameTime = 1.0f / hertz;
    bool running = true;
    
    while (running)
    {
        sf::Event event;
        delta = clock.restart();
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::KeyPressed:
                input.setKey(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                input.setKey(event.key.code, false);
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        if (input.isKeyPressed(sf::Keyboard::Key::Down)) {
            hertz -= 10.0f;
        }
        if (input.isKeyPressed(sf::Keyboard::Key::Up)) {
            hertz += 10.0f;
        }
        frameTime = 1.0f / hertz;

        window.clear(sf::Color::Black);
        window.setActive();

        if (Time::update() && sim->update(delta.asSeconds())) {
            sim->draw(window);
        }
        else {
            running = false;
        }

        window.display();
        sf::Time delay(sf::seconds(frameTime - delta.asSeconds()));
        sf::sleep(delay);
    }

    delete sim;
    sim = nullptr;

    return 0;
}
