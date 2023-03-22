#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>	
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	: GraphObject(imageID, startX, startY, dir, depth, size)
{
	m_gameworld = gameworld;
	m_ticks_to_move = 0;
	m_state = active;	
	m_teleport = false;
}
Actor::~Actor()
{}

StudentWorld* Actor::getWorld()
{
	return m_gameworld;
}
void Actor::setWalkDirection(int dir)
{
	m_walkDir = dir;
}
int Actor::getWalkDirection() const
{
	return m_walkDir;
}
void Actor::setWalkAndSpriteDirection(int dir)
{
	setWalkDirection(dir);
	if (dir == left)
		setDirection(left);
	else
		setDirection(right);
}
int Actor::returnValidDirection(int currentWalkDir)
{
	int tempX, tempY;
	if (currentWalkDir == right || currentWalkDir == left)
	{
		getPositionInThisDirection(up, SPRITE_HEIGHT, tempX, tempY);
		if (getWorld()->getBoard()->getContentsOf(tempX / SPRITE_WIDTH, tempY / SPRITE_HEIGHT) != Board::GridEntry::empty)
			return up;
		return down;
	}
	getPositionInThisDirection(right, SPRITE_HEIGHT, tempX, tempY);
	if (getWorld()->getBoard()->getContentsOf(tempX / SPRITE_WIDTH, tempY / SPRITE_HEIGHT) != Board::GridEntry::empty)
		return right;
	return left;
}
bool Actor::checkCoord() //return true if at corner of square (not in middle)
{
	if (getX() % SPRITE_WIDTH != 0 || getY() % SPRITE_HEIGHT != 0)
		return false;
	return true;
}
bool Actor::canWalk(int dir) //if object can walk in direction and is at corner of sqaure
{
	int tempX, tempY;
	getPositionInThisDirection(dir, SPRITE_HEIGHT, tempX, tempY);
	/*if (tempX % SPRITE_WIDTH != 0 || tempY % SPRITE_HEIGHT != 0)
		return false;*/
	if (tempX < 0 || tempX > VIEW_WIDTH || tempY < 0 || tempY > VIEW_HEIGHT)
		return false;
	if (getWorld()->getBoard()->getContentsOf(tempX / SPRITE_WIDTH, tempY / SPRITE_HEIGHT) == Board::GridEntry::empty)
		return false;
	return true;
}
void Actor::findPossibleDirs(vector<int>& v)
{
	for (int i = 0; i != 360; i += 90)
	{
		if (canWalk(i))
			v.push_back(i);
	}
}
int Actor::getTicks()
{
	return m_ticks_to_move;
}
void Actor::subtractTicks(int ticks)
{
	m_ticks_to_move -= ticks;
}
void Actor::setTicks(int ticks)
{
	m_ticks_to_move = ticks;
}
void Actor::setActivityState(ActivityState state)
{
	m_state = state;
}
Actor::ActivityState Actor::getActivityState()
{
	return m_state;
}
bool Actor::isDestructable()
{
	return m_destructable;
}
void Actor::setDestructable(bool value)
{
	m_destructable = value;
}

