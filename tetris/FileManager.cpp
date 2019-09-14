#include "FileManager.h"

//................The file manager consructor - the singeltone!...
// used for loading all the critic files, as sounds, imaegs
// and screens.
// this is the singeltone class
FileManager::FileManager()
{
	// loading images

	//  loading screens
	m_pScreeen[MENU_m].loadFromFile("screens/menu.jpg");
	m_pScreeen[GAME_OVER_m].loadFromFile("screens/game_is_over.jpg");

	// loading sounds 

	m_font[GAME_FONT].loadFromFile("fonts/gameFont.otf");
	m_font[GET_READY_FONT].loadFromFile("fonts/getReadyFont.otf");
	m_gameSounds[LVL_UP].loadFromFile("sounds/lvl_up.wav");
	m_gameSounds[GAME_IS_OVER].loadFromFile("sounds/game_over.wav");

}



sf::Font * FileManager::getFont(size_t type)
{
		return &m_font[type];
}

// this function used for getting the sounds for the game 
// sounds as eating cookies, dead etc.
sf::SoundBuffer * FileManager::getGameSound(size_t type)
{
	return &m_gameSounds[type];
}
//................func 6..............
// this function used for getting the sounds for the game
FileManager & FileManager::instance()
{
	static FileManager instance;
	return instance;
}

// this function used for getting screens, along the program
sf::Texture * FileManager::getScreen(size_t screen)
{
	return &m_pScreeen[screen];
}


