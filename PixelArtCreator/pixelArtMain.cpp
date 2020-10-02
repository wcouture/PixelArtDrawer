#include "essentials.h"

int findPixel(RectangleShape mouseSquare);

vector<RectangleShape> pixelGrid;
Color activeColor;


int main()
{
	cout << "Enter the grid size ->		";

	int gridSize = 50;

	cin >> gridSize;



	// Create a Window to Display Graphics, Define Size and Window Name
	sf::RenderWindow window(sf::VideoMode(1000, 1100), "SFML Window");

	bool drawing = false;

	activeColor = Color::White;

	float width = gridSize;
	float height = gridSize;

	float pixelSize = window.getSize().x / width;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			RectangleShape temp;
			
			temp.setSize(Vector2f(pixelSize, pixelSize));
			temp.setPosition(Vector2f(j * pixelSize, i * pixelSize));
			temp.setFillColor(activeColor);
			
			pixelGrid.push_back(temp);
		}
	}

	
	Font font;
	font.loadFromFile("mainFont.ttf");

	Text label;
	label.setFont(font);
	label.setString("Colors:");
	label.setCharacterSize(30);
	label.setFillColor(Color::White);


	Vector2f textPos;
	textPos.y = pixelGrid[pixelGrid.size() - 1].getPosition().y + pixelSize + 10;
	textPos.x = 10;

	label.setPosition(textPos);


	vector<RectangleShape> colorSelections;
	vector<Color> colors = {Color::Black, Color::Blue, Color::Cyan, Color::Green, Color::Magenta, Color::Yellow, Color::Red, Color::White};

	Vector2f colorPalleteSize;
	colorPalleteSize.x = 60;
	colorPalleteSize.y = 60;
	float padding = 26.25;

	for (int i = 0; i < 8; i++) {
		RectangleShape temp;
		temp.setFillColor(colors[i]);
		temp.setSize(colorPalleteSize);
		Vector2f position;
		position.x = 100 + (112.5 * i) + padding;
		position.y = (label.getPosition().y + 10);
		temp.setPosition(position);

		colorSelections.push_back(temp);

	}


	activeColor = Color::Red;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// When X Button Clicked, Close Window
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonPressed)
				drawing = true;
			else if (event.type == Event::MouseButtonReleased)
				drawing = false;
			else if (event.type == Event::KeyPressed) {
				if (event.KeyPressed == Keyboard::F) {
					cout << "------Custom Color Initiated------" << endl;
					Vector3f rgbValues;
					cout << "Custom Color Red Value:	";
					cin >> rgbValues.x;
					cout << "Custom Color Green Value:	";
					cin >> rgbValues.y;
					cout << "Custom Color Blue Value:	";
					cin >> rgbValues.z;
					activeColor = Color::Color(rgbValues.x, rgbValues.y, rgbValues.z);
				}
			}
			if (drawing) {
				RectangleShape temp;
				temp.setSize(Vector2f(.1, .1));

				Vector2f mousePos;
				mousePos.x = Mouse::getPosition(window).x;
				mousePos.y = Mouse::getPosition(window).y;

				temp.setPosition(mousePos);

				int pixelIndex = findPixel(temp);
				if (pixelIndex != -1) {
					pixelGrid[pixelIndex].setFillColor(activeColor);
				}
				else {
					for (RectangleShape color : colorSelections) {
						if (temp.getGlobalBounds().intersects(color.getGlobalBounds())) {
							activeColor = color.getFillColor();
							break;
						}
					}
				}

			}
		}

		/* DEFINE ACTIONS (i.e. MOVEMENT) HERE */

		window.clear(Color::Color(138,138,138));
		for (RectangleShape square : pixelGrid) {
			window.draw(square);
		}
		for (RectangleShape color : colorSelections) {
			window.draw(color);
		}
		window.draw(label);
		window.display();
	}
}

int findPixel(RectangleShape mouseSquare) {
	for (int i = 0; i < pixelGrid.size(); i++) {
		if (pixelGrid[i].getGlobalBounds().intersects(mouseSquare.getGlobalBounds())) {
			return i;
		}
	}

	return -1;
}