bool Actor::isImpact()
{
	return m_impact;
}
void Actor::setImpact(bool value)
{
	m_impact = value;
}
void Actor::setTeleport(bool value)
{
	m_teleport = value;
}
bool Actor::getTeleport()
{
	return m_teleport;
}
void Actor::findRandomCoord(int& x, int& y)
{
	x = randInt(0, BOARD_WIDTH - 1);
	y = randInt(0, BOARD_HEIGHT - 1);
	while (getWorld()->getBoard()->getContentsOf(x, y) == Board::GridEntry::empty)
	{
		x = randInt(0, BOARD_WIDTH - 1);
		y = randInt(0, BOARD_HEIGHT - 1);
	}
}
void Actor::teleport(Actor* a)
{
	int x, y;
	findRandomCoord(x, y);
	a->moveTo(x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
}
Player_Avatar::Player_Avatar(int imageID, int startX, int startY, int dir, int depth, double size, int player_number, StudentWorld* gameworld)
	:Actor(imageID, startX, startY, dir, depth, size, gameworld)
{
	m_rollstate = waiting_to_roll;
	m_player_number = player_number;
	m_starcount = 0;
	m_coincount = 0;
	m_vortexstate = false;
	m_flag = new_player;
	setWalkAndSpriteDirection(dir);
	setDestructable(false);
	setImpact(false);
}
Player_Avatar::~Player_Avatar()
{
}

void Player_Avatar::addCoins(int amt)
{
	m_coincount += amt;
	if (m_coincount < 0)
		m_coincount = 0;
}
void Player_Avatar::addStars(int amt)
{
	m_starcount += amt;
	if (m_starcount < 0)
		m_starcount = 0;
}
void Player_Avatar::setCoins(int amt)
{
	m_coincount = amt;
}
void Player_Avatar::setStars(int amt)
{
	m_starcount = amt;
}
int Player_Avatar::getSpacesToMove()
{
	return getTicks() / 8;
}
int Player_Avatar::getCoins()
{
	return m_coincount;
}
int Player_Avatar::getStars()
{
	return m_starcount;
}
void Player_Avatar::emptyCoins()
{
	m_coincount = 0;
}
void Player_Avatar::emptyStars()
{
	m_starcount = 0;
}
bool Player_Avatar::getVortex()
{
	return m_vortexstate;
}
string Player_Avatar::getVortexString()
{
	if (getVortex())
		return "VOR";
	return "";
}
void Player_Avatar::setVortex(bool value)
{
	m_vortexstate = value;
}
Player_Avatar::PlayerState Player_Avatar::getRollState()
{
	return m_rollstate;
}
void Player_Avatar::setRollState(PlayerState state)
{
	m_rollstate = state;
}

void Player_Avatar::setFlag(PlayerFlag flag)
{
	m_flag = flag;
}
Player_Avatar::PlayerFlag Player_Avatar::getFlag()
{
	return m_flag;
}

void Player_Avatar::doSomething()
{
	if (m_rollstate == waiting_to_roll)
	{
		if (getWalkDirection() < 0)
		{
			vector<int> possibleDirs = {};
			findPossibleDirs(possibleDirs);
			setWalkAndSpriteDirection(possibleDirs.at(randInt(0, possibleDirs.size() - 1)));
		}
		vector<int> v = {};
		findPossibleDirs(v);
		int tempX, tempY;
		if (v.size() > 2)
		{}
		else if (getWalkDirection() == up || getWalkDirection() == right)
		{
			getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, tempX, tempY);
			if (getWorld()->getBoard()->getContentsOf(tempX / SPRITE_WIDTH, tempY / SPRITE_HEIGHT) == Board::GridEntry::empty)
				setWalkAndSpriteDirection(returnValidDirection(getWalkDirection()));
		}
		else
		{
			getPositionInThisDirection(getWalkDirection(), 2, tempX, tempY);
			if (getWorld()->getBoard()->getContentsOf(tempX / SPRITE_WIDTH, tempY / SPRITE_HEIGHT) == Board::GridEntry::empty || tempX < 0 || tempY < 0)
				setWalkAndSpriteDirection(returnValidDirection(getWalkDirection()));
		}
		switch (getWorld()->getAction(m_player_number))
		{
		case ACTION_ROLL:
		{
			int die_roll = randInt(1, 10);
			/*int die_roll;
			cout << "roll: ";
			cin >> die_roll;*/
			setTicks(die_roll * 8);
			m_rollstate = walking;
			//	cout << "done" << endl;
			//	//cout << "(x: " << getX() << ", y: " << getY() << ") || " << "(x: " << getX() / SPRITE_WIDTH << ", y: " << getY() / SPRITE_HEIGHT << ")" << endl;
			break;
		}
		case ACTION_FIRE:
		{
			if (getVortex())
			{
				getWorld()->addVortex(getX(), getY(), getWalkDirection());
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				setVortex(false);
			}
			break;
		}
		default:
		{
			return;
		}
		}
	}
	if (m_rollstate == walking)
	{
		setFlag(PlayerFlag::new_player);
		
		if (!checkCoord())
		{}
		else if (getWorld()->getBoard()->getContentsOf(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT) == Board::GridEntry::down_dir_square)
			setWalkAndSpriteDirection(down);
		else if (getWorld()->getBoard()->getContentsOf(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT) == Board::GridEntry::up_dir_square)
			setWalkAndSpriteDirection(up);
		else if (getWorld()->getBoard()->getContentsOf(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT) == Board::GridEntry::left_dir_square)
			setWalkAndSpriteDirection(left);
		else if (getWorld()->getBoard()->getContentsOf(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT) == Board::GridEntry::right_dir_square)
			setWalkAndSpriteDirection(right);
		else
		{
			vector<int> possibleDirs = {};
			findPossibleDirs(possibleDirs);
			/*for (int i = 0; i < possibleDirs.size(); i++)
			{
				cout << possibleDirs.at(i) << ", " << endl;
			}*/
			//cout << possibleDirs.size() << endl;
			if (possibleDirs.size() > 2)
			{
				int action = getWorld()->getAction(m_player_number);
				switch (action)
				{
				case ACTION_LEFT:
				{
					if (find(possibleDirs.begin(), possibleDirs.end(), left) != possibleDirs.end() && getWalkDirection() != right)
					{
						setWalkAndSpriteDirection(left);
						break;
					}
					else
						return;
				}
				case ACTION_RIGHT:
				{
					if (find(possibleDirs.begin(), possibleDirs.end(), right) != possibleDirs.end() && getWalkDirection() != left)
					{
						setWalkAndSpriteDirection(right);
						break;
					}
					else
						return;
				}
				case ACTION_UP:
				{
					if (find(possibleDirs.begin(), possibleDirs.end(), up) != possibleDirs.end() && getWalkDirection() != down)
					{
						setWalkAndSpriteDirection(up);
						break;
					}
					else
						return;
				}
				case ACTION_DOWN:
				{
					if (find(possibleDirs.begin(), possibleDirs.end(), down) != possibleDirs.end() && getWalkDirection() != up)
					{
						setWalkAndSpriteDirection(down);
						break;
					}
					else
						return;
				}
				default:
					return;
				
				}
			}
			else if (!canWalk(getWalkDirection()))
			{
				int tempX, tempY;
				if (getWalkDirection() == up || getWalkDirection() == right)
				{
					getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, tempX, tempY);
					if (getWorld()->getBoard()->getContentsOf(tempX / SPRITE_WIDTH, tempY / SPRITE_HEIGHT) == Board::GridEntry::empty)
						setWalkAndSpriteDirection(returnValidDirection(getWalkDirection()));
				}
				else
				{
					getPositionInThisDirection(getWalkDirection(), 2, tempX, tempY);
					if (getWorld()->getBoard()->getContentsOf(tempX / SPRITE_WIDTH, tempY / SPRITE_HEIGHT) == Board::GridEntry::empty || tempX < 0 || tempY < 0)
						setWalkAndSpriteDirection(returnValidDirection(getWalkDirection()));
				}
			}
		}
		//cout << "(x: " << getX() << ", y: " << getY() << ")" << endl;
		moveAtAngle(getWalkDirection(), 2);
		subtractTicks(1);
		if (getTicks() == 0)
		{
			m_rollstate = waiting_to_roll;
		}

	}
}

