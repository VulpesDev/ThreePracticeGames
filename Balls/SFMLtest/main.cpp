#include<iostream>
#include <string> 
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(640, 400), "Minecraft");
	window.setFramerateLimit(60);

	CircleShape hoop;
	int dir = 0;
	hoop.setRadius(35.f);
	hoop.setFillColor(Color::Red);
	hoop.setOutlineThickness(2);
	hoop.setOutlineColor(Color::Yellow);

	float hoopSpeed = 5.f;

	CircleShape ball;
	bool isShot = false;
	ball.setRadius(20.f);
	ball.setFillColor(Color::Red);
	ball.setPosition(Vector2f(0, window.getSize().y - ball.getRadius() * 3));

	Font scoreFont;
	scoreFont.loadFromFile("OpenSans-Regular.ttf");
	Text scoreText;
	scoreText.setFont(scoreFont);
	scoreText.setString("0");
	scoreText.setCharacterSize(150);
	FloatRect textRect = scoreText.getLocalBounds();
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	scoreText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	int score = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Update hoop
		if (hoop.getPosition().x <= 0)
			dir = 1;
		else if (hoop.getPosition().x + hoop.getRadius()*2 >= window.getSize().x)
		{
			dir = 0;
		}
		if (dir == 0)
		{
			hoop.move(-hoopSpeed, 0.f);
		}
		else
		{
			hoop.move(hoopSpeed, 0.f);
		}
		//GameDifficulty
		hoopSpeed = (1 + (score*0.1f)) * 5.f;
		//Collision ball
		if (ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
		{
			score++;
			isShot = false;
			ball.setPosition(Vector2f(0, window.getSize().y - ball.getRadius() * 3));
		}
		if(ball.getPosition().y < 0)
		{
			score = 0;
			isShot = false;
			ball.setPosition(Vector2f(0, window.getSize().y - ball.getRadius() * 3));
		}
		scoreText.setString(std::to_string(score));
		//Update ball
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			isShot = true;
		}
		if(!isShot)
		ball.setPosition(Mouse::getPosition(window).x, ball.getPosition().y);
		else
		{
			ball.move(0, -15.f);
		}

		//Draw
		window.clear(Color::Black);

		window.draw(hoop);
		window.draw(ball);
		window.draw(scoreText);

		window.display();

	}

	return 0;
}