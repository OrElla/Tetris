#include "Screens.h"
//CONSTRUCTOR 
Screens::Screens()
{
	loadScreens();
}

//LOAD THE GAME'S SCREENS
void Screens::loadScreens()
{
	if (!m_screens[0].loadFromFile("screens/menu.jpg"))
		std::cout << "COULD NOT LOAD SCREEN!";
	if (!m_screens[1].loadFromFile("screens/backGround.jpg"))
		std::cout << "COULD NOT LOAD SCREEN!";
	if (!m_screens[2].loadFromFile("screens/game_is_over.jpg"))
		std::cout << "COULD NOT LOAD SCREEN!";

	for (int i=0 ; i<NUM_OF_SCREENS ; i++)
		gameScreens[i].setTexture(m_screens[i]);

	dead_music.openFromFile("sounds/dead.wav");
	dead_music.setVolume(70);
}

//RUNING THE MENU SCREEN
void Screens::runMenu()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(610, 610), "Tetris");
	menu(window);
}

//MENU OF THE PROGRRAM
void Screens::menu(sf::RenderWindow & window)
{
	dead_music.play();

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Menu_t button = getMenuButton(sf::Vector2i(event.mouseButton.x,
						event.mouseButton.y));
					switch (button)
					{		
					case PLAY_t:
					{
						dead_music.stop();
						GameIsOver = m_gameController.run(window);
						if (!GameIsOver)
							gameOver(window);
						break;
					}
					case EXIT_t:
						window.close();  //exit the game 
						break;
					case SOUND_t:
						//checkSound();
						break;

					default:
						break;
					}
				}
				break;
			}
		}
		window.draw(gameScreens[0]);//draw the menu's screen
		window.display();
		window.clear();
	}
}

//THE MENU SCREEN - ASKS FOR OPERATION
Menu_t Screens::getMenuButton(sf::Vector2i buttonPos)
{
	if (buttonPos.x > 169 && buttonPos.x < 438
		&& buttonPos.y > 304 && buttonPos.y < 343)
		return PLAY_t;

	else if (buttonPos.x > 240 && buttonPos.x < 416 &&
		buttonPos.y > 400 && buttonPos.y < 437)
		return EXIT_t;

	else if (buttonPos.x > 570 && buttonPos.x < 591 &&
		buttonPos.y > 579 && buttonPos.y < 599)
		return SOUND_t;
}

//GAME OVER SCREEN - ASKS FOR OPERATION

GAME_OVER_f Screens::getGoButton(sf::Vector2i buttonPos)
{

	if (buttonPos.x > 169 && buttonPos.x < 443
		&& buttonPos.y > 300 && buttonPos.y < 344)
	{
		std::cout << "play again";
		return PLAY_f;
	}

	else if (buttonPos.x > 240 && buttonPos.x < 416 &&
		buttonPos.y > 400 && buttonPos.y < 437)
		return EXIT_f;

	else if (buttonPos.x > 560 && buttonPos.x < 591 &&
		buttonPos.y > 574 && buttonPos.y < 599)
		return SOUND_f;
}

//GAME OVER OF THE PROGRRAM

void Screens::gameOver(sf::RenderWindow & window)
{
	dead_music.play();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					GAME_OVER_f button = getGoButton(sf::Vector2i(event.mouseButton.x,
						event.mouseButton.y));
					switch (button)
					{
					case PLAY_f:
					{
						Controller NEW;

						dead_music.stop();
						NewGame = NEW.run(window);
						if (!NewGame)
							gameOver(window);
						break;
					}
					case EXIT_f:
						window.close();  //exit the game 
						break;
					case SOUND_f:
						//checkSound();
						break;
					}

				}
			}
			window.draw(gameScreens[2]);
			window.display();
			window.clear();

		}
	}
}


Screens::~Screens()
{
}
