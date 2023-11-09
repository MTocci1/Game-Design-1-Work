#ifndef HPP_BEE_STATES
#define HPP_BEE_STATES

#include "Bee.hpp"

struct Bee::State
{
	State(Bee& bee);
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual State* handleEvent(TriggerEvent const&) = 0;
	virtual void update(float dt) = 0;
	Bee& controlledBee;
};

// TODO Declare the inner-structs for the Bee states here
struct Bee::idleState : public Bee::State {
	idleState(Bee& bee);
	void enter();
	void exit();
	State* handleEvent(TriggerEvent const&);
	void update(float dt);
};

struct Bee::orbitState : public Bee::State {
	orbitState(Bee& bee);
	void enter();
	void exit();
	State* handleEvent(TriggerEvent const&);
	void update(float dt);
};

struct Bee::wanderState : public Bee::State {
	wanderState(Bee& bee);
	void enter();
	void exit();
	State* handleEvent(TriggerEvent const&);
	void update(float dt);
};

#endif HPP_BEE_STATES
