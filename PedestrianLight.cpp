#include "PedestrianLight.h"

PedestrianLight::PedestrianLight(std::string startPhase, float x, float y, bool isHorizontal) {
    currentPhase = startPhase;
    initialPhase = startPhase;
    float radius = 20.f;
    float padding = 10.f;

    if (isHorizontal) {
        casing.setSize({110.f, 60.f});
        casing.setFillColor(sf::Color(20, 20, 20));
        casing.setPosition({x, y});

        redBulb.setRadius(radius);
        redBulb.setPosition({x + padding, y + padding});

        greenBulb.setRadius(radius);
        greenBulb.setPosition({x + padding * 2 + radius * 2, y + padding});
    } else {
        casing.setSize({60.f, 110.f});
        casing.setFillColor(sf::Color(20, 20, 20));
        casing.setPosition({x, y});

        redBulb.setRadius(radius);
        redBulb.setPosition({x + padding, y + padding});

        greenBulb.setRadius(radius);
        greenBulb.setPosition({x + padding, y + padding * 2 + radius * 2});
    }

    updateVisuals();
}

void PedestrianLight::changeColour() {
    if (currentPhase == "Green") currentPhase = "RedWait1";
    else if (currentPhase == "RedWait1") currentPhase = "RedWait2";
    else if (currentPhase == "RedWait2") currentPhase = "RedWait3";
    else currentPhase = "Green";

    updateVisuals();
}

void PedestrianLight::updateVisuals() {
    redBulb.setFillColor(sf::Color(80, 0, 0));
    greenBulb.setFillColor(sf::Color(0, 80, 0));

    if (currentPhase == "Green") {
        greenBulb.setFillColor(sf::Color::Green);
    } else {
        redBulb.setFillColor(sf::Color::Red);
    }
}

void PedestrianLight::setModeState(const std::string& state) {
    redBulb.setFillColor(sf::Color(80, 0, 0));
    greenBulb.setFillColor(sf::Color(0, 80, 0));
}

void PedestrianLight::restoreNormalState() {
    updateVisuals();
}

void PedestrianLight::forceGreen() {
    currentPhase = "Green";
    updateVisuals();
}

void PedestrianLight::resetLight() {
    currentPhase = initialPhase;
    updateVisuals();
}

float PedestrianLight::getStateDuration() const {
    if (currentPhase == "Green" || currentPhase == "RedWait2") return 4.0f;
    return 1.5f;
}

void PedestrianLight::draw(sf::RenderWindow& window) {
    window.draw(casing);
    window.draw(redBulb);
    window.draw(greenBulb);
}

std::string PedestrianLight::getColour() const {
    return (currentPhase == "Green") ? "Green" : "Red";
}