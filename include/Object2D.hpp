// # 
// # @Autho: Estenio Garcia
// # 
// # Date of Creation: 04/19/2021
// # 

#pragma once

#include <SFML/Graphics.hpp>

class Object2D{

public:
	float posx, posy, width, height;
	float velocity;

	sf::Texture texture;
	sf::Sprite sprite;

	// # Functions
	virtual void Update() = 0;
	virtual sf::Sprite* getSprite() = 0; 
};