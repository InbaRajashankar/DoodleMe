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

  return skeleton;
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
 * @brief Main gameflow logic for mode 2. 
 */
void Game::start_mode2()
{
  int wait;
  bool play_more = true;
  std::string buffer;

  std::cout << "Please enter your preferred wait time: ";
  std::cin >> wait;
  while (wait == 0)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid time entered! Please try again: ";
    std::cin >> wait;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
  std::cout << "Wait time: " << wait << " seconds.\n";

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

void Game::start_mode1()
{
  int num_prompts;
  std::cout << "Enter the number of prompts to generate: ";
  std::cin >> num_prompts;
  while (num_prompts == 0)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid number entered! Please try again: ";
    std::cin >> num_prompts;
  }

  std::cout << "\nGenerating " << num_prompts << " prompts...\n";

  for (int i = 1; i <= num_prompts; i++)
  {
    std::cout << "- " << i << ") " << Game::make_prompt() << '\n';
  }

}

/**
 * @brief Constructor for a game object. 
 */
Game::Game()
{
  int game_mode;

  Game::process_files();
  std::cout << "Hello, the game will start now\nEnter a game mode:\n";
  std::cout << " - 1: Generate a set-number of random doodle prompts.\n";
  std::cout << " - 2: Generate a random prompt ever X seconds.\n> ";

  std::cin >> game_mode;
  while (game_mode == 0)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid game mode entered! Please try again: ";
    std::cin >> game_mode;
  }
  std::cout << "Game mode " << game_mode << " chosen.\n";

  if (game_mode == 1)
    Game::start_mode1();
  else if (game_mode == 2)
    Game::start_mode2();
}