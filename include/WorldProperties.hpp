#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class WorldProperties{

public:
	int earthHP;
	int level;

	bool PlayerWin = false;

	sf::Texture tex;
	sf::Texture texWin;
	sf::Texture texFail;

	sf::Sprite sprite;

	sf::Text displayText;
	sf::Text displayTextLevel;

	sf::SoundBuffer sbuffer_Environment;
	sf::SoundBuffer sbuffer_GameOver;
	sf::SoundBuffer sbuffer_PlayerWin;
	sf::SoundBuffer sbuffer_VictoryIsComing;

	sf::Sound speakerMusic;

	explicit WorldProperties(sf::Font& pfont){

		earthHP = 100;
		level = 1;

		tex.loadFromFile("../resource/EarthBackground.jpg");
		texWin.loadFromFile("../resource/EarthBackgroundWin.jpg");
		texFail.loadFromFile("../resource/EarthBackgroundEnd.jpg");

		sprite.setTexture(tex);

		this->displayText.setFont(pfont);
		this->displayText.setCharacterSize(14);
		this->displayText.setFillColor(sf::Color::Blue);

		this->displayText.setString("Earth: "+ std::to_string(this->earthHP));

		this->displayText.setPosition(600, 10);

		this->displayTextLevel.setFont(pfont);
		this->displayTextLevel.setCharacterSize(14);
		this->displayTextLevel.setFillColor(sf::Color::White);

		this->displayTextLevel.setString("Level: "+ std::to_string(this->level));

		this->displayTextLevel.setPosition(300, 10);

		this->sbuffer_Environment.loadFromFile("../sfx/Environment.wav");
		this->sbuffer_GameOver.loadFromFile("../sfx/GameOver.wav");
		this->sbuffer_PlayerWin.loadFromFile("../sfx/PlayerWin.wav");
		this->sbuffer_VictoryIsComing.loadFromFile("../sfx/VictoryIsComing.wav");

		this->speakerMusic.setBuffer(sbuffer_Environment);
		this->speakerMusic.setVolume(40);
		this->speakerMusic.setLoop(true);
		this->speakerMusic.play();
	}

	void Update(){

		this->displayTextLevel.setString("Level: "+ std::to_string(this->level));
	}

	void applyDamage(){

		if(this->PlayerWin == false){
			this->earthHP -= 5;

			if(this->earthHP <= 0){
				earthHP = 0;
				this->sprite.setTexture(texFail);
				this->speakerMusic.setBuffer(sbuffer_GameOver);
				this->speakerMusic.play();
			}
		}

		this->displayText.setString("Earth: "+ std::to_string(this->earthHP));

	}

	void addLevel(){

		this->level++;

		if(this->level == 5){
			this->speakerMusic.setBuffer(sbuffer_VictoryIsComing);
			this->speakerMusic.setVolume(80);
			this->speakerMusic.play();
		}

		if(this->level >= 7){
			this->sprite.setTexture(texWin);
			this->speakerMusic.setBuffer(sbuffer_PlayerWin);
			this->speakerMusic.play();

			this->PlayerWin = true;
		}
	}

};