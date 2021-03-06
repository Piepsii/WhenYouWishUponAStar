#include <SFML\Graphics.hpp>
#include "WhenYouWishUponAStar/Simulation.h"
#include "WhenYouWishUponAStar/InputManager.h"
#include "WhenYouWishUponAStar/Time.h"
#include "WhenYouWishUponAStar/StaticVariables.h"

using namespace WhenYouWishUponAStar;

int main() {
    sf::VideoMode videoMode;
    const char* title = "When You Wish Upon A*";
    InputManager input;
    
    Simulation* sim = Simulation::Instance();
    sim->setInput(input);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), title);

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

    return 0;
}
