#pragma once
struct Event;

/// <summary>
/// Interface for objects that watch for changes to another object.
/// </summary>
class Observer {
public:
    /// <summary>
    /// Respond to a notification from the subject under observation.
    /// </summary>
    /// <param name="ev">information about what happened to the subject</param>
    virtual void onNotify(::Event const&) = 0;
};