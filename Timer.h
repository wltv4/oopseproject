#pragma once

template <typename T>
class Timer {
private:
    T elapsedTime;

public:
    Timer() { elapsedTime = static_cast<T>(0); }
    void addTime(T deltaTime) { elapsedTime += deltaTime; }
    void reset() { elapsedTime = static_cast<T>(0); }
    T get() const { return elapsedTime; }
};