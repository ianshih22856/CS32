#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class StudentWorld : public GameWorld
{
public:
  StudentWorld(string assetPath);
  virtual ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  Board* getBoard();
  Player_Avatar* getPeach();
  Player_Avatar* getYoshi();
  void addToBank(int num);
  void emptyBank();
  int getBank();
  vector<Player_Avatar*> getPlayers();
  void addDroppingSquare(int x, int y);
  void addVortex(int x, int y, int walkDir);
  Actor* checkVortex(int x, int y);
  bool checkOverlap(int x, int y, int vx, int vy);
private:
	vector<Actor*> m_actors = {};
	Board* m_board;
	Player_Avatar* m_peach;
	Player_Avatar* m_yoshi;
	vector<Player_Avatar*> m_players = {};
	int m_bank_total;

};

#endif // STUDENTWORLD_H_
