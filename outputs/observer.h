#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Subject;
#include <memory>

class Observer
{
public:
    virtual void notify() = 0;
    virtual void setSubject(std::shared_ptr<Subject> subject, std::shared_ptr<Observer> o) = 0;
    virtual ~Observer() = default;
};
#endif
