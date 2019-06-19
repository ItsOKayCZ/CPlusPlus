#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

class Ball{

public:
  Ball(int windowWidth, int windowHeight);
  ~Ball();

  sf::RectangleShape getShape();

  void update();

private:
  float width;
  float height;

  sf::RectangleShape shape;

  sf::Vector2f direction;

  sf::Color color;

};

#endif