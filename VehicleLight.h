#pragma once
#include "Signal.h"
#include <SFML/Graphics.hpp>
#include <string>

class VehicleLight : public Signal {
private:
    std::string currentColour;
    std::string initialColour;
    sf::RectangleShape casing;
    sf::CircleShape redBulb;
    sf::CircleShape yellowBulb;
    sf::CircleShape greenBulb;

    void updateVisuals();

public:
    VehicleLight(std::string startColour, float x, float y, bool isHorizontal = false);

    void changeColour() override;
    void setModeState(const std::string& state) override;
    void restoreNormalState() override;
    void forceGreen() override;
    void resetLight() override;
    float getStateDuration() const override;
    void draw(sf::RenderWindow& window) override;
    std::string getColour() const override;
};