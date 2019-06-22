#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Score{

public:
  Score(int _windowWidth, int _windowHeight);
  ~Score();

  void update();

  sf::Text *getText();

  void updateScore(int playerID);

private:
  int windowWidth;
  int windowHeight;

  sf::Font font;
  int textSize;
  sf::Color color;

  sf::Text playerText[2];

  int playerScore[2];

};

#endif