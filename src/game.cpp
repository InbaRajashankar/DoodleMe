#include <iostream>
#include <thread>
#include <chrono> // time

#include <fstream>
#include <vector>

#include <sstream>

#include <random>

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
 * @brief Chooss a random string from a vector.
 */
std::string Game::choose_rand(std::vector<std::string>& vec)
{
  std::random_device random_device;
  std::mt19937 gen(random_device());
  std::uniform_int_distribution<> dist(0, vec.size() - 1);
  return vec[dist(gen)];
}

/**
 * @brief Forms a procedurally generated drawing prompt.
 */
std::string Game::make_prompt()
{

  std::string skeleton = Game::choose_rand(skeletons);

  std::string specials[] = {"[A]", "[N]", "[NP]"};
  std::vector<std::string> vecs[] = {adjectives, nounsSng, nounsPlu};

  for (int i = 0; i < 3; i++)
  {
    size_t startPos = 0;
    while ((startPos = skeleton.find(specials[i])) != std::string::npos)
    {
      std::string replacement = Game::choose_rand(vecs[i]);
      skeleton.replace(startPos, specials[i].size(), replacement);
      startPos += replacement.length();
    }
  }

  // size_t startPos = 0;
  // while ((startPos = skeleton.find("[A]")) != std::string::npos)
  // {
  //   std::string replacement = Game::choose_rand(adjectives);
  //   skeleton.replace(startPos, 3, replacement);
  //   startPos += replacement.length();
  // }

  // startPos = 0;
  // while ((startPos = skeleton.find("[N]")) != std::string::npos)
  // {
  //   std::string replacement = Game::choose_rand(nounsSng);
  //   skeleton.replace(startPos, 3, replacement);
  //   startPos += replacement.length();
  // }

  // startPos = 0;
  // while ((startPos = skeleton.find("[NP]")) != std::string::npos)
  // {
  //   std::string replacement = Game::choose_rand(nounsPlu);
  //   skeleton.replace(startPos, 4, replacement);
  //   startPos += replacement.length();
  // }

  return skeleton;
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

/**
 * @brief calls private methods to process files.
 */
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
    std::string prompt = Game::make_prompt();
    std::cout << "\nPROMPT: " << prompt << "\nPress enter to start the timer.";
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
