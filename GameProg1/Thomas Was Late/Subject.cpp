#include "Subject.h"
#include "Event.h"

void Subject::addObserver(Observer& o) {
    observers.insert(&o);
}

void Subject::removeObserver(Observer& o) {
    observers.erase(&o);
}

void Subject::notify(Event& ev) {
    for (Observer* o : observers) {
        o->onNotify(ev);
    }
}