// # 
// # @Autho: Estenio Garcia
// # 
// # Date of Creation: 04/19/2021
// # 

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../include/Object2D.hpp"
#include "../include/Projectile.hpp"

class Player : public Object2D{

public:

	// # Variables
	float speedX, speedY;
	float projectileDirection;

	bool doOnce = false;
	bool* inputKey;
	bool isDead = false;
	bool playerWin = false;

	int i;
	int HP, score;

	sf::Texture texBullet;
	sf::Text displayText;
	sf::Text displayTextScore;

	std::vector<Projectile> bulletList;

	sf::SoundBuffer sbuffer_fire;

	sf::Sound gunfire;

	explicit Player(bool* movement, sf::Font& font);
	~Player();

	void Update() override;

	sf::Sprite* getSprite() override{
		return &sprite;
	}

	void shot(){
		bulletList.push_back((*new Projectile(this->posx, this->posy, this->texBullet, this->projectileDirection)));
		this->gunfire.play();
	}

	void applyDamage();

	//Not implemented
	bool isOverlap(Object2D* object);

};