#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <map>
#include <vector>
#include "Signal.h"
#include "Timer.h"

enum class TrafficMode { Regular, Emergency, Maintenance };

class Intersection {
private:
    std::map<std::string, Signal*> lights;
    Timer<float> cycleTimer;
    Timer<float> blinkTimer;
    float speedMultiplier;

    TrafficMode currentMode;
    bool blinkState;

    bool isGlitched;
    std::string resetBuffer;

    std::vector<std::string> eventLogs;

public:
    Intersection();
    ~Intersection();

    TrafficMode getMode() const;
    bool isSystemGlitched() const;
    const std::vector<std::string>& getLogs() const;

    void logEvent(const std::string& message);
    void addLight(const std::string& name, Signal* light);
    void loadConfiguration(const std::string& filename);
    void setMode(int modeInput);
    void triggerGlitch();
    void processResetCode(sf::Keyboard::Key key);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};