#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Player{

public:

  Player(int _windowWidth, int _windowHeight);
  ~Player();

  sf::RectangleShape getShape();

  void setPosition(sf::Vector2f position);
  sf::Vector2f getPosition();
  sf::Vector2f getSize();

  void changeMove(sf::Keyboard::Key direction, bool isMoving);
  void update();

private:

  int windowWidth;
  int windowHeight;

  float width;
  float height;

  float speed;

  struct Moves{
    bool up = false;
    bool down = false;
  } move;

  sf::Vector2f pos;

  sf::RectangleShape shape;
  sf::Color color;

};

#endif