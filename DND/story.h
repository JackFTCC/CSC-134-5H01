#ifndef STORY_H
#define STORY_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
#include "dnd.h"
using namespace std;

// DEFINE TO false TO SKIP ALL SAVES!
static const bool SAVE = true;


void main_menu();
void main_menu_fake();
void choice_prof();
void battle_victory_Prof();
void choice_adventure1();
void choice_go_home();
void choice_food();
void choice_bed();
void choice_break_in();
void experiencePoints(int xpGained);
void save_progress(int choice);
void displayCharacterAction();
void battleWithEnemy(const std::string& currentClass, int& strength, const std::string& enemy);
int get_saved_progress_for_player(const string& playerName);
int savedState = 1;

//NOTE - struct LevelData

struct LevelData {
  int level;
  int xpThreshold;
  int proficiencyBonus;
};

//NOTE - LevelData LevelTable

const LevelData levelTable[] = {
  {1, 0, 2},
  {2, 300, 2},
  {3, 900, 2},
  {4, 2700, 2},
  {5, 6500, 3},
  {6, 14000, 3},
  {7, 23000, 3},
  {8, 34000, 3},
  {9, 48000, 4},
  {10, 64000, 4},
  {11, 85000, 4},
  {12, 100000, 4},
  {13, 120000, 5},
  {14, 140000, 5},
  {15, 165000, 5},
  {16, 195000, 5},
  {17, 225000, 6},
  {18, 265000, 6},
  {19, 305000, 6},
  {20, 355000, 6}
};


//SECTION Main Game Loop

void main_menu() {
  static bool firstLoad = true;  // Tracks whether this is the first time loading progress
  int lastChoice = load_progress(); // Load last position
  string emoji;
  static bool partyMember = false;

  if (currentClass == "Fighter"){
      emoji = "⚔️";
  }
  else if (currentClass == "Magic-User"){
      emoji = "🧙";
  }
  else if (currentClass == "Thief"){
      emoji = "🗡️";
  }
  else if (currentClass == "Cleric"){
      emoji = "💉";
  }
  else if (currentClass == "Elf"){
      emoji = "🏹";
  }
  else if (currentClass == "Dwarf"){
      emoji = "🔨";
  }
  else if (currentClass == "Halfling"){
      emoji = "🔱";
  }
  if (lastChoice != 0 && firstLoad) {
      cout << "Resuming from your last choice: " << lastChoice << endl;
      firstLoad = false;  // Prevent message from appearing again
    switch (lastChoice) {
          case 1:
              choice_prof();
              break;
          case 2:
              choice_adventure1();
              break;
          case 3:
              choice_go_home();
              break;
          case 200:
              battle_victory_Prof();
              break;
          default:
              main_menu();
              break;
      }
  }
  else{
  // Normal game start if no progress exists
  cout << "" << endl;
  cout << "Welcome " << currentPlayer << " the " << currentClass << "." << endl;
  cout << "You've awakened as a " << currentClass << "." << endl;
  if (currentClass == "Fighter"){
    cout << "Since you're a fighter it makes you better at using physical abilites and brute force!" << endl;
  }
  else if (currentClass == "Magic-User"){
    cout << "Since you're a magic-user it gives you the immense power of abilites but you're weaker in health and physical combat." << endl;
  }
  else if (currentClass == "Thief"){
      cout << "Since you're a thief you're good at stealth and are really agile, but you're strength is weaker than most." <<endl;
  }
  else if (currentClass == "Cleric"){
      cout << "Since you're a cleric you are given the ability to heal people, and connect with nature. This comes with weaker health, but you have things to counteract that" << endl;
  }
  else if (currentClass == "Elf"){
      cout << "Since you're an elf you're good with bows and arrows, but you're more frail." << endl;
  }
  else if (currentClass == "Dwarf"){
      cout << "Since you're a dwarf you're stronger and you have the ability to make armor more powerful!"<< endl;
  }
  else if (currentClass == "Halfling"){
      cout << "Since you're a halfling you're a master with the spear." << endl;
  }
  cout << "Your journey begins here, the whole world ahead of you. What shall you do?" << endl;
  cout << "========================================" << endl;
  cout << emoji << "  : " << currentPlayer << " the " << currentClass << endl;
  if (partyMember){
      cout << "TODO" << endl;
  }
  cout << "1. Go find the professor to go explore" << endl;
  cout << "2. Go Adventure" << endl;
  cout << "3. Forget it, and go home" << endl;
  cout << "4. Stats" << endl;
  cout << "Choose: ";

  int choice;
  cin >> choice;
  if (SAVE) {save_progress(choice);}// Save progress at this step
  saveCharacter();

  switch (choice) {
      case 1:
          choice_prof();
          break;
      case 2:
          choice_adventure1();
          break;
      case 3:
          choice_go_home();
          break;
      case 4:
          displayCharacterAction();
          break;
      default:
          cout << "That's not a valid choice, please try again." << endl;
          cin.ignore();
          main_menu();
          break;
  }
}
}


