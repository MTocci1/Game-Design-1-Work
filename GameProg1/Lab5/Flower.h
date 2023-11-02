#ifndef H_FLOWER
#define H_FLOWER

#include "gameObject.h"
#include <SFML/System/Vector2.hpp>

class Flower : public GameObject 
{
public:
	Flower(sf::Vector2f const&);
	void update(sf::Time const&);
};

#endif H_FLOWER