# Traffic Light Controller
A simulated intersection with four synchronised traffic lights.

## Table of contents
* [Intro] (#intro)
* [How to run] (#how-to-run)
* [3.0 requirements] (#3.0-requirements)
* [3.5 requirements] (#3.5-requirements)
* [4.0 requirements] (#4.0-requirements)
* [4.5 requirements] (#4.5-requirements)
* [5.0 requirements] (#5.0-requirements)
* [Authors] (#authors)

## Intro
This programme is a simulation of an intersection. The simulation uses an SFML graphic library, a customisable configuration file and adapts to user input.

## How to run
* The programme requires CMake, a C++17 compatible compiler and SFML3 library configured (the programme was done in CLion IDE).
* Before running, ensure the font file COMIC.TTF is placed in the cmake-build-debug folder.
* **Optional:** A config.txt file may be placed in the same folder containing a single float value to alter the simulation speed.
* The controls are listed in the top right corner of the screen. The bottom right corner displays the console outputs.
* The simulation can work in four states:
  1. **Regular mode:** standard traffic cycle
  2. **Emergency mode:** blinking yellow lights
  3. **Maintenance mode:** all lights off
  4. **Glitch:** can be used to force the northernmost light to turn green. If the light is supposed to be red or yellow at the time the glitch is introduced, the simulation should go into emergency mode and a special code (2137) will be required to reset the system.
* Press Esc to exit the simulation

## 3.0 requirements
* **At least one class with attributes and methods:** Implemented via the VehicleLight and PedestrianLight classes, which possess attributes like shapes and colours, and methods to update their visual states.
* **Working main functionality & logic in functions:** The rendering and event polling loops are separated from the core logic, which is handled by class methods.
* **Encapsulation & Constructors:** All classes utilise private attributes that can only be modified through public methods. Constructors are used to initialise positions, sizes, and starting colours.
* **Use of references in functions:** Rendering methods utilise sf::RenderWindow& window to pass the heavy window object by reference rather than by value.

## 3.5 requirements
* **Interaction between objects (A second class):** The Intersection class acts as a central manager. It owns the individual light objects and commands them to update and draw synchronously.
* **STL Container:** The lights are stored within an STL container to allow for dynamic management rather than hardcoding individual variables.
* **Destructors & Pointers:** The programme dynamically allocates the lights using new and passes their pointers to the controller. The Intersection class contains a custom destructor that iterates through the container and calls delete to prevent memory leaks.
* **Handling basic edge cases:** The update loops contain .empty() checks to ensure the programme does not crash if it attempts to update an intersection with no registered lights.

## 4.0 requirements
* **Use of an STL Algorithm:** Implemented std::count_if to actively monitor the state of the intersection.
* **Dynamic Memory Management:** Fully realised through the combination of base class pointers, new keyword allocations, and explicit heap cleanup.

## 4.5 requirements
* **Separation into multiple files:** The codebase is properly divided into main, header and class files to ensure modularity.
* **Inheritance and Polymorphism:** Introduced an abstract base class called Signal with pure virtual methods. Both VehicleLight and PedestrianLight inherit from this base class, allowing the Intersection controller to store a single collection of pointers and trigger polymorphic behaviour.
* **Use of additional STL containers:** Utilised maps to store the lights with string-based keys, alongside a vector to manage the rolling on-screen event log.
* **A Reusable Component:** The timing logic was abstracted into a standalone Timer class that could easily be exported and reused in any other time-dependent C++ application.

## 5.0 requirements
* **Use of Class Templates:** The reusable Timer class was upgraded to a template class Timer<T>, allowing it to be instantiated with float for standard tracking or double for microsecond tracking.
* **Multiple STL Algorithms:** * std::count_if is used critically as a safety failsafe, scanning the map every frame to detect if more than 4 lights are green at the same time. std::for_each is used alongside lambda expressions to replace standard loops during the rendering phase.
* **Basic File Handling:** Added a loadConfiguration() method that reads a config.txt file at startup to dynamically set the simulation's speed multiplier.
* **Exception Handling (try/catch):** The programme handles missing files. If config.txt or the required .ttf font file is missing or corrupted, the programme throws an std::runtime_error, catches it, prints a warning to the dashboard, and safely falls back to default settings without crashing.

## Authors
Paweł Duda & Mieszko Karski

![Concept art](https://github.com/wltv4/oopseproject/blob/main/Traffic_lights.png)
