#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <SFML/Graphics.hpp>

class PlayerAI{

public:
  PlayerAI(int windowWidth, int windowHeight);
  ~PlayerAI();

  sf::RectangleShape getShape();

  sf::Vector2f getPosition();
  sf::Vector2f getSize();

  void update(sf::Vector2f ballPos, sf::Vector2f ballSize);

private:

  int windowWidth;
  int windowHeight;

  sf::Vector2f size;
  sf::Vector2f pos;

  float width;
  float height;

  float speed;

  sf::RectangleShape shape;
  sf::Color color;

};

#endif