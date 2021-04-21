// # 
// # @Autho: Estenio Garcia
// # 
// # Date of Creation: 04/19/2021
// # 

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../include/Player.hpp"
#include "../include/Meteor.hpp"
#include "../include/WorldProperties.hpp"

int main(){

	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(700, 600), "Protect The Earth",sf::Style::Titlebar | sf::Style::Close);

	// # Variables
	static bool input[5];
	static int i, j;

	sf::Font font;
	font.loadFromFile("../font/SuperMario256.ttf");

	// # Instances
	WorldProperties* wp = new WorldProperties(font);
	Player* player = new Player(input, font);
	MeteorManager* meteor = new MeteorManager(wp);

	while(window.isOpen()){

		sf::Event event;

		while(window.pollEvent(event)){

			if(event.type == sf::Event::Closed){
				window.close();
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			input[ 0 ] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			input[ 1 ] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			input[ 2 ] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			input[ 3 ] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			input[ 4 ] = true;

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			input[ 0 ] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			input[ 1 ] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			input[ 2 ] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			input[ 3 ] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			input[ 4 ] = false;

		// # Instances call Update
		player->Update();
		meteor->Update(j);
		wp->Update();

		// # checking if player won the game
		if(wp->PlayerWin == true){
			player->playerWin = true;
		}

		// # Instances checking overlap
		meteor->isOverlap(player);

		for(i = 0; i < player->bulletList.size(); i++){

			player->bulletList[ i ].Update();
		}


		window.clear();

		if(wp->earthHP <= 0 || player->HP <= 0){

			wp->sprite.setTexture(wp->texFail);

			window.draw(wp->sprite);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
				wp->level = 1;
				wp->earthHP = 100;
				wp->sprite.setTexture(wp->tex);
				wp->speakerMusic.setBuffer(sbuffer_Environment);
				wp->speakerMusic.play();

				player->score = 0;
				player->HP = 100;
				player->velocity = 0.2f;
				player->posx = 300;
				player->posy = 430;

				meteor->pvel = 0.05f;
				meteor->meteorList.clear();

			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

				exit(0);
			}

		}else if(wp->level >= 7){

			window.draw(wp->sprite);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){

				exit(0);
			}

		}else{

			window.draw(wp->sprite);
			window.draw(wp->displayText);
			window.draw(wp->displayTextLevel);
			window.draw(player->displayText);
			window.draw(player->displayTextScore);

			for(i = 0; i < meteor->meteorList.size(); i++){

				window.draw(*meteor->meteorList[ i ].getSprite());
			}

			window.draw(*player->getSprite());

			for(i = 0; i < player->bulletList.size(); i++){

				window.draw(*player->bulletList[ i ].getSprite());
			}
		}

		window.display();
	}

	return 0;
}