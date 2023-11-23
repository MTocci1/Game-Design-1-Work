#pragma once

#include <set>
#include "Observer.h"

/// <summary>
/// Interface for objects that are observed by other objects.
/// </summary>
class Subject {
public:
    /// <summary>
    /// Register a new observer object watching this subject.
    /// </summary>
    /// <param name="o">an object interested in changes to this subject</param>
    void addObserver(Observer&);

    /// <summary>
    /// Remove the given observer from the list of watchers for this subject.
    /// </summary>
    /// <param name="o">an object no longer interested in changes to this subject</param>
    void removeObserver(Observer&);

    /// <summary>
    /// Notify all observers watching this object of any events on this subject.
    /// </summary>
    virtual void notify(::Event&);

private:
    // Note: vector<> and list<> are also possible choices here depending on our needs
    std::set<Observer*> observers;
};