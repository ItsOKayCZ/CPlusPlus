#include "../Headers/Score.hpp"

Score::Score(int _windowWidth, int _windowHeight){

  this->windowWidth = _windowWidth;
  this->windowHeight = _windowHeight;

  // Loading font
  if(!font.loadFromFile("Fonts/font.ttf")){
    printf("[!!] Cannot load font from Fonts/font.ttf\n");
  }

  // Setting font
  playerText[0].setFont(font);
  playerText[1].setFont(font);

  // Setting score to 0
  playerScore[0] = 0;
  playerScore[1] = 0;

  // Setting the string
  playerText[0].setString(std::to_string(playerScore[0]));
  playerText[1].setString(std::to_string(playerScore[1]));

  // Setting size
  textSize = 35;
  playerText[0].setCharacterSize(textSize);
  playerText[1].setCharacterSize(textSize);

  // Setting color
  color = sf::Color::White;
  playerText[0].setFillColor(color);
  playerText[1].setFillColor(color);

  // Setting position
  sf::Vector2f pos;
  pos.x = (windowWidth / 3);
  pos.y = (windowHeight / 6);
  playerText[0].setPosition(pos);
  pos.x = windowWidth - (windowWidth / 3);
  playerText[1].setPosition(pos);
}
Score::~Score(){}

void Score::update(){

}

sf::Text *Score::getText(){
  return playerText;
}

void Score::updateScore(int playerID){
  playerScore[playerID]++;
  playerText[playerID].setString(std::to_string(playerScore[playerID]));
}