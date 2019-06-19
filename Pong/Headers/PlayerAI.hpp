#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include "../Headers/Player.hpp"

#include <SFML/Graphics.hpp>

class PlayerAI{

public:
  PlayerAI(int windowWidth, int windowHeight);
  ~PlayerAI();

  sf::RectangleShape getShape();

private:
  Player base;

};

#endif