void displayCharacterAction(){
  displayCharacter();
  saveCharacter();
  cout << "Any Key: Go back \n" << endl;
  string choice;
  cin >> choice;
  main_menu();
  }

void choice_prof() {
  if (SAVE) {save_progress(1);}
  if (savedState != 0){
  cout << "You appear at the professor's door, to be a adventurer you must defeat him...in a battle!" << endl;}
  else {
    cout << "" << endl;
  }
  cout << "Do you:" << endl;
  cout << "1. Fight the Professor!" << endl;
  cout << "2. Give up and go home" << endl;
  int choice;
  string enemy;
  cout << "Choose: ";
  cin >> choice;
  switch (choice){
    case 1:
    if (savedState != 0){
      enemy = "Professor";
      battleWithEnemy(currentClass, strength, enemy);
      break;
    }
    else {
      cout << "He won't fight you again." << endl;
      choice_prof();
    }
    case 2:
      choice_go_home();
      break;
    default:
      cout << "That's not a valid choice, please try again." << endl;
      cin.ignore();
      choice_prof();
      break;
  }
}

void battle_victory_Prof(){
  if (SAVE) {save_progress(200);}
  savedState = 200;
  cout << "He sends you off on your adventure and gives you a buff, you're ready" << endl;
  cout << "Do you:" << endl;
  cout << "1. Adventure!" << endl;
  cout << "2. Give up and go home" << endl;
  int choice;
  string enemy;
  cout << "Choose: ";
  cin >> choice;
  switch (choice){
    case 1:
      enemy = "Professor";
      battleWithEnemy(currentClass, strength, enemy);
      break;
    case 2:
      choice_go_home();
      break;
    default:
      cout << "That's not a valid choice, please try again." << endl;
      cin.ignore();
      choice_prof();
      break;
  }
}

void choice_adventure1() { 
  cout << "Nervous, you venture out..." << endl;
  cout << "Do you:" << endl;
  cout << "1. Continue Forward" << endl;
  cout << "2. Use the scary forest path" << endl;
  int choice;
  string enemy;
  cout << "Choose: ";
  cin >> choice;
  switch (choice){
    case 1:
      enemy = "GoblinLeader";
      battleWithEnemy(currentClass, strength, enemy);
      break;
    case 2:
      enemy = "Goblin";
      battleWithEnemy(currentClass, strength, enemy);
      break;
    default:
      cout << "That's not a valid choice, please try again." << endl;
      cin.ignore();
      choice_prof();
      break;
  }
}

