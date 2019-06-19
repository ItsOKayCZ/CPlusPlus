#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "../Headers/Player.hpp"
#include "../Headers/PlayerAI.hpp"
#include "../Headers/Ball.hpp"

class Window{

public:
  Window(int _width, int height, std::string _title);
  ~Window();

  void run(Player *player, PlayerAI *playerAi, Ball *ball);

  int getWidth();
  int getHeight();

private:
  int width;
  int height;

  std::string title;

  sf::RenderWindow window;
};

#endif
