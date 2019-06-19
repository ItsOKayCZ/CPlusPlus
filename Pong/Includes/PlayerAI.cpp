#include "../Headers/PlayerAI.hpp"

PlayerAI::PlayerAI(int windowWidth, int windowHeight)
: base(windowWidth, windowHeight)
{
  
  sf::Vector2f size = base.getSize();

  sf::Vector2f position;
  position.x = windowWidth - size.x - 25;
  position.y = (windowHeight / 2) - (size.y / 2);
  base.setPosition(position);

}

PlayerAI::~PlayerAI(){}

sf::RectangleShape PlayerAI::getShape(){
  return base.getShape();
}