void choice_go_home() {
  save_progress(2); 
  cout << "You go home." << endl;
  cout << "You're hungry " << endl;
  cout << "Do you:" << endl;
  cout << "1. Go out for food" << endl;
  cout << "2. Go to bed" << endl;
  int choice;
  cout << "Choose: ";
  cin >> choice;
  switch (choice){
    case 1:
      choice_food();
      break;
    case 2:
      choice_bed();
      break;
    default:
      cout << "That's not a valid choice, please try again." << endl;
      cin.ignore();
      choice_prof();
      break; 
  }
}

void choice_food(){
  save_progress(0);
  cout << "You drive for food..." << endl;
  cout << "Unfortunatley, since you live in a town where entering random houses is normal, someone stole the lugnuts on your tires causing them to fly off while driving" << endl; 
  cout << "~~~~~ Hungry Ending ~~~~~" << endl;
  cout << "          3/3        " << endl;
}

void choice_bed(){
  save_progress(0);
  cout << "You go to bed..." << endl;
  cout << "You live to see the next day!" << endl; 
  cout << "~~~~~ Lazy Ending ~~~~~" << endl;
  cout << "          2/3        " << endl;
}

void choice_break_in(){
  save_progress(0);
  srand(time(0));
  string enemy = "Door";
  
  battleWithEnemy(currentClass, strength, enemy);
  saveCharacter();
}

void battle_victory_doorHouse(){
  saveCharacter();
  main_menu();
}

//!SECTION





//NOTE - Save Progress

void save_progress(int choice) {
    if (currentPlayer.empty()) {
        cerr << "Error: No player name found. Progress not saved!" << endl;
        return;
    }

    map<string, string> progressMap;  // Map to store encrypted choices

    // Read existing progress data from the file
    ifstream progressFileRead("player_progress.txt", ios::in);
    if (progressFileRead) {
        string name, encryptedChoice;
        while (progressFileRead >> name >> encryptedChoice) {
            progressMap[name] = encryptedChoice;  // Store existing encrypted progress
        }
        progressFileRead.close();
    }

    // Encrypt the current player's progress
    string encryptedChoice = encryptStats(to_string(choice));
    progressMap[currentPlayer] = encryptedChoice;  // Update progress for the current player

    // Write the updated progress back to the file
    ofstream progressFileWrite("player_progress.txt", ios::out | ios::trunc);  // Open file for writing and truncate old content
    if (progressFileWrite) {
        for (const auto& entry : progressMap) {
            progressFileWrite << entry.first << " " << entry.second << endl;  // Write encrypted data
        }
        progressFileWrite.close();
        cout << "Progress saved for " << currentPlayer << endl;
    } else {
        cerr << "Error: Unable to save progress!" << endl;
    }
}

int get_saved_progress_for_player(const string& playerName) {
    ifstream progressFile("player_progress.txt");
    if (!progressFile) {
        cerr << "Warning: Could not open progress file." << endl;
        return 0;  // Default if no file exists
    }

    string name, encryptedChoice;
    while (progressFile >> name >> encryptedChoice) {
        if (name == playerName) {
            string decryptedChoice = decryptStats(encryptedChoice);
            try {
                return stoi(decryptedChoice);
            } catch (...) {
                cerr << "Error: Corrupted save data for player " << playerName << endl;
                return 0;
            }
        }
    }

    return 0; // No save found for this player
}


//NOTE - Enemy Battle

