#include "Intersection.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

Intersection::Intersection() {
    speedMultiplier = 1.0f;
    currentMode = TrafficMode::Regular;
    blinkState = false;
    isGlitched = false;
    resetBuffer = "";
    logEvent("System initialised.");
}

Intersection::~Intersection() {
    for (std::map<std::string, Signal*>::iterator it = lights.begin(); it != lights.end(); ++it) {
        delete it->second;
    }
}

TrafficMode Intersection::getMode() const { return currentMode; }
bool Intersection::isSystemGlitched() const { return isGlitched; }
const std::vector<std::string>& Intersection::getLogs() const { return eventLogs; }

void Intersection::logEvent(const std::string& message) {
    eventLogs.push_back("> " + message);
    std::cout << message << "\n";
    if (eventLogs.size() > 6) {
        eventLogs.erase(eventLogs.begin());
    }
}

void Intersection::addLight(const std::string& name, Signal* light) {
    if (light != nullptr) lights[name] = light;
}

void Intersection::loadConfiguration(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Configuration file missing.");

    std::string multiplierString;
    if (std::getline(file, multiplierString)) {
        try {
            speedMultiplier = std::stof(multiplierString);
            logEvent("Loaded custom speed: " + std::to_string(speedMultiplier));
        } catch (...) {
            throw std::runtime_error("Invalid data in config file.");
        }
    }
}

void Intersection::setMode(int modeInput) {
    if (modeInput == 1) {
        if (isGlitched) {
            logEvent("ACCESS DENIED: System glitched.");
            logEvent("Enter Maintenance (3) to reset.");
            return;
        }
        currentMode = TrafficMode::Regular;
        for (auto& pair : lights) pair.second->restoreNormalState();
        logEvent("Mode changed to: Regular");
    }
    else if (modeInput == 2) {
        currentMode = TrafficMode::Emergency;
        blinkTimer.reset();
        blinkState = false;
        logEvent("Mode changed to: Emergency");
    }
    else if (modeInput == 3) {
        currentMode = TrafficMode::Maintenance;
        resetBuffer = "";
        for (auto& pair : lights) pair.second->setModeState("Off");
        logEvent("Mode changed to: Maintenance");
        if (isGlitched) {
            logEvent("SYSTEM LOCKED: Enter code to reset.");
        }
    }
}

void Intersection::triggerGlitch() {
    if (lights.find("NorthVehicle") != lights.end()) {
        logEvent("Glitch injected! Forcing NorthVehicle to Green...");
        lights["NorthVehicle"]->forceGreen();
    }
}

void Intersection::processResetCode(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::Num2 || key == sf::Keyboard::Key::Numpad2) resetBuffer += "2";
    else if (key == sf::Keyboard::Key::Num1 || key == sf::Keyboard::Key::Numpad1) resetBuffer += "1";
    else if (key == sf::Keyboard::Key::Num3 || key == sf::Keyboard::Key::Numpad3) resetBuffer += "3";
    else if (key == sf::Keyboard::Key::Num7 || key == sf::Keyboard::Key::Numpad7) resetBuffer += "7";
    else resetBuffer = "";

    if (resetBuffer.length() > 4) resetBuffer = resetBuffer.substr(resetBuffer.length() - 4);

    if (resetBuffer == "2137") {
        logEvent("VALID AUTHORIZATION CODE ACCEPTED. Rebooting...");
        isGlitched = false;
        resetBuffer = "";

        for (auto& pair : lights) {
            pair.second->resetLight();
        }
        cycleTimer.reset();
        setMode(1);
    }
}

void Intersection::update(float deltaTime) {
    if (lights.empty()) return;

    if (currentMode == TrafficMode::Regular) {
        cycleTimer.addTime(deltaTime * speedMultiplier);
        float currentPhaseDuration = lights.begin()->second->getStateDuration();

        if (cycleTimer.get() >= currentPhaseDuration) {
            cycleTimer.reset();
            for (auto& pair : lights) {
                pair.second->changeColour();
            }
        }

        int activeGreens = std::count_if(lights.begin(), lights.end(), [](const std::pair<std::string, Signal*>& pair) {
            return pair.second->getColour() == "Green" || pair.second->getColour() == "RedYellow";
        });

        if (activeGreens > 4 && !isGlitched) {
            logEvent("CRITICAL ERROR: Conflicting green lights detected (" + std::to_string(activeGreens) + ")!");
            logEvent("Safety failsafe triggered. Forcing Emergency.");
            isGlitched = true;
            setMode(2);
        }

    }
    else if (currentMode == TrafficMode::Emergency) {
        blinkTimer.addTime(deltaTime);
        if (blinkTimer.get() >= 0.6f) {
            blinkTimer.reset();
            blinkState = !blinkState;

            for (auto& pair : lights) {
                if (pair.first.find("Pedestrian") != std::string::npos) {
                    pair.second->setModeState("Off");
                } else {
                    pair.second->setModeState(blinkState ? "Yellow" : "Off");
                }
            }
        }
    }
}

void Intersection::draw(sf::RenderWindow& window) {
    std::for_each(lights.begin(), lights.end(), [&window](const std::pair<std::string, Signal*>& pair) {
        pair.second->draw(window);
    });
}