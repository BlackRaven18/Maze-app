#include "Engine.h"
#include <iostream>

Engine::Engine() {};

void Engine::start() {
	initialize();
	startMainLoop();
}

void Engine::updateMousePosition() {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPos);
}

void Engine::initializeMazeTable() {
	for (int i = 0; i < MAZE_TABLE_WIDTH; i++) {
		for (int j = j = 0; j < MAZE_TABLE_HEIGHT; j++) {
			mazeTable[i][j].setPosition(i * MAZE_TABLE_CELL_SIZE, j * MAZE_TABLE_CELL_SIZE);
			mazeTable[i][j].setSize(MAZE_TABLE_CELL_SIZE, MAZE_TABLE_CELL_SIZE);
			mazeTable[i][j].setColor(MAZE_BACKGROUND_COLOR);
		}
	}
}

void Engine::initializeButtons() {
	//font.loadFromFile("arial.ttf");
	//textButton = Button("Reset", sf::Vector2f(100, 630), font, sf::Color::Black, sf::Color::White,sf::Color::Black, sf::Vector2f(100, 50));
	buttonsTextures.resize(BUTTONS_NUM);
	buttonsTextures[0].loadFromFile("Textures/start.png");
	buttonsTextures[1].loadFromFile("Textures/restart.png");
	buttonsTextures[2].loadFromFile("Textures/boxwhite.png");
	buttonsTextures[3].loadFromFile("Textures/boxgreen.png");
	buttonsTextures[4].loadFromFile("Textures/boxred.png");

	buttonsPos = { {100,630}, {250,630}, {1100, 200}, {1100,300}, {1100,400} };
	buttonsSizes = { {100,50}, {100,50}, {72,72}, {72,72}, {72,72} };

	buttons.resize(BUTTONS_NUM);
	for (int i = 0; i < BUTTONS_NUM; i++) {
		buttons[i] = Button(buttonsTextures[i], buttonsPos[i], sf::Color::White, buttonsSizes[i]);
	}
}

void Engine::initialize() {
	this->window = new sf::RenderWindow(sf::VideoMode(APP_WIDTH, APP_HEIGHT), APP_TITLE);

	initializeMazeTable();
	initializeButtons();
}

void Engine::startMainLoop() {
	while (window->isOpen()) {
		update();
		draw();
	}
}

void Engine::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			window->close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{

			if (buttons[1].isClicked(window))
			{
				for (int i = 0; i < MAZE_TABLE_WIDTH; i++) {
					for (int j = j = 0; j < MAZE_TABLE_HEIGHT; j++) {
						mazeTable[i][j].setColor(sf::Color::White);
					}
				}
			}
		}

		//if (event.type == sf::Event::Resized)
		//{
		//	// update the view to the new size of the window
		//	sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		//	window -> setView(sf::View(visibleArea));
		//}
	}
}

void Engine::update() {
	handleEvents();
	updateMousePosition();
}



void Engine::draw() {
	window->clear(BACKGROUND_COLOR);

	drawMazeTable();
	drawMaze();

	for (auto b : buttons) {
		window->draw(b);
	}

	window->display();
}

void Engine::drawMaze()
{

	//TODO: napisa� funkcje kt�ra sprawdzi czy punkt(albo myszka) jest aktualnie wewn�trz danego obszaru; przyda sie do 
	//sprawdzania czy myszka jest na obszarze do rysowania i do znalezienia elementu tablicy do pokolorowania 
	
	//checking if mouse is on the maze board

	if (mousePosition.x > MAZE_TABLE_WIDTH * MAZE_TABLE_CELL_SIZE && mousePosition.y > MAZE_TABLE_HEIGHT * MAZE_TABLE_CELL_SIZE) {
		return;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return;
	}

	int i = mousePosition.x / MAZE_TABLE_CELL_SIZE;
	int j = mousePosition.y / MAZE_TABLE_CELL_SIZE;

	if (i < MAZE_TABLE_WIDTH && j < MAZE_TABLE_HEIGHT)
		mazeTable[i][j].setColor(sf::Color::Green);
}

void Engine::drawMazeTable() {
	for(int i = 0; i < MAZE_TABLE_WIDTH; i++)
		for (int j = 0; j < MAZE_TABLE_HEIGHT; j++) {
			mazeTable[i][j].draw(window);

		}

}

sf::RectangleShape Engine::createRectangle(int x, int y, int width, int height, sf::Color color) {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(color);
	return rectangle;
}