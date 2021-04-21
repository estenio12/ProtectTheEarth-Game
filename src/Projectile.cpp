// # 
// # @Autho: Estenio Garcia
// # 
// # Date of Creation: 04/19/2021
// # 

#include <iostream>

#include "../include/Projectile.hpp"

Projectile::Projectile(float p_posx, float& p_posy, sf::Texture& texture, float& projectileDirection){

	this->posx = p_posx + ( 130 / 3 );
	this->posy = p_posy;

	velocity = projectileDirection;

	this->sprite.setTexture(texture);
	this->sprite.setPosition(posx, posy);

	sf::Vector2u size = texture.getSize();

	this->width = size.x;
	this->height = size.y;
}

void Projectile::Update(){

	this->posy += velocity;

	this->sprite.setPosition(this->posx, this->posy);
}
