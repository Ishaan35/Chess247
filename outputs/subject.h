#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"

class Observer;

class Subject
{
    std::vector<std::weak_ptr<Observer>> observers;

public:
    void attach(Observer *o);
    void detach(Observer *o);
    void notifyObservers();
    virtual ~Subject() = default;
};

#endif
