// # 
// # @Autho: Estenio Garcia
// # 
// # Date of Creation: 04/20/2021
// # 

#include "../include/Meteor.hpp"

MeteorProjectile::MeteorProjectile(sf::Texture& tex,float& pvel){


	this->posx = ( rand() % 500 ) + 50;
	this->posy = -450 - ( rand() % 250 );

	this->velocity = pvel;

	this->sprite.setTexture(tex);

	sf::Vector2u size = tex.getSize();

	this->width = size.x;
	this->height = size.y;

	this->sprite.setPosition(this->posx, this->posy);
} 

void MeteorProjectile::Update(){

	this->posy += velocity;

	this->sprite.setPosition(this->posx, this->posy);
}