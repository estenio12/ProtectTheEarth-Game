// # 
// # @Autho: Estenio Garcia
// # 
// # Date of Creation: 04/19/2021
// # 

#include <iostream>

#include "../include/Player.hpp"

Player::Player(bool* movement, sf::Font& font){

	this->inputKey = movement;

	HP = 100;
	score = 0;

	posx = 300;
	posy = 430;

	velocity = 0.2f;
	speedX = 0;
	speedY = 0;
	projectileDirection = -1.5f;

	if(!texture.loadFromFile("../resource/ship2.png"))
		std::cerr << "Error: Cannot load player sprite!" << std::endl;

	if(!texBullet.loadFromFile("../resource/PlayerBullet.png"))
		std::cerr << "Error: Cannot load bullet sprite!" << std::endl;

	sprite.setTexture(texture);
	sprite.setPosition(posx, posy);

	sf::Vector2u bounds = texture.getSize();

	width = bounds.x;
	height = bounds.y;

	// # HUD assets
	this->displayText.setFont(font);
	this->displayText.setCharacterSize(14);
	this->displayText.setFillColor(sf::Color::Green);

	this->displayText.setString("Health: "+ std::to_string(this->HP));

	this->displayText.setPosition(10, 10);

	this->displayTextScore.setFont(font);
	this->displayTextScore.setCharacterSize(14);
	this->displayTextScore.setFillColor(sf::Color::Yellow);

	this->displayTextScore.setString("Score: "+ std::to_string(this->HP));

	this->displayTextScore.setPosition(10, 40);

	// # Audio Load
	this->sbuffer_fire.loadFromFile("../sfx/Shot1.wav");

	this->gunfire.setBuffer(sbuffer_fire);
	this->gunfire.setVolume(30);
}

void Player::Update(){


	if(inputKey[0])
		this->speedY = -velocity;
	if(inputKey[1])
		this->speedY = velocity;
	if(inputKey[2])
		this->speedX = -velocity;
	if(inputKey[3])
		this->speedX = velocity;
	if(inputKey[4])
		if(doOnce == false)
			this->shot();
			this->doOnce = true;

	this->posx += speedX;
	this->posy += speedY;

	if(this->posx > 570){
		this->posx = 570;
	}
	if(this->posx < 0){
		this->posx = 0;
	}
	if(this->posy > 470){
		this->posy = 470;
	}
	if(this->posy < 0){
		this->posy = 0;
	}

	sprite.setPosition(this->posx, this->posy);

	if(!inputKey[0])
		this->speedY = 0;
	if(!inputKey[1])
		this->speedY = 0;
	if(!inputKey[2])
		this->speedX = 0;
	if(!inputKey[3])
		this->speedX = 0;
	if(!inputKey[4])
		this->doOnce = false;


	// # Checking if bullet is out screen and delete object

	for(i = 0; i < bulletList.size(); i++){

		if(bulletList[ i ].posy < 0){
			bulletList.erase(bulletList.begin() + i);
		}
	}

	this->displayText.setString("Health: "+ std::to_string(this->HP));
	this->displayTextScore.setString("Score: "+ std::to_string(this->score));
}

void Player::applyDamage(){

	if(this->playerWin == false){
		this->HP -= 10;

		if(this->HP <= 0){

			this->isDead = true;
		}
	}
}