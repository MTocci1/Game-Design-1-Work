#pragma once
#include <SFML/Graphics.hpp>
#include "Observer.h"
#include "Event.h"

using namespace sf;

class Hud: public Observer
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_TimeText;
	Text m_LevelText;

	int levelNumber;
public:
	Hud();

	Text getMessage();

	Text getLevel();

	Text getTime();

	void setLevel(String text);

	void setTime(String text);

	void onNotify(::Event const& ev);
};