Activating_Object::Activating_Object(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld) 
	:Actor(imageID, startX, startY, dir, depth, size, gameworld)
{
}
Activating_Object::~Activating_Object()
{}



bool Activating_Object::checkPlayerOnSquare(Player_Avatar* player)
{
	if (player->getX() == getX() && player->getY() == getY())
		return true;
	return false;
}

bool Activating_Object::checkPlayerLandOnSquare(Player_Avatar* player)
{
	if (checkPlayerOnSquare(player))
	{
		if (player->getFlag() == Player_Avatar::PlayerFlag::new_player && player->getRollState() == Player_Avatar::PlayerState::waiting_to_roll)
		{
			
			return true;
		}
	}
	return false;
}

Coin_Square::Coin_Square(int imageID, int startX, int startY, int dir, int depth, double size, CoinStatus coin_status, StudentWorld* gameworld) 
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	m_coin_status = coin_status;
	if (coin_status == give3)
		m_coins = 3;
	if (coin_status == take3)
		m_coins = -3;
	setDestructable(true);
	setImpact(false);
}
Coin_Square::~Coin_Square()
{}
void Coin_Square::doSomething()
{
	if (getActivityState() == inactive)
		return;
	for (int i = 0; i < 2; i++)
	{
		if (checkPlayerLandOnSquare(getWorld()->getPlayers().at(i)))
		{
			getWorld()->getPlayers().at(i)->addCoins(m_coins);
			getWorld()->playSound(SOUND_GIVE_COIN);
			getWorld()->getPlayers().at(i)->setFlag(Player_Avatar::PlayerFlag::old_player);
		}
	}
	
	
}

