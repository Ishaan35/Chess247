#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "outputs/observer.h"

class Observer;

class Subject
{
    std::vector<std::weak_ptr<Observer>> observers; // application will clean up the observers. Subject doesn't own the observers

public:
    void attach(std::weak_ptr<Observer> o);
    void detach(std::weak_ptr<Observer> o);
    void notifyObservers();
    virtual ~Subject() = 0;
};

#endif
