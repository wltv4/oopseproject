#include "VehicleLight.h"

VehicleLight::VehicleLight(std::string startColour, float x, float y, bool isHorizontal) {
    currentColour = startColour;
    initialColour = startColour;

    float radius = 20.f;
    float padding = 10.f;

    if (isHorizontal) {
        casing.setSize({160.f, 60.f});
        casing.setFillColor(sf::Color(20, 20, 20));
        casing.setPosition({x, y});

        redBulb.setRadius(radius);
        redBulb.setPosition({x + padding, y + padding});

        yellowBulb.setRadius(radius);
        yellowBulb.setPosition({x + padding * 2 + radius * 2, y + padding});

        greenBulb.setRadius(radius);
        greenBulb.setPosition({x + padding * 3 + radius * 4, y + padding});
    } else {
        casing.setSize({60.f, 160.f});
        casing.setFillColor(sf::Color(20, 20, 20));
        casing.setPosition({x, y});

        redBulb.setRadius(radius);
        redBulb.setPosition({x + padding, y + padding});

        yellowBulb.setRadius(radius);
        yellowBulb.setPosition({x + padding, y + padding * 2 + radius * 2});

        greenBulb.setRadius(radius);
        greenBulb.setPosition({x + padding, y + padding * 3 + radius * 4});
    }

    updateVisuals();
}

void VehicleLight::changeColour() {
    if (currentColour == "Red") currentColour = "RedYellow";
    else if (currentColour == "RedYellow") currentColour = "Green";
    else if (currentColour == "Green") currentColour = "Yellow";
    else currentColour = "Red";

    updateVisuals();
}

void VehicleLight::updateVisuals() {
    sf::Color dimRed(80, 0, 0);
    sf::Color dimYellow(80, 80, 0);
    sf::Color dimGreen(0, 80, 0);

    redBulb.setFillColor(dimRed);
    yellowBulb.setFillColor(dimYellow);
    greenBulb.setFillColor(dimGreen);

    if (currentColour == "Red") {
        redBulb.setFillColor(sf::Color::Red);
    } else if (currentColour == "RedYellow") {
        redBulb.setFillColor(sf::Color::Red);
        yellowBulb.setFillColor(sf::Color::Yellow);
    } else if (currentColour == "Green") {
        greenBulb.setFillColor(sf::Color::Green);
    } else if (currentColour == "Yellow") {
        yellowBulb.setFillColor(sf::Color::Yellow);
    }
}

void VehicleLight::setModeState(const std::string& state) {
    redBulb.setFillColor(sf::Color(80, 0, 0));
    yellowBulb.setFillColor(sf::Color(80, 80, 0));
    greenBulb.setFillColor(sf::Color(0, 80, 0));

    if (state == "Yellow") {
        yellowBulb.setFillColor(sf::Color::Yellow);
    }
}

void VehicleLight::restoreNormalState() {
    updateVisuals();
}

void VehicleLight::forceGreen() {
    currentColour = "Green";
    updateVisuals();
}

void VehicleLight::resetLight() {
    currentColour = initialColour;
    updateVisuals();
}

float VehicleLight::getStateDuration() const {
    if (currentColour == "Green" || currentColour == "Red") return 4.0f;
    return 1.5f;
}

void VehicleLight::draw(sf::RenderWindow& window) {
    window.draw(casing);
    window.draw(redBulb);
    window.draw(yellowBulb);
    window.draw(greenBulb);
}

std::string VehicleLight::getColour() const { 
    return currentColour; 
}