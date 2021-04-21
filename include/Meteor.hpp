#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../include/Object2D.hpp"
#include "../include/Player.hpp"
#include "../include/WorldProperties.hpp"

class MeteorProjectile : public Object2D{

public:

	MeteorProjectile(sf::Texture& tex, float& pvel);

	void Update() override ;

	sf::Sprite* getSprite(){
		return &this->sprite;
	}

};

class MeteorManager{


public:

	int l, k;

	bool doOnce = false;

	sf::Texture meteorTex;

	std::vector<MeteorProjectile> meteorList;

	WorldProperties* wp;

	float pvel = 0.05f;

	sf::SoundBuffer sbuffer_MeteorExplision;
	sf::SoundBuffer sbuffer_OverlapPlayer;
	sf::SoundBuffer sbuffer_LevelUp;

	sf::Sound eventSound;
	sf::Sound eventSound_LevelUP;

	explicit MeteorManager(WorldProperties* wp){

		this->meteorTex.loadFromFile("../resource/Meteor.png"); 
		this->wp = wp;

		sbuffer_MeteorExplision.loadFromFile("../sfx/MeteorExplosion.wav");
		sbuffer_OverlapPlayer.loadFromFile("../sfx/PlayerCollide.wav");
		sbuffer_LevelUp.loadFromFile("../sfx/LevelUp.wav");

		eventSound.setBuffer(sbuffer_OverlapPlayer);

		eventSound.setVolume(100);
		eventSound_LevelUP.setVolume(100);
	}

	void isOverlap(Player* player){

		for(l = 0; l < meteorList.size(); l++){

			// # Checking if overlap in player
			if(meteorList[ l ].posx < player->posx + player->width &&
			   meteorList[ l ].posx + meteorList[ l ].width > player->posx &&
			   meteorList[ l ].posy < player->posy + player->height &&
			   meteorList[ l ].posy + meteorList[ l ].height > player->posy ){

				if(doOnce == false){

					eventSound.setBuffer(sbuffer_OverlapPlayer);
					eventSound.setVolume(100);
					eventSound.play();

					meteorList.erase(meteorList.begin() + l);
					player->applyDamage();
					doOnce = true;
				}
			}

			// # Checking if overlap in player bullet
			for(k = 0; k < player->bulletList.size(); k++){
				if(meteorList[ l ].posx < player->bulletList[ k ].posx + player->bulletList[ k ].width &&
				   meteorList[ l ].posx + meteorList[ l ].width > player->bulletList[ k ].posx &&
				   meteorList[ l ].posy < player->bulletList[ k ].posy + player->bulletList[ k ].height &&
				   meteorList[ l ].posy + meteorList[ l ].height > player->bulletList[ k ].posy ){

					eventSound.setBuffer(sbuffer_MeteorExplision);
					eventSound.setVolume(100);
					eventSound.play();

				    meteorList.erase(meteorList.begin() + l);
					player->bulletList.erase(player->bulletList.begin() + k);
					player->score += 3;

					if(player->score >= 100){

						eventSound_LevelUP.setBuffer(sbuffer_LevelUp);
						eventSound_LevelUP.setVolume(100);
						eventSound_LevelUP.play();

						wp->addLevel();
						player->score = 0;
						player->velocity += 0.05f;
						this->pvel += 0.02f;
					}
				}
			}
		}

		doOnce = false;
	}

	void Update(int& caret){

		if(meteorList.size() < 10){

			meteorList.push_back((*new MeteorProjectile(meteorTex, this->pvel)));
		}

		for(caret = 0; caret < meteorList.size(); caret++){

			meteorList[ caret ].Update();

			if( meteorList[ caret ].posy > 700 ){

				meteorList.erase(meteorList.begin() + caret);
				wp->applyDamage();
			}
		}
	}
};