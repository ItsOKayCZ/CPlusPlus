#include "../Headers/Ball.hpp"

Ball::Ball(int windowWidth, int windowHeight){
  
  // Ball size
  width = height = windowWidth / 20;
  shape.setSize(sf::Vector2f(width, height));

  // Setting position
  sf::Vector2f position;
  position.x = (windowWidth / 2) - (width / 2);
  position.y = (windowHeight / 2) - (height / 2);
  shape.setPosition(position);

  // Setting color
  color = sf::Color::White;
  shape.setFillColor(color);

}
Ball::~Ball(){}

sf::RectangleShape Ball::getShape(){
  return shape;
}

void Ball::update(){



}