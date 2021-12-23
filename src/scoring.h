#ifndef SCORING_H
#define SCORING_H

#include <iostream>
#include <map>

using namespace std;

class Scoring {
private:
  int player_score;
  string name;
  string const score_sheet_file_path = "score_sheet.txt";

public:
  Scoring();
  int GetScore();
  void SetScore(int s);

  string GetName();
  void SetName(string n);

  void WriteScore();
  std::map<string, int> ReadScore();
};

#endif //SCORING_H