#include <iostream>
#include <thread>
#include <chrono> // time

#include <fstream>
#include <vector>

#include <sstream>

#include "game.h"

std::vector<std::string> skeletons, adjectives, nounsSng, nounsPlu;

/**
 * @brief Reads each line of a file as a string, which are pushed into a vector.
 */
void Game::file_to_vector(const std::string& path, std::vector<std::string>& vec)
{
  std::string buffer;
  std::ifstream curFile (path);

  if (!curFile.is_open())
  {
    std::cout << "Unable to open " << path << "!\n";
    exit(0);
  }

  while (std::getline (curFile, buffer))
    vec.push_back(buffer);

  curFile.close();
}

/**
 * @brief Reads each line of file as a comma-separated string, which are pushed into two vectors.
 */
void Game::file_to_two_vector(const std::string& path, std::vector<std::string>& vec1, std::vector<std::string>& vec2)
{
  std::string buffer;
  std::string word1;
  std::string word2;

  std::ifstream curFile (path);

  if (!curFile.is_open())
  {
    std::cout << "Unable to open " << path << "!\n";
    exit(0);
  }

  while (std::getline (curFile, buffer))
  {
    std::stringstream ss(buffer);
    while (ss.good())
    {
      std::getline(ss, word1, ',');
      std::getline(ss, word2);
      vec1.push_back(word1);
      vec2.push_back(word2);
    }
  }
  
  curFile.close();
}

/**
 * @brief Constructor for a game object. 
 */
Game::Game()
{
  Game::process_files();
  std::cout << "Hello, the game will start now\n";
  Game::start();
}

void Game::process_files()
{
  Game::file_to_vector("src/text_files/adjectives.txt", adjectives);
  Game::file_to_two_vector("src/text_files/nouns.txt", nounsSng, nounsPlu);
  Game::file_to_vector("src/text_files/skeletons.txt", skeletons);
}

/**
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
    std::cout << "\nDRAWING PROMPT\nPress enter to start the timer.";
    std::getline(std::cin, buffer);
    std::cout << "Timer started!\n";
    std::this_thread::sleep_for(std::chrono::seconds(wait));
    std::cout << "Time up!\nEnter q to stop the game, or anything else to continue:";
    std::getline(std::cin, buffer);
    if (buffer == "q")
      play_more = false;
  }

  std::cout << "Thank you for playing\n";
  return;
}
