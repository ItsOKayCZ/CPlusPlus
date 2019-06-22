#include "../Headers/Ball.hpp"

float angleToRadians(float angle){
  return (PI/180) * angle;
}

Ball::Ball(int _windowWidth, int _windowHeight, Score *_scoreMan){

  // Score manager
  scoreMan = _scoreMan;

  // Window size
  windowWidth = _windowWidth;
  windowHeight = _windowHeight;

  // Ball size
  width = height = windowWidth / 20;
  shape.setSize(sf::Vector2f(width, height));

  // Setting position
  pos.x = (windowWidth / 2) - (width / 2);
  pos.y = (windowHeight / 2) - (height / 2);
  startPos = pos;
  shape.setPosition(pos);

  // Setting color
  color = sf::Color::White;
  shape.setFillColor(color);

  // Setting angle and speed
  speed = 0.1;
  angle = -45;
  accel = 1.1;
}
Ball::~Ball(){}

sf::RectangleShape Ball::getShape(){
  return shape;
}
sf::Vector2f Ball::getPosition(){
  return shape.getPosition();
}
sf::Vector2f Ball::getSize(){
  return shape.getSize();
}

void Ball::update(Player *player, PlayerAI *playerAI){

  vel.x = sin(angleToRadians(angle)) * speed;
  vel.y = cos(angleToRadians(angle)) * speed;

  pos.x += vel.x;
  pos.y += vel.y;

  checkPlayerPosition(player, playerAI);

  // Touched the top
  if(pos.y < 0){
    pos.y = 0;

    dir.up = false;
    dir.down = true;

    if(dir.right == true){
      angle -= 90;
    } else {
      angle += 90;
    }
  }
  // Touched the bottom
  if(pos.y + height > windowHeight){
    pos.y = windowHeight - height;

    dir.down = false;
    dir.up = true;

    if(dir.right == true){
      angle += 90;
    } else {
      angle -= 90;
    }
  }

  // Touched the left side
  if(pos.x < 0){
    pos = startPos;
    angle = -90;

    scoreMan->updateScore(1);
  }
  // Touched the right side
  if(pos.x + width > windowWidth){
    pos = startPos;
    angle = 90;

    scoreMan->updateScore(0);
  }

  if(angle >= 360){
    angle = (int)angle % 360;
  }

  shape.setPosition(pos);
}

void Ball::checkPlayerPosition(Player *player, PlayerAI *playerAI){
  
  // Ball going left
  if(dir.left == true){

    sf::Vector2f playerPos = player->getPosition();
    sf::Vector2f playerSize = player->getSize();
    float tolerance = playerSize.x - (playerSize.x / 10);

    // Checking for X
    if((playerPos.x + tolerance > pos.x) && (pos.x < playerPos.x + playerSize.x)){

      // Checking for Y
      // Checking top half of paddle
      if((playerPos.y <= pos.y + height) && (pos.y <= playerPos.y + (playerSize.y / 2))){
        
        // Hit confirmed

        dir.left = false;
        dir.right = true;

        // Change direction to right
        angle = 90;        

        dir.up = true;
        dir.down = false;

        // Changing the direction to go up-right
        angle += 45;

        // Changing the speed
        speed *= accel;

      } else 
      // Checking bottom half of paddle
      if((playerPos.y + (playerSize.y / 2) < pos.y + height) && (pos.y < playerPos.y + playerSize.y)){
        
        // Hit confirmed

        dir.left = false;
        dir.right = true;

        // Change direction to right
        angle = 90;        

        dir.up = false;
        dir.down = true;

        // Changing the direction to go up-right
        angle -= 45;

        // Changing the speed
        speed *= accel;

      }

    }


  } else if(dir.right == true){ // Ball going right
    
    sf::Vector2f playerAiPos = playerAI->getPosition();
    sf::Vector2f playerAiSize = playerAI->getSize();
    float tolerance = (playerAiSize.x / 10);

    // Checking for X
    if((pos.x + width > playerAiPos.x) && (pos.x + width < playerAiPos.x + tolerance)){

      // Checking for Y
      // Checking top half of paddle
      if((playerAiPos.y <= pos.y + height) && (pos.y <= playerAiPos.y + (playerAiSize.y / 2))){
        
        // Hit confirmed

        dir.right = false;
        dir.left = true;

        // Change direction to right
        angle = -90;

        dir.up = true;
        dir.down = false;

        // Changing the direction to go up-right
        angle -= 45;

        // Changing the speed
        speed *= accel;

      } else 
      // Checking bottom half of paddle
      if((playerAiPos.y + (playerAiSize.y / 2) < pos.y + height) && (pos.y < playerAiPos.y + playerAiSize.y)){
        
        // Hit confirmed

        dir.right = false;
        dir.left = true;

        // Change direction to right
        angle = -90;

        dir.up = false;
        dir.down = true;

        // Changing the direction to go up-right
        angle += 45;

        // Changing the speed
        speed *= accel;

      }

    }

  }

}