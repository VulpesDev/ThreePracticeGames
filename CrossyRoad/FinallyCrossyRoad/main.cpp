#include<iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

using namespace sf;

class Car {
public:
	RectangleShape shape;
	float speed = rand() % 8 + 4;
	int direction = 0;
	Car() {
		shape.setSize(Vector2f(30.f, 10.f));
		shape.setFillColor(Color::White);
		int r = rand() % 641;
		std::cout << r << std::endl;
		shape.setPosition(Vector2f(r, 0.f));
		direction = rand() % 2 == 0 ? -1 : 1;
	}
	void Move(RenderWindow &window) {
		shape.move(Vector2f(speed * direction, 0.f));
		if (shape.getPosition().x + shape.getGlobalBounds().width < 0)
		{
			shape.setPosition(Vector2f(window.getSize().x, shape.getPosition().y));
		}
		else if (shape.getPosition().x - shape.getGlobalBounds().width
		> window.getSize().x - shape.getGlobalBounds().width)
		{
			shape.setPosition(Vector2f(-shape.getGlobalBounds().width, shape.getPosition().y));
		}
	}
};
class Player {
public:
	RectangleShape sprite;
	int speed = 3;
	Player(RenderWindow &window) {
		sprite.setFillColor(Color::White);
		sprite.setSize(Vector2f(10.f, 10.f));
		sprite.setPosition(window.getSize().x / 2, window.getSize().y - sprite.getSize().y * 2);
	}
	void Input()
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			sprite.move(Vector2f(0.f, -speed));
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			sprite.move(Vector2f(0.f, speed));
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			sprite.move(Vector2f(-speed, 0.f));
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			sprite.move(Vector2f(speed, 0.f));
		}
	}
	void GameRules(RenderWindow &window)
	{
		if (sprite.getPosition().x < 0)
		{
			sprite.setPosition(Vector2f(0.f, sprite.getPosition().y));
		}
		if (sprite.getPosition().x > window.getSize().x - sprite.getGlobalBounds().width)
		{
			sprite.setPosition(Vector2f(window.getSize().x - sprite.getGlobalBounds().width,
				sprite.getPosition().y));
		}
		if (sprite.getPosition().y > window.getSize().y - sprite.getGlobalBounds().height)
		{
			sprite.setPosition(Vector2f(sprite.getPosition().x,
				window.getSize().y - sprite.getGlobalBounds().height));
		}
	}
};

bool won = false;
int main()
{
	srand(time(0));
	RenderWindow window(sf::VideoMode(640, 400), "Crossy Tsetso");
	window.setFramerateLimit(60);

	const int _carL = 40;
	Car _car [_carL];

	Player _player(window);

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
		//Update Game Logic
		won = _player.sprite.getPosition().y < 0;
		_player.GameRules(window);

		if (won)
		{
			window.close();
		}
		//Collisions
		for (int i = 1; i <= _carL; i++)
		{
			if (_car[i - 1].shape.getGlobalBounds().intersects(_player.sprite.getGlobalBounds()))
			{
				_player.sprite.setPosition
				(window.getSize().x / 2, window.getSize().y - _player.sprite.getSize().y * 2);
			}
		}
		//Update Input
		_player.Input();

		//Update Car
		for (int i = 1; i <= _carL; i++)
		{
			_car[i - 1].Move(window);
		}

		//Draw
		window.clear(Color::Black);
		window.draw(_player.sprite);
		
		for (int i = 1; i <= _carL; i++)
		{
				_car[i - 1].shape.setPosition(Vector2f(_car[i - 1].shape.getPosition().x,
					((window.getSize().y / _carL) + _player.sprite.getGlobalBounds().height)*i));
				window.draw(_car[i - 1].shape);
		}

		window.display();
	}
	return 0;
}