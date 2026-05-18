#pragma once
#include "Signal.h"
#include <SFML/Graphics.hpp>
#include <string>

class PedestrianLight : public Signal {
private:
    std::string currentPhase;
    std::string initialPhase;
    sf::RectangleShape casing;
    sf::CircleShape redBulb;
    sf::CircleShape greenBulb;

    void updateVisuals();

public:
    PedestrianLight(std::string startPhase, float x, float y, bool isHorizontal = false);

    void changeColour() override;
    void setModeState(const std::string& state) override;
    void restoreNormalState() override;
    void forceGreen() override;
    void resetLight() override;
    float getStateDuration() const override;
    void draw(sf::RenderWindow& window) override;
    std::string getColour() const override;
};