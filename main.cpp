#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <optional>
#include <iostream>
#include "Intersection.h"
#include "VehicleLight.h"
#include "PedestrianLight.h"

void drawRoads(sf::RenderWindow& window) {
    sf::RectangleShape verticalRoad({320.f, 1080.f});
    verticalRoad.setPosition({800.f, 0.f});
    verticalRoad.setFillColor(sf::Color(50, 50, 50));

    sf::RectangleShape horizontalRoad({1920.f, 320.f});
    horizontalRoad.setPosition({0.f, 380.f});
    horizontalRoad.setFillColor(sf::Color(50, 50, 50));

    window.draw(verticalRoad);
    window.draw(horizontalRoad);

    sf::RectangleShape vDivider({10.f, 1080.f});
    vDivider.setPosition({955.f, 0.f});
    vDivider.setFillColor(sf::Color(200, 200, 50));

    sf::RectangleShape hDivider({1920.f, 10.f});
    hDivider.setPosition({0.f, 535.f});
    hDivider.setFillColor(sf::Color(200, 200, 50));

    window.draw(vDivider);
    window.draw(hDivider);

    sf::RectangleShape centreBox({320.f, 320.f});
    centreBox.setPosition({800.f, 380.f});
    centreBox.setFillColor(sf::Color(50, 50, 50));
    window.draw(centreBox);
}

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Traffic Light Controller", sf::State::Fullscreen);

    Intersection mainJunction;

    try {
        mainJunction.loadConfiguration("config.txt");
    } catch (const std::exception& e) {
        mainJunction.logEvent(std::string("File Notice: ") + e.what() + " Using default settings.");
    }

    sf::Font font;
    std::optional<sf::Text> menuText;
    bool fontLoaded = false;

    try {
        if (font.openFromFile("COMIC.TTF")) {
            menuText.emplace(font, "MODES:\n1. Regular\n2. Emergency\n3. Maintenance\n4. Inject glitch", 30);
            menuText->setFillColor(sf::Color::White);
            menuText->setPosition({1600.f, 30.f});
            fontLoaded = true;
        } else {
            throw std::runtime_error("Could not find COMIC.TTF");
        }
    } catch (const std::exception& e) {
        mainJunction.logEvent(std::string("Font Warning: ") + e.what());
    }

    mainJunction.addLight("NorthVehicle", new VehicleLight("Red", 930.f, 200.f));
    mainJunction.addLight("SouthVehicle", new VehicleLight("Red", 930.f, 720.f));
    mainJunction.addLight("EastVehicle", new VehicleLight("Green", 1140.f, 510.f, true));
    mainJunction.addLight("WestVehicle", new VehicleLight("Green", 620.f, 510.f, true));

    mainJunction.addLight("NorthPedestrian", new PedestrianLight("Green", 1110.f, 300.f, true));
    mainJunction.addLight("SouthPedestrian", new PedestrianLight("Green", 700.f, 720.f, true));
    mainJunction.addLight("EastPedestrian", new PedestrianLight("RedWait2", 1140.f, 690.f));
    mainJunction.addLight("WestPedestrian", new PedestrianLight("RedWait2", 720.f, 280.f));

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }

                if (mainJunction.isSystemGlitched() && mainJunction.getMode() == TrafficMode::Maintenance) {
                    mainJunction.processResetCode(keyPressed->code);
                }
                else {
                    if (keyPressed->code == sf::Keyboard::Key::Num1) {
                        mainJunction.setMode(1);
                    } else if (keyPressed->code == sf::Keyboard::Key::Num2) {
                        mainJunction.setMode(2);
                    } else if (keyPressed->code == sf::Keyboard::Key::Num3) {
                        mainJunction.setMode(3);
                    } else if (keyPressed->code == sf::Keyboard::Key::Num4) {
                        mainJunction.triggerGlitch();
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        mainJunction.update(deltaTime);

        window.clear(sf::Color(60, 120, 60));

        drawRoads(window);
        mainJunction.draw(window);

        if (fontLoaded) {
            window.draw(*menuText);

            const auto& logs = mainJunction.getLogs();

            sf::Text logDisplay(font, "", 24);
            logDisplay.setFillColor(sf::Color::Yellow);

            float startY = 1050.f - (logs.size() * 30.f);

            for (size_t i = 0; i < logs.size(); ++i) {
                logDisplay.setString(logs[i]);
                logDisplay.setPosition({1200.f, startY + (i * 30.f)});
                window.draw(logDisplay);
            }
        }

        window.display();
    }

    return 0;
}