#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265358979323846

#include "../Headers/Player.hpp"
#include "../Headers/PlayerAI.hpp"
#include "../Headers/Score.hpp"

class Ball{

public:
  Ball(int windowWidth, int windowHeight, Score *_scoreMan);
  ~Ball();

  sf::RectangleShape getShape();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();

  void update(Player *player, PlayerAI *playerAI);

private:
  void checkPlayerPosition(Player *player, PlayerAI *playerAI);
  void resetProperties(int startingAngle);

  float width;
  float height;

  int windowWidth, windowHeight;

  sf::RectangleShape shape;

  sf::Vector2f vel;
  float speed;
  float startingSpeed;
  float angle;
  sf::Vector2f pos;
  sf::Vector2f startPos;
  float accel; // Acceleration

  struct Direction{
    bool left = true;
    bool right = false;
    bool up = false;
    bool down = false;
  } dir;

  sf::Color color;

  // Score manager
  Score *scoreMan;
};

#endif