#include "Event.hpp"

Event::Event(Subject& sub, std::string const& name)
    : source(sub), name(name) {}