void battleWithEnemy(const std::string& currentClass, int& strength, const std::string& enemy) {
  srand(time(0));
  int youRoll = rollDice() + rollDice();
  int enemyRoll = rollDice() + rollDice();
  int enemyStrength = rollDice() + rollDice();

  if (enemy == "Door"){
    if (enemyStrength < 5){
      enemyStrength += 3;
    }
    else if (enemyStrength < 13 && enemyStrength > 15){
      enemyStrength -= 3;
    }
  }

  if (enemy == "Professor"){
    if (enemyStrength < 2){
      enemyStrength += 4;
    }
    else if (enemyStrength < 10 && enemyStrength > 20){
      enemyStrength -= 3;
    }
  }

  if (enemy == "GoblinLeader"){
    if (enemyStrength > 20){
      enemyStrength = 20;
    }
  }

  if (enemy == "Goblin"){
    if (enemyStrength < 2){
      enemyStrength += 4;
    }
    else if (enemyStrength < 15 && enemyStrength > 20){
      enemyStrength -= 5;
    }
  }

  std::cout << "" << std::endl;
  std::cout << enemy << " Strength: " << enemyStrength << std::endl;

  // Class-based adjustments
  if (currentClass == "Fighter") {
      std::cout << "You Roll " << youRoll << "!" << std::endl;
      std::cout << "You gain +3 for the class bonus!" << std::endl;
      youRoll += 3;
      if (youRoll > 20){
        youRoll = 20;
      }
      std::cout << "You Roll " << youRoll << "!" << std::endl;
  }
  else if (currentClass == "Thief") {
      std::cout << "You Roll " << youRoll << "!" << std::endl;
      std::cout << "You lose 3 for the class debuff" << std::endl;
      youRoll -= 3;
      if (youRoll < 0){
        youRoll = 0;
      }
      std::cout << "You Roll " << youRoll << "!" << std::endl;
  }
  else if (currentClass == "Magic-User") {
      std::cout << "You Roll " << youRoll << "!" << std::endl;
      std::cout << "You lose 5 for the class debuff" << std::endl;
      youRoll -= 5;
      if (youRoll < 0){
        youRoll = 0;
      }
      std::cout << "You Roll " << youRoll << "!" << std::endl;
  }
  int saveState = savedState;
  if (saveState >= 200) {
      std::cout << "You gain +1 from the professor bonus!" << std::endl;
      youRoll += 1;
      if (youRoll > 20){
        youRoll = 20;
      }
      std::cout << "Your New Roll " << youRoll << "!" << std::endl;
      std::cout << "" << std::endl;
  }
  else {
      std::cout << "" << std::endl;
  }

  std::cout << enemy << " Rolls " << enemyRoll << "!" << std::endl;

  // Adjust rolls based on strength difference
  if (strength > enemyStrength) {
      enemyRoll = enemyRoll - (strength - enemyStrength);
      std::cout << "Because you're stronger, you weaken the " << enemy << "'s roll!" << std::endl;
      if (enemyRoll < 0) {
          std::cout << "New "<< enemy <<" Roll " << 0 << "!" << std::endl;
      } else {
          std::cout << "New " << enemy << " Roll " << enemyRoll << "!" << std::endl;
      }
  }
  else if (enemyStrength > strength) {
      youRoll = youRoll - (enemyStrength - strength);
      std::cout << "Because you're weaker, the" << enemy << "weakens your roll!" << std::endl;
      if (youRoll < 0) {
          std::cout << "Your New Roll " << 0 << "!" << std::endl;
      } else {
          std::cout << "Your New Roll " << youRoll << "!" << std::endl;
      }
  }
  if (enemy == "Door"){
    if (youRoll > enemyRoll || youRoll == enemyRoll){
      cout << "You break it down!" << endl;
      battle_victory_doorHouse();
    }
    else {
      cout << "You don't break down the door" << endl;
      choice_go_home();
    }
  }
  if (enemy == "Professor"){
    if (youRoll > enemyRoll || youRoll == enemyRoll){
      cout << "You defeat the Professor!" << endl;
      battle_victory_Prof();
    }
    else {
      savedState = 0;
      cout << "You got kicked out..." << endl;
      choice_prof();
    }
  }
  if (enemy == "Goblin Leader"){
    if (youRoll > enemyRoll || youRoll == enemyRoll){
      cout << "How did you defeat a goblin leader? I literally made this impossible." << endl;
      battle_victory_Prof();
    }
    else {
      cout << "You die." << endl;
      choice_go_home();
    }
  }
}

//NOTE - Experience





#endif // STORY_H