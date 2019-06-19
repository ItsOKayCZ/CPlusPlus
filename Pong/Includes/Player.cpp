#include "../Headers/Player.hpp"


Player::Player(int windowWidth, int windowHeight){

  Player::windowWidth = windowWidth;
  Player::windowHeight = windowHeight;

  // Setting size
  width = 20;
  height = windowHeight / 4;
  shape.setSize(sf::Vector2f(width, height));

  // Setting position
  pos.x = 25;
  pos.y = (windowHeight / 2) - (height / 2);
  shape.setPosition(pos);

  // Color
  color = sf::Color::White;
  shape.setFillColor(color);

  // Setting player speed
  speed = 0.5;
}
Player::~Player(){}

sf::RectangleShape Player::getShape(){
  return shape;
}

sf::Vector2f Player::getSize(){
  return shape.getSize();
}

void Player::setPosition(sf::Vector2f position){
  shape.setPosition(position);
}

void Player::changeMove(sf::Keyboard::Key direction, bool isMoving){
  if(sf::Keyboard::Up == direction){
    move.up = isMoving;  
  } else if(sf::Keyboard::Down == direction){
    move.down = isMoving;
  }
}

void Player::update(){

  if(move.up == true){
    pos.y -= speed;
  }

  if(move.down == true){
    pos.y += speed;
  }

  if(pos.y < 0){
    pos.y = 0;
  }

  if(pos.y + height > windowHeight){
    pos.y = windowHeight - height;
  }

  shape.setPosition(pos);
}