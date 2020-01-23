#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}

	text.setFont(font);
	text.setPosition(0, 0);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);

	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineColor(sf::Color::Cyan);
	circle.setRadius(50);
	circle.setPosition(-100, 0);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W)) {
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed" << std::endl;
	}

	if (input->isKeyDown(sf::Keyboard::J) &&
		input->isKeyDown(sf::Keyboard::K) &&
		input->isKeyDown(sf::Keyboard::L)
		) {
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "J, K and L were all pressed" << std::endl;
	}
	
	if (input->isKeyDown(sf::Keyboard::Escape)) {
		exit(0);
	}
}

// Update game objects
void Level::update()
{
	std::string mouseText = "Mouse position: " + 
		std::to_string(input->getMouseX()) + 
		", " + 
		std::to_string(input->getMouseY());

	text.setString(mouseText);

	if (input->isMouseLDown() && !isMouseHeld) {
		isMouseHeld = true;
		holdMouseX = input->getMouseX();
		holdMouseY = input->getMouseY();
	}

	if (!input->isMouseLDown() && isMouseHeld) {
		isMouseHeld = false;
		int distX = abs(holdMouseX - input->getMouseX());
		int distY = abs(holdMouseY - input->getMouseY());

		std::cout << "Mouse distance: " << sqrt(pow(distX, 2) + pow(distY, 2)) << std::endl;
	}

	if (input->isMouseRDown()) {
		input->setMouseRDown(false);
		circle.setPosition(input->getMouseX() - circle.getRadius(), input->getMouseY() - circle.getRadius());
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(text);
	window->draw(circle);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}