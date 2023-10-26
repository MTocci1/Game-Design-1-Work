#include "Observer.hpp"
#include "Event.hpp"

#include <iostream>

void Observer::onNotify(Event const& ev) {
    std::cout << "Responding to event '" << ev.name
        << "' from subject (" << (&ev.source)
        << ")" << std::endl;
}