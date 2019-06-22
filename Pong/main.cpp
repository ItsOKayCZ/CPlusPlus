// Window manager
#include "Headers/Window.hpp"

// Player manager
#include "Headers/Player.hpp"

// AI player manager
#include "Headers/PlayerAI.hpp"

// Ball manager
#include "Headers/Ball.hpp"

// Score manager
#include "Headers/Score.hpp"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 700;

int main(){

  // Making the window manager
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
  
  // Making the player and AI manager
  Player player(WINDOW_WIDTH, WINDOW_HEIGHT);
  PlayerAI playerAI(WINDOW_WIDTH, WINDOW_HEIGHT);

  Score scoreMan(WINDOW_WIDTH, WINDOW_HEIGHT);

  Ball ball(WINDOW_WIDTH, WINDOW_HEIGHT, &scoreMan);

  // Runnning the game
  window.run(&player, &playerAI, &ball, &scoreMan);

  return 0;
}