Star_Square::Star_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	setDestructable(true);
	setImpact(false);
}
Star_Square::~Star_Square()
{}
void Star_Square::doSomething()
{
	for (int i = 0; i < 2; i++)
	{
		if (checkPlayerLandOnSquare(getWorld()->getPlayers().at(i)))
		{
			if (getWorld()->getPlayers().at(i)->getCoins() < 20)
				return;
			getWorld()->getPlayers().at(i)->addCoins(-20);
			getWorld()->getPlayers().at(i)->addStars(1);
			getWorld()->playSound(SOUND_GIVE_STAR);
			getWorld()->getPlayers().at(i)->setFlag(Player_Avatar::PlayerFlag::old_player);
		}
		
	}
}

Directional_Square::Directional_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	m_walkDir = dir;
	setDestructable(true);
	setImpact(false);
}
Directional_Square::~Directional_Square()
{}
void Directional_Square::doSomething()
{
	for (int i = 0; i < 2; i++)
	{
		if (checkPlayerOnSquare(getWorld()->getPlayers().at(i)))
		{
			getWorld()->getPlayers().at(i)->setWalkAndSpriteDirection(m_walkDir);
			getWorld()->getPlayers().at(i)->setFlag(Player_Avatar::PlayerFlag::old_player);
		}
		
	}
}

Bank_Square::Bank_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	setDestructable(true);
	setImpact(false);
}
Bank_Square::~Bank_Square()
{}
void Bank_Square::doSomething()
{
	for (int i = 0; i < 2; i++)
	{
		if (checkPlayerOnSquare(getWorld()->getPlayers().at(i)))
		{
			if (checkPlayerLandOnSquare(getWorld()->getPlayers().at(i)))
			{

				getWorld()->getPlayers().at(i)->addCoins(getWorld()->getBank());
				getWorld()->emptyBank();
				getWorld()->getPlayers().at(i)->setFlag(Player_Avatar::PlayerFlag::old_player);
				getWorld()->playSound(SOUND_WITHDRAW_BANK);
			}
			else if (getWorld()->getPlayers().at(i)->getRollState() == Player_Avatar::PlayerState::walking)
			{
				if (getWorld()->getPlayers().at(i)->getCoins() < 5)
					getWorld()->addToBank(getWorld()->getPlayers().at(i)->getCoins());
				else
					getWorld()->addToBank(5);
				getWorld()->getPlayers().at(i)->addCoins(-5);
				getWorld()->playSound(SOUND_DEPOSIT_BANK);
			}
		}
		
	}
}
Event_Square::Event_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	setDestructable(true);
	setImpact(false);
}
Event_Square::~Event_Square()
{}

