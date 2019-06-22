#include "../Headers/Window.hpp"

Window::Window(int _width, int _height, std::string _title)
: window(sf::VideoMode(_width, _height), _title)
{
  width = _width;
  height = _height;

  title = _title;
}
Window::~Window(){}

void Window::run(Player *player, PlayerAI *playerAI, Ball *ball, Score *scoreMan){

  while(window.isOpen()){

    sf::Event event;
    while(window.pollEvent(event)){

      switch(event.type){

        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          if((event.key.code == sf::Keyboard::Up) ||
             (event.key.code == sf::Keyboard::Down)){

            player->changeMove(event.key.code, true);
          }
          break;

        case sf::Event::KeyReleased:
          if((event.key.code == sf::Keyboard::Up) ||
             (event.key.code == sf::Keyboard::Down)){
            
            player->changeMove(event.key.code, false);
          }
          break;

      }


    }

    player->update();
    ball->update(player, playerAI);
    playerAI->update(ball->getPosition(), ball->getSize());

    window.clear();
    window.draw(player->getShape());
    window.draw(playerAI->getShape());
    window.draw(ball->getShape());
    window.draw(scoreMan->getText()[0]);
    window.draw(scoreMan->getText()[1]);
    window.display();

  }

}

int Window::getWidth(){
  return width;
}
int Window::getHeight(){
  return height;
}