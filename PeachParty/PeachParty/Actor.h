#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
#include <vector>
using namespace std;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// actor list: Peach, Yoshi
// Coin Squares, Star Squares, Directional Squares, Bank Squares, Event Squares, Dropping Squares
// Boo, Bowser, Vortexes

class StudentWorld;

class Actor : public GraphObject
{
	public: 
		enum ActivityState
		{
			active, inactive
		};
		Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
		virtual ~Actor();
		virtual void doSomething() = 0;
		StudentWorld* getWorld();
		void setWalkDirection(int dir);
		int getWalkDirection() const;
		void setWalkAndSpriteDirection(int dir);
		int returnValidDirection(int currentWalkDir);
		bool checkCoord();
		bool canWalk(int dir);
		void findPossibleDirs(vector<int>& v);
		int getTicks();
		void setTicks(int ticks);
		void subtractTicks(int ticks);
		void setActivityState(ActivityState state);
		ActivityState getActivityState();
		bool isDestructable();
		void setDestructable(bool value);
		bool isImpact();
		void setImpact(bool value);
		void setTeleport(bool value);
		bool getTeleport();
		void findRandomCoord(int& x, int& y);
		void teleport(Actor* a);

	private:
		StudentWorld* m_gameworld;	
		int m_walkDir;
		int m_ticks_to_move;
		ActivityState m_state;
		bool m_destructable;
		bool m_impact;
		bool m_teleport;

};

class Player_Avatar : public Actor
{
	public:
		enum PlayerState
		{
			walking, waiting_to_roll
		};
		enum PlayerFlag
		{
			new_player, old_player
		};
		Player_Avatar(int imageID, int startX, int startY, int dir, int depth, double size, int player_number, StudentWorld* gameworld);
		virtual ~Player_Avatar();
		virtual void doSomething();
		//bool canWalk(int dir);
		void addCoins(int amt);
		void addStars(int amt);
		int getCoins();
		int getStars();
		void setCoins(int amt);
		void setStars(int amt);
		void emptyCoins();
		void emptyStars();
		int getSpacesToMove();
		bool getVortex();
		string getVortexString();
		void setVortex(bool value);
		PlayerState getRollState();
		void setRollState(PlayerState state);
		void setFlag(PlayerFlag flag);
		PlayerFlag getFlag();

	private:	
		PlayerState m_rollstate;
		int m_ticks_to_move;
		int m_player_number; 
		int m_coincount;
		int m_starcount;
		bool m_vortexstate;
		PlayerFlag m_flag;
		
};

class Activating_Object : public Actor
{
public:
	
	Activating_Object(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Activating_Object();
	virtual void doSomething() = 0;
	bool checkPlayerOnSquare(Player_Avatar* player);
	bool checkPlayerLandOnSquare(Player_Avatar* player);
};

class Bank_Square : public Activating_Object
{
public:
	Bank_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Bank_Square();
	virtual void doSomething();
};

class Coin_Square : public Activating_Object
{
public:

	enum CoinStatus
	{
		give3, take3
	};
	Coin_Square(int imageID, int startX, int startY, int dir, int depth, double size, CoinStatus coin_status, StudentWorld* gameworld);
	virtual ~Coin_Square();
	virtual void doSomething();
private:
	CoinStatus m_coin_status;
	int m_coins;
};

class Directional_Square : public Activating_Object
{
public:
	Directional_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Directional_Square();
	virtual void doSomething();
private:
	int m_walkDir;
};
class Star_Square : public Activating_Object
{
public:
	Star_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Star_Square();
	virtual void doSomething();
};
class Dropping_Square : public Activating_Object
{
public:
	Dropping_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Dropping_Square();
	virtual void doSomething();
};

class Event_Square : public Activating_Object
{
public:
	Event_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Event_Square();
	virtual void doSomething();
	
};


class Baddie : public Activating_Object
{
public:
	enum BaddieState
	{
		paused, walking
	};
	Baddie(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Baddie();
	void doSomething();
	void subtractPauseCounter(int num);
	int getPauseCounter();
	void setPauseCounter(int num);
	BaddieState getState();
	void setState(Baddie::BaddieState state);
	virtual void impactPlayer(Player_Avatar* player) = 0;
	virtual int rollDie() = 0;
	virtual void DroppingSquare() = 0;
	bool getPFlag();
	bool getYFlag();
	void setPFlag(bool value);
	void setYFlag(bool value);
private:
	bool m_pflag;
	bool m_yflag;
	BaddieState m_state;
	int m_pause_counter;
};

class Bowser : public Baddie
{
public:
	Bowser(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Bowser();
	virtual void impactPlayer(Player_Avatar* player);
	virtual int rollDie();
	virtual void DroppingSquare();
};

class Boo : public Baddie
{
public:
	Boo(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld);
	virtual ~Boo();
	virtual void impactPlayer(Player_Avatar* player);
	virtual int rollDie();
	virtual void DroppingSquare();
};

class Vortex : public Activating_Object
{
public:
	Vortex(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld, int moveDir);
	virtual ~Vortex();
	virtual void doSomething();
private:
	int m_moveDir;
};
#endif // ACTOR_H_
