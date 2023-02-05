#include "GUI.h"
#include "Entities.h"
#include <map>
#include <stdio.h>

	///////////////////////////
	// Variable Declarations //
	///////////////////////////


typedef sf::Event Action;
static sf::Vector2i prevMousePosition;

static const int window_w = 1000;
static const int window_h = 800;
static const float centerX = (float)(window_w / 2);
static const float centerY = (float)(window_h / 2);

static const float RL_REGION_X = (float)(window_w / 5);
static const float RL_REGION_Y = (float)(window_h / 2);

static const float GAN_REGION_X = (float)(window_w / 2.25);
static const float GAN_REGION_Y = (float)(window_h / 5);

static const float CNN_REGION_X = (float)(window_w / 1.5);
static const float CNN_REGION_Y = (float)(window_h / 2);

static const float RNN_REGION_X = (float)(window_w / 1.175);
static const float RNN_REGION_Y = (float)(window_h / 2);

static const float SNN_REGION_X = (float)(window_w / 2.25);
static const float SNN_REGION_Y = (float)(window_h / 1.25);



	///////////////////////
	// Support Functions //
	///////////////////////


	// Filter Intactions
static inline void queueEvents(Action event, sf::RenderWindow* display) {
	switch (event.type) {
		case Action::MouseWheelMoved: 
		{
			sf::View view{ display->getView() };
			view.zoom((-(float)event.mouseWheel.delta * 0.05f + 1.0f));
			display->setView(view);
			break;
		}
		case Action::MouseButtonPressed: {
			if (event.mouseButton.button == sf::Mouse::Left) {
				// some action
			}
			if (event.mouseButton.button == sf::Mouse::Right) {
				// some menu
			}
			break;
		}
		case Action::MouseMoved: {
			sf::Vector2i newMousePosition = sf::Mouse::getPosition(*display);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
				sf::View view{ display->getView() };
				view.move(sf::Vector2f{ prevMousePosition - newMousePosition });
				display->setView(view);
			}

			prevMousePosition = newMousePosition;
			break;
		}
		case Action::Closed:
		{
			display->close();
			return;
		}
	}
}

void drawObjects(sf::RenderWindow* display) {
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(10, 10)),
		sf::Vertex(sf::Vector2f(150, 150)),
		sf::Vertex(sf::Vector2f(150, 200))
	};

	display->draw(line, 3, sf::Lines);

	for (sf::RectangleShape System : Objects->Systems) {
		display->draw(System);
	}

	for (sf::RectangleShape Line : Objects->Connections) {
		display->draw(Line);
	}

	for (sf::CircleShape Data : Objects->Data) {
		display->draw(Data);
	}

	for (sf::CircleShape Node : Objects->Nodes) {
		display->draw(Node);
	}
}


	// Main Render Loop //
static inline void runRenderLoop(sf::RenderWindow* display) {
	while (display->isOpen()) {
		Action event;

		while (display->pollEvent(event)) {
			queueEvents(event, display);
		}

		display->clear();
		drawObjects(display);
		display->display();
	}
}

void prepareEnvironment() {
	createSystem(100.0f, 100.0f, RL_REGION_X, RL_REGION_Y, colors::Red);
	createSystem(100.0f, 100.0f, GAN_REGION_X, GAN_REGION_Y, colors::Green);
	createSystem(100.0f, 100.0f, CNN_REGION_X, CNN_REGION_Y, colors::Blue);
	createSystem(100.0f, 100.0f, RNN_REGION_X, RNN_REGION_Y, colors::Magenta);
	createSystem(100.0f, 100.0f, SNN_REGION_X, SNN_REGION_Y, colors::Yellow);
}

	// Entry Point //
void initGUI() {
	sf::RenderWindow display(sf::VideoMode(window_w, window_h), "CARL!");
	sf::View view(sf::FloatRect(0.0f, 0.0f, (float)window_w, (float)window_h));
	display.setView(view);

	prepareEnvironment();

	runRenderLoop(&display);
}