void Event_Square::doSomething()
{
	for (int i = 0; i < 2; i++)
	{
		if (checkPlayerLandOnSquare(getWorld()->getPlayers().at(i)))
		{
			int option = randInt(1, 3);
			//int option = 3;
			if (option == 1)
			{
				teleport(getWorld()->getPlayers().at(i));
				getWorld()->playSound(SOUND_PLAYER_TELEPORT);
				getWorld()->getPlayers().at(i)->setWalkDirection(-1);
				//teleport
				
			}
			else if (option == 2)
			{
				Player_Avatar* base = getWorld()->getPlayers().at(i);
				Player_Avatar* other;
				if (i == 1)
					other = getWorld()->getPlayers().at(0);
				else
					other = getWorld()->getPlayers().at(1);
				int tempX, tempY, temp_ticks, temp_walk, temp_dir;
				Player_Avatar::PlayerState temp_roll;
				tempX = base->getX();
				tempY = base->getY();
				temp_ticks = base->getTicks();
				temp_dir = base->getDirection();
				temp_walk = base->getWalkDirection();
				temp_roll = base->getRollState();

				base->moveTo(other->getX(), other->getY());
				base->setTicks(other->getTicks());
				base->setDirection(other->getDirection());
				base->setWalkDirection(other->getWalkDirection());
				base->setRollState(other->getRollState());

				other->moveTo(tempX, tempY);
				other->setTicks(temp_ticks);
				other->setDirection(temp_dir);
				other->setWalkDirection(temp_walk);
				other->setRollState(temp_roll);	

				base->setFlag(Player_Avatar::PlayerFlag::new_player);
				other->setFlag(Player_Avatar::PlayerFlag::old_player);
				return;
			}
			else if (option == 3)
			{
				if (!getWorld()->getPlayers().at(i)->getVortex())
				{
					getWorld()->getPlayers().at(i)->setVortex(true);
					getWorld()->playSound(SOUND_GIVE_VORTEX);
				}
			}
		}
	}
}

Dropping_Square::Dropping_Square(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	setDestructable(false);
	setImpact(false);
}
Dropping_Square::~Dropping_Square()
{}
void Dropping_Square::doSomething()
{
	for (int i = 0; i < 2; i++)
	{
		if (checkPlayerLandOnSquare(getWorld()->getPlayers().at(i)))
		{
			if (getWorld()->getPlayers().at(i)->getStars() > 0)
				getWorld()->getPlayers().at(i)->addStars(-1);
			else
				getWorld()->getPlayers().at(i)->addCoins(-10);
			getWorld()->getPlayers().at(i)->setFlag(Player_Avatar::PlayerFlag::old_player);
			getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
		}

		
	}
}

Baddie::Baddie(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	m_state = paused;
	m_pause_counter = 180;
	setWalkDirection(right);
	setTicks(0);
	m_pflag = true;
	m_yflag = true;
	setDestructable(false);
	setImpact(true);
}
Baddie::~Baddie()
{}
void Baddie::subtractPauseCounter(int num)
{
	m_pause_counter -= num;
}
int Baddie::getPauseCounter()
{
	return m_pause_counter;
}
void Baddie::setPauseCounter(int num)
{
	m_pause_counter = num;
}
Baddie::BaddieState Baddie::getState()
{
	return m_state;
}
void Baddie::setState(Baddie::BaddieState state)
{
	m_state = state;
}
bool Baddie::getPFlag()
{
	return m_pflag;
}
bool Baddie::getYFlag()
{
	return m_yflag;
}
void Baddie::setPFlag(bool value)
{
	m_pflag = value;
}
void Baddie::setYFlag(bool value)
{
	m_yflag = value;
}


void Baddie::doSomething()
{
	if (getTeleport())
	{
		teleport(this);
		setWalkAndSpriteDirection(right);
		setState(paused);
		setTicks(180);
		setTeleport(false);
	}
	if (getState() == paused)
	{
		//cout << "pause" << endl;
		
		if (checkPlayerOnSquare(getWorld()->getYoshi()) && getYFlag() && getWorld()->getYoshi()->getRollState() == Player_Avatar::PlayerState::waiting_to_roll)
		{
			//cout << "LAND" << endl;	
			impactPlayer(getWorld()->getYoshi());
			setYFlag(false);
		}
		if (checkPlayerOnSquare(getWorld()->getPeach()) && getPFlag() && getWorld()->getPeach()->getRollState() == Player_Avatar::PlayerState::waiting_to_roll)
		{
			//cout << "LAND" << endl;	
			impactPlayer(getWorld()->getPeach());
			//getWorld()->getPeach()->setFlag(Player_Avatar::PlayerFlag::old_player);
			setPFlag(false);
		}
		
		subtractPauseCounter(1);
		if (getPauseCounter() == 0)
		{
			//different dice roll setTicks
			setTicks(rollDie());
			vector<int> possibleDirs = {};
			findPossibleDirs(possibleDirs);
			//for (int i = 0; i < possibleDirs.size(); i++)
			//	cout << possibleDirs.at(i) << ", ";
			int dir = possibleDirs.at(randInt(0, possibleDirs.size() - 1));
			//cout << "dir: " << dir << endl;
			//cout << "(x: " << getX() << ", y: " << getY() << ") || " << "(x: " << getX() / SPRITE_WIDTH << ", y: " << getY() / SPRITE_HEIGHT << ")" << endl;
			setWalkAndSpriteDirection(dir);
			setState(walking);
		}
	}
	if (getWorld()->getPeach()->getRollState() == Player_Avatar::PlayerState::walking || getState() == walking)
		setPFlag(true);
	if (getWorld()->getYoshi()->getRollState() == Player_Avatar::PlayerState::walking || getState() == walking)
		setYFlag(true);

	if (getState() == walking)
	{
		
		if (checkCoord())
		{
			vector<int> possibleDirs = {};
			findPossibleDirs(possibleDirs);
			//for (int i = 0; i < possibleDirs.size(); i++)
			//	cout << possibleDirs.at(i) << ", ";
			if (possibleDirs.size() > 2)
			{
				int dir = possibleDirs.at(randInt(0, possibleDirs.size() - 1));
				setWalkAndSpriteDirection(dir);
				//cout << "1" << endl;
			}
			else if (!canWalk(getWalkDirection()))
			{
				setWalkAndSpriteDirection(returnValidDirection(getWalkDirection()));
				//cout << "2" << endl;
			}
		}
		moveAtAngle(getWalkDirection(), 2);
		subtractTicks(1);
		if (getTicks() == 0)
		{
			setState(paused);
			setPauseCounter(180);
			//dropping square for bowser
			DroppingSquare();
		}
	}

}
Bowser::Bowser(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Baddie(imageID, startX, startY, dir, depth, size, gameworld)
{}
Bowser::~Bowser()
{}
void Bowser::impactPlayer(Player_Avatar* player)
{
	if (randInt(0, 1) == 0)
	{
		player->emptyCoins();
		player->emptyStars();
		getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
	}
}
int Bowser::rollDie()
{
	return randInt(1, 10) * 8;
}
void Bowser::DroppingSquare()
{
	if (randInt(1, 4) == 1)
	{
		if (getWorld()->getBoard()->getContentsOf(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT) == Board::GridEntry::blue_coin_square || getWorld()->getBoard()->getContentsOf(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT) == Board::GridEntry::red_coin_square)
		{
			getWorld()->addDroppingSquare(getX(), getY());
			getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
		}
	}
}
Boo::Boo(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld)
	:Baddie(imageID, startX, startY, dir, depth, size, gameworld)
{}
Boo::~Boo()
{}
void Boo::impactPlayer(Player_Avatar* player)
{
	if (randInt(0, 1) == 0)
	{
		int temp_holder = getWorld()->getPeach()->getCoins();
		getWorld()->getPeach()->setCoins(getWorld()->getYoshi()->getCoins());
		getWorld()->getYoshi()->setCoins(temp_holder);
	}
	else
	{
		int temp_holder = getWorld()->getPeach()->getStars();
		getWorld()->getPeach()->setStars(getWorld()->getYoshi()->getStars());
		getWorld()->getYoshi()->setStars(temp_holder);
	}
	getWorld()->playSound(SOUND_BOO_ACTIVATE);
}
int Boo::rollDie()
{
	return randInt(1, 3) * 8;
}
void Boo::DroppingSquare()
{}

Vortex::Vortex(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* gameworld, int moveDir)
	:Activating_Object(imageID, startX, startY, dir, depth, size, gameworld)
{
	m_moveDir = moveDir;
	setDestructable(false);
	setImpact(false);
}
Vortex::~Vortex()
{
}
void Vortex::doSomething()
{
	if (getActivityState() == inactive)
		return;

	moveAtAngle(m_moveDir, 2);
	if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setActivityState(inactive);
		return;
	}
	//
	Actor* p = getWorld()->checkVortex(getX(), getY());
	if (p != nullptr)
	{
		p->setTeleport(true);
		setActivityState(inactive);
		getWorld()->playSound(SOUND_HIT_BY_VORTEX);
	}
	
}
