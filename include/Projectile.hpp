// # 
// # @Autho: Estenio Garcia
// # 
// # Date of Creation: 04/19/2021
// # 

#include <SFML/Graphics.hpp>

#include "../include/Object2D.hpp"

class Projectile : public Object2D{

public:
	Projectile(float p_posx, float& p_posy, sf::Texture& texture,  float& projectileDirection);
	//~Projectile();

	void Update() override ;

	sf::Sprite* getSprite() override {

		return &this->sprite;
	}

};