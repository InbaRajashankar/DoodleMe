#include <iostream>
#include <thread>
#include <chrono>

#include "game.h"

/*
 * @brief Constructor for a game object. 
 */
Game::Game()
{
  std::cout << "Hello, the game will start now!\n";
  Game::start();
}

/*
 * @brief Main gameflow logic. 
 */
void Game::start()
{
  int wait;
  bool play_more = true;
  std::string buffer;

  std::cout << "Please enter your preferred wait time: ";
  std::cin >> wait;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
  std::cout << "wait: " << wait << "\n";

  while (play_more)
  {
    std::cout << "\nDRAWING PROMPT\n";
    std::this_thread::sleep_for(std::chrono::seconds(wait));
    std::cout << "Time up!\nEnter q to stop the game, or anything else to continue:";
    std::getline(std::cin, buffer);
    if (buffer == "q")
      play_more = false;
  }

  std::cout << "Thank you for playing\n";
  return;
}
