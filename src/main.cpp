#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


using namespace std;

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "--help") == 0) {
    cout << "Usage: \n./SnakeGame <gamertag> \n <gamertag>: the name under which "
            "you want your score to be stored."
         << endl;
    return 0;
  }
  string name;
  if (argc > 1)
    name = argv[1];
  else {
    name = "Default";
    cout << "No Name given. Choosing Default." << endl;
  }
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  for (auto &c : name)
    c = toupper(c);
  game.gamertag = name;
  game.Run(controller, renderer, kMsPerFrame);
  game.SetScore();
  return 0;
}