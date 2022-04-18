#include<iostream>
#include <stdlib.h>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

using namespace sf;

class Player
{
private:
	bool left;
	float speed = 10.f;
public:
	RectangleShape sprite;
	int points = 0;

	Player(RenderWindow &window, bool _left)
	{
		sprite.setSize(Vector2f(10.f, 50.f));
		sprite.setFillColor(Color::White);
		if (_left)
		{
			sprite.setPosition(Vector2f(sprite.getGlobalBounds().width,
				window.getSize().y / 2 - sprite.getGlobalBounds().height / 2));
		}
		else
		{
			sprite.setPosition(Vector2f(window.getSize().x - sprite.getGlobalBounds().width*2,
				window.getSize().y / 2 - sprite.getGlobalBounds().height/2));
		}
		left = _left;
	}
	void Inputs(RenderWindow &window)
	{
		if (left)
		{
			if (Keyboard::isKeyPressed(Keyboard::W) &&
				sprite.getPosition().y > 0)
			{
				sprite.move(Vector2f(0.f, -speed));
			}
			else if (Keyboard::isKeyPressed(Keyboard::S) &&
				sprite.getPosition().y < window.getSize().y - sprite.getGlobalBounds().height)
			{
				sprite.move(Vector2f(0.f, speed));
			}
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) &&
				sprite.getPosition().y > 0)
			{
				sprite.move(Vector2f(0.f, -speed));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down) &&
				sprite.getPosition().y < window.getSize().y - sprite.getGlobalBounds().height)
			{
				sprite.move(Vector2f(0.f, speed));
			}
		}
	}
};
class Ball
{
private:
	int left;
	float startSpeed = 1.0f; float speed; float maxSpeed = 8.0f;
	Vector2f velocity = Vector2f(.0f, .0f);
public:
	RectangleShape sprite;
	Clock timer;

	Ball(RenderWindow &window, bool _left) {
		sprite.setSize(Vector2f(10.f, 10.f));
		sprite.setFillColor(Color::White);
		RespawnBall(window);
		left = _left ? -1 : 1;
		velocity = Vector2f(left * speed, speed);
	}
	void Physics(RenderWindow &window, Player p1, Player p2)
	{
		if (speed < maxSpeed)
		{
			speed += timer.getElapsedTime().asSeconds() / 2;
			velocity = Vector2f(left * speed, speed);
		}
		if ( p1.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) ||
			p2.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		{
			velocity.x *= -1;
		}
		else if (sprite.getPosition().y < 0 ||
			sprite.getPosition().y > window.getSize().y - sprite.getGlobalBounds().height)
		{
			velocity.y *= -1;
		}
		else if (sprite.getPosition().x < 0 ||
			sprite.getPosition().x > window.getSize().x - sprite.getGlobalBounds().width)
		{
			RespawnBall(window);
		}
		sprite.move(velocity);
	}
	void RespawnBall(RenderWindow &window)
	{
		sprite.setPosition(Vector2f(window.getSize().x / 2 - sprite.getGlobalBounds().width / 2,
			window.getSize().y / 2 - sprite.getGlobalBounds().height / 2));
		speed = startSpeed;
		timer.restart();
	}

};
//class ScoreUI
//{
//private:
//	Font font;
//	FloatRect rect;
//public:
//	Text text;
//	ScoreUI()
//	{
//		font.loadFromFile("OpenSans-Regular.ttf");
//		text.setFont(font);
//		text.setString("0");
//		text.setCharacterSize(50);
//		text.setPosition(Vector2f(1.f, 1.f));
//	}
//	void UpdateText(String _text)
//	{
//		text.setString(_text);
//	}
//};

int main()
{
	RenderWindow window(sf::VideoMode(640, 400), "PongForTwo");
	window.setFramerateLimit(60);


	Player player1(window, true);
	Player player2(window, false);
	Ball ball(window, false);

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

		player1.Inputs(window);
		player2.Inputs(window);
		ball.Physics(window, player1, player2);
		if (ball.sprite.getPosition().x < 0)
		{
			system("CLS");
			player2.points++;
			std::cout << "Player1: " << player1.points << " Player2: " << player2.points << std::endl;
		}
		else if (ball.sprite.getPosition().x > window.getSize().x - ball.sprite.getGlobalBounds().width)
		{
			system("CLS");
			player1.points++;
			std::cout << "Player1: " << player1.points << " Player2: " << player2.points << std::endl;
		}

		window.clear(Color::Black);

		window.draw(player1.sprite);
		window.draw(player2.sprite);
		window.draw(ball.sprite);

		window.display();
	}
}