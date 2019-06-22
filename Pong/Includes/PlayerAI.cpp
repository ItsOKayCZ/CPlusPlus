#include "../Headers/PlayerAI.hpp"

PlayerAI::PlayerAI(int _windowWidth, int _windowHeight){
  
  // Setting the window
  windowWidth = _windowWidth;
  windowHeight = _windowHeight;

  // Setting the speed
  speed = 0.5;
  
  // Set size
  width = 20;
  height = windowHeight / 4;
  shape.setSize(sf::Vector2f(width, height));

  // Setting the position
  pos.x = windowWidth - width - 25;
  pos.y = (windowHeight / 2) - (height / 2);
  shape.setPosition(pos);

  // Setting the color
  color = sf::Color::White;
  shape.setFillColor(color);


}

PlayerAI::~PlayerAI(){}

void PlayerAI::update(sf::Vector2f ballPos, sf::Vector2f ballSize){

  if(pos.y < 0){
    pos.y = 0;
  }
  if(pos.y + height > windowHeight){
    pos.y = windowHeight - height;
  }

  // Middle points of both objects
  float playerPos = pos.y + (height / 2);
  float middleBallPos = ballPos.y + (ballSize.y / 2);
  if(playerPos < middleBallPos){
    pos.y += speed;
  } else if(playerPos > middleBallPos){
    pos.y -= speed;
  }

  shape.setPosition(pos);
}

sf::RectangleShape PlayerAI::getShape(){
  return shape;
}
sf::Vector2f PlayerAI::getPosition(){
  return shape.getPosition();
}
sf::Vector2f PlayerAI::getSize(){
  return shape.getSize();
}

