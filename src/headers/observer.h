//src/headers/observer.h
#ifndef PROYECTO_PROGRAMACION3_OBSERVER_H
#define PROYECTO_PROGRAMACION3_OBSERVER_H

#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

#endif