#ifndef HPP_EVENT
#define HPP_EVENT

#include <string>
#include "Subject.hpp"

class Subject;

/// <summary>
/// Simple object encapsulating data about an event.
/// </summary>
struct Event {
    Event(Subject&, std::string const& name);

    Subject& source;
    std::string name;
    // TODO a useful event would probably store other kinds of data also
};

#endif HPP_EVENT