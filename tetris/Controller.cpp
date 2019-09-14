#include "Controller.h"

//CONSTRUCTOR
Controller::Controller()
{
	loadFiles();
}

//RUN THE PROGRAM
bool Controller::run(sf::RenderWindow & window)
{

	static sf::Clock clock;
	window.create(sf::VideoMode(width,hight),"Tetris Game");


	insertShape();
	insertShape();
	int counter = 0; 

	while (window.isOpen())
	{
		m_music[0].play();

		while (!checkGameOver())
		{
			defineTool(window);

			window.draw(m_backGroundScreen);
			if (counter == 0)
				drawGetReady(window);
			counter = 1;

			sf::Event Event;
			while (window.pollEvent(Event))
			{
				if (Event.type == sf::Event::Closed)
					window.close();
				if (Event.type == sf::Event::KeyPressed)
					getKey(Event.key.code);
			}

			moveDown(clock);
			draw(window);
			window.display();
			window.clear(sf::Color::White);

			if (checkCollision())
				switchShape();
			levelFinished(window);
		}
		m_music[0].stop();
		return false;
	}
	return true;
}


//DISTRUCTOR
Controller::~Controller()
{
}


//DRAW THE MAIN WINDOW AND SHAPES
void Controller::draw(sf::RenderWindow & window)
{
	m_shapes.front()->draw(window);
	m_board.draw(window);

	for (int i = 0; i <NUM_OF_STATUS_BAR ; i++ )
		window.draw(m_statusBar[i]);

	if(m_level <= 3)
	drawNextShape(window);
}

// DRAW THE NEXT SHAPE OUTSIDE THE BOARD
void Controller::drawNextShape(sf::RenderWindow & window)
{
	Shape nextShape = *m_shapes.back().get();
	nextShape.drawNext(window);		
}


//GET A KEY OF DIRECTION
void Controller::getKey(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Up:
		m_shapes.front()->rotateShape(m_board);
		break;
	case sf::Keyboard::Down:
		m_shapes.front()->move(DOWN, m_board);
		break;
	case sf::Keyboard::Left:
		m_shapes.front()->move(LEFT, m_board);
		break;
	case sf::Keyboard::Right:
		m_shapes.front()->move(RIGHT, m_board);
		break;
	case sf::Keyboard::Space:
		dropShape();
		break;
	}
}

//MOVE DOWN THE RUNNIG SHAPE
void Controller::moveDown(sf::Clock &clock)
{
	if (clock.getElapsedTime().asSeconds() > m_speed)
	{
			m_shapes.front()->move(DOWN,m_board);
			clock.restart();
	}
}

// DEFINES THE TOOL
void Controller::defineTool(sf::RenderWindow & window)
{
	std::string status = "SCORE: " + std::to_string(m_score);
	std::string status1 = " LEVEL: " + std::to_string(m_level); 
	std::string status2 = " NEXT: ";

	m_statusBar[0].setFont(font[0]);
	m_statusBar[0].setColor(sf::Color::Blue);
	m_statusBar[0].setStyle(sf::Text::Bold);
	m_statusBar[0].setPosition(window.getSize().x/2-(leftGap+140), window.getSize().y/6);
	m_statusBar[0].setString(status);
	m_statusBar[0].setCharacterSize(rectSize * 1.5);

	m_statusBar[1].setFont(font[0]);
	m_statusBar[1].setColor(sf::Color::Blue);
	m_statusBar[1].setStyle(sf::Text::Bold);
	m_statusBar[1].setPosition(window.getSize().x / 2-(leftGap+142), window.getSize().y / 2 - 50);
	m_statusBar[1].setString(status1);
	m_statusBar[1].setCharacterSize(rectSize*1.5);

	m_statusBar[2].setFont(font[0]);
	m_statusBar[2].setColor(sf::Color::Blue);
	m_statusBar[2].setStyle(sf::Text::Bold);
	m_statusBar[2].setPosition(window.getSize().x / 2 + (leftGap), window.getSize().y / 6);
	m_statusBar[2].setString(status2);
	m_statusBar[2].setCharacterSize(rectSize*1.5);

}


// DRAW "GET READY" BEFORE STARTING
void Controller::drawGetReady(sf::RenderWindow & window)
{
	std::string getReady;
	float time = 0;
	sf::Clock clock;
	clock.restart();
	m_getReady.setColor(sf::Color::Cyan);
	m_getReady.setCharacterSize(width / 10);
	m_getReady.setOutlineColor(sf::Color::Blue);
	m_getReady.setOutlineThickness(3);
	for (int i = 0; i < 3;)
	{
		getReady = "GET READY!  " + std::to_string(3 - i);
		time += clock.getElapsedTime().asSeconds();
		draw(window);
		m_getReady.setPosition(window.getSize().x /2, (window.getSize().y / 2));
		m_getReady.setString(getReady);
		window.draw(m_getReady);
		window.display();
		window.clear();
		if (time >= 45)
		{
			i++;
			time = 0;
			clock.restart();
		}
	}
}


//DRAWING "NEXT LEVEL" AFTER EVERY FINISHED LEVEL
void Controller::drawNextLevel(sf::RenderWindow & window)
{
	m_music[0].play();

	std::string getReady;
	float time = 0;
	sf::Clock clock;
	clock.restart();
	m_getReady.setColor(sf::Color::White);
	m_getReady.setCharacterSize(width / 10);
	m_getReady.setOutlineColor(sf::Color::Blue);
	m_getReady.setOutlineThickness(3);
	for (int i = 0; i < 3;)
	{
		getReady = "NEXT LEVEL!  " + std::to_string(3 - i);
		time += clock.getElapsedTime().asSeconds();
		draw(window);
		m_getReady.setPosition((window.getSize().x / 2) - 140
			, (window.getSize().y / 2) - 120);
		m_getReady.setString(getReady);
		window.draw(m_getReady);
		window.display();
		window.clear();

		if (time >= 45)
		{
			i++;
			time = 0;
			clock.restart();
		}
	}

}

//UPDATING THE PROGRRAM AFTER THE LEVEL FINISHED
void Controller::levelFinished(sf::RenderWindow & window)
{
	if (m_level < m_score / MAX_LEVEL_POINTS + 1)
	{
		m_level = m_score / MAX_LEVEL_POINTS + 1;
		m_speed -= 0.1;

		m_music[0].pause();
		m_music[2].play();

		drawNextLevel(window);

	}
}

//CHECKS IF THE GAME IS OVER
bool Controller::checkGameOver()
{
	return m_shapes.front()->isOver(checkCollision());
}

// DROP SHAPE
void Controller::dropShape()
{
	while(!checkCollision())
		m_shapes.front()->move(DOWN, m_board);
	switchShape();
}

//ENTERED THE NEXT SHAPE TO THE GAME
void Controller::switchShape()
{
	m_shapes.pop();
	insertShape();
	m_score = m_board.getScore();
}

//CHECK COLLISION OF THE CURRENT SHAPE
bool Controller::checkCollision()
{
	return m_board.checkCollision(m_shapes.front()->getRects());
}

//INSERT SHAPES TO THE QUEUE
void Controller::insertShape()
{
	int shapeNumber = rand() % 7;
	switch (shapeNumber)
	{
	case 0:
		m_shapes.push(std::make_unique<I>());
		break;
	case 1:
		m_shapes.push(std::make_unique<J>());
		break;
	case 2:
		m_shapes.push(std::make_unique<L>());
		break;
	case 3:
		m_shapes.push(std::make_unique<O>());
		break;
	case 4:
		m_shapes.push(std::make_unique<S>());
		break;
	case 5:
		m_shapes.push(std::make_unique<T>());
		break;
	case 6:
		m_shapes.push(std::make_unique<Z>());
		break;
	default:
		break;
	}
	
}

//LOAD FILES
void Controller::loadFiles()
{
	if (!font[0].loadFromFile("fonts/gameFont.otf"))
		std::cout << "COULD NOT LOAD FONT!";

	if (!m_texture.loadFromFile("screens/backGround.jpg"))
		std::cout << "COULD NOT LOAD SCREEN!";

	m_getReady.setFont(font[0]);
	font[1].loadFromFile("fonts/getReadyFont.otf");
	
	m_backGroundScreen.setTexture(m_texture);
	
	m_music[0].openFromFile("sounds/toy.wav");
	m_music[1].openFromFile("sounds/breakRow.wav");
	m_music[2].openFromFile("sounds/nextLevel.wav");
	m_music[3].openFromFile("sounds/dead.wav");


	for (int i=0 ; i<NUM_OF_MUSIC ; i++)
		m_music[i].setVolume(70);

}
