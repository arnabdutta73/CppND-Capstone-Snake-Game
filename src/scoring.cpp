#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "scoring.h"

using namespace std;

Scoring::Scoring() {

  // Creating a default gamer
  name = "Default";
  player_score = 0;
}

// Getter and Setter of Score
void Scoring::SetScore(int s) { this->player_score = s; }
int Scoring::GetScore() { return player_score; }

// Getter and Setter of Gamer Name
void Scoring::SetName(string n) {
  name = n;
}
string Scoring::GetName() { return name; }

// Writing Scores under the gamertag in the score sheet file
void Scoring::WriteScore() {

  auto score_on_sheet = this->ReadScore();

  // Check if there are entries in the score sheet
  if (score_on_sheet.size() > 0) {
    try {

      // Check if previous score is beaten
      if (score_on_sheet.at(this->name) < this->player_score) {
        cout << "New Score " << this->player_score
             << " beats the previous best score of "
             << score_on_sheet.at(this->name) << endl;
        score_on_sheet.erase(this->name);
        score_on_sheet.emplace(std::make_pair(this->name, this->player_score));

        // write scores on the sheet
        std::map<string, int>::iterator it;
        ofstream score_sheet;
        score_sheet.open(score_sheet_file_path, std::ios::in | std::ios::out);
        for (std::pair<std::string, int> element : score_on_sheet) {
          score_sheet << element.first << " " << element.second << std::endl;
        }
        score_sheet.close();
        score_sheet.clear();
      } else {
        cout << "New score " << this->player_score
             << " did not beat the previous best score of "
             << score_on_sheet.at(this->name) << endl;
      }
    } catch (...) {

      // New GamerTag found
      cout << "New user. Setting score." << endl;
      ofstream score_sheet;
      score_sheet.open(score_sheet_file_path,
                       std::ios::in | std::ios::out | std::ios::app);
      score_sheet << this->name << " " << this->player_score << endl;
      score_sheet.close();
      score_sheet.clear();
    }
  } else {

    // If there are no scores on the score sheet
    cout << "There are no scores yet" << endl;
    ofstream score_sheet;
    score_sheet.open(score_sheet_file_path, std::ios::in | std::ios::out);
    score_sheet << this->name << " " << this->player_score << endl;
    score_sheet.close();
    score_sheet.clear();
  }
}

std::map<string, int> Scoring::ReadScore() {

  // Reading the score sheet
  std::map<string, int> player_scores;
  string my_name, line, comma;
  int my_score;
  std::istringstream linestream(line);
  // Read Scores from the score sheet
  ifstream score_sheet(score_sheet_file_path);

  if (score_sheet.is_open()) {
    while (std::getline(score_sheet, line)) {
      std::istringstream linestream(line);

      while (linestream >> my_name >> my_score) {
        player_scores.insert(std::make_pair(my_name, my_score));
      }
    }
    // Close the score sheet file
    score_sheet.close();

  } else {
    std::ofstream outfile(score_sheet_file_path);
    std::cout << "score sheet file does not exist. New is created."
              << std::endl;
  }

  return player_scores;
}