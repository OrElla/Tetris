
#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include"SFML\Window.hpp"
#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "Shape.h"

using std::string;

const int NUM_OF_SOUNDS = 6;
const int NUM_OF_SCREENS = 2;
//const int NUM_OF_ICONS = 4;
const int NUM_OF_FONTS = 2;




class FileManager
{
public:
	sf::Font * getFont(size_t type);
	sf::SoundBuffer * getGameSound(size_t type);
	static FileManager & instance();
	sf::Texture * getScreen(size_t screen);

private:
	FileManager();
	//sf::Texture m_pTexture[NUM_OF_ICONS];
	sf::Texture m_pScreeen[NUM_OF_SCREENS];

	sf::Texture m_lifeCount;
	sf::Font m_font[NUM_OF_FONTS];
	sf::SoundBuffer m_pacmanSounds[NUM_OF_SOUNDS - 2];
	sf::SoundBuffer m_gameSounds[NUM_OF_SOUNDS - 4];

};