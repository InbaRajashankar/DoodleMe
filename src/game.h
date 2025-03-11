#ifndef GAME_H  // Include guard to prevent multiple inclusions
#define GAME_H
#endif

#include <vector>

class Game
{
private:
  std::vector<std::string> skeletons;
  std::vector<std::string> adjectives;
  std::vector<std::string> nounsSng;
  std::vector<std::string> nounsPlu;

  void file_to_vector(const std::string& path, std::vector<std::string>& vec);
  void file_to_two_vector(const std::string& path, std::vector<std::string>& vec1, std::vector<std::string>& vec2);

  std::string choose_rand(std::vector<std::string>& vec);
  std::string make_prompt();

  void process_files();
  void start_mode2();
  void start_mode1();

public:
  Game();
};