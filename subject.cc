#include "subject.h"

void Subject::attach(std::weak_ptr<Observer> o)
{
    observers.push_back(o);
}
void Subject::detach(std::weak_ptr<Observer> o)
{
    std::shared_ptr<Observer> oLocked = o.lock();
    for (size_t i = 0; i < observers.size(); i++)
    {
        if (observers[i].lock().get() == oLocked.get())
        {
            observers.erase(observers.begin() + i); // we do not delete as the subject does not own the observer. observer deletion is taken care of in main.
        }
    }
}

void Subject::notifyObservers()
{
    for (auto p : observers)
    {
        // make sure that our weak pointer is pointing to something
        // boolean evaluation of lockedPointer will return true if we are indeed pointing to something safely
        if (auto lockedPtr = p.lock())
        {
            lockedPtr->notify();
        }
    }
}

Subject::~Subject()
{
}
