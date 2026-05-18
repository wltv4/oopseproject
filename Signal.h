#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Signal {
public:
    virtual ~Signal() = default;

    virtual void changeColour() = 0;
    virtual float getStateDuration() const = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual std::string getColour() const = 0;

    virtual void setModeState(const std::string& state) = 0;
    virtual void restoreNormalState() = 0;

    virtual void forceGreen() = 0;
    virtual void resetLight() = 0;
};