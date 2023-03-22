#include "StudentWorld.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_board = new Board();
    m_bank_total = 0;
}
StudentWorld::~StudentWorld()
{}

Board* StudentWorld::getBoard()
{
    return m_board;
}

Player_Avatar* StudentWorld::getPeach()
{
    return m_peach;
}
Player_Avatar* StudentWorld::getYoshi()
{
    return m_yoshi;
}
vector<Player_Avatar*> StudentWorld::getPlayers()
{
    return m_players;
}
void StudentWorld::addToBank(int num)
{
    m_bank_total += num;    
}
int StudentWorld::getBank()
{
    return m_bank_total;
}
void StudentWorld::emptyBank()
{
    m_bank_total = 0;
}
void StudentWorld::addDroppingSquare(int x, int y)
{
    for (int i = 0; i < m_actors.size(); i++)
    {
        if (m_actors.at(i)->getX() == x && m_actors.at(i)->getY() == y)
        {
            if (m_actors.at(i)->isDestructable())
            {
                delete m_actors.at(i);
                m_actors.erase(m_actors.begin() + i);
                Dropping_Square* dropping_square = new Dropping_Square(IID_DROPPING_SQUARE, x, y, GraphObject::right, 1, 1, this);
                //m_actors.at(i) = dropping_square;
                m_actors.push_back(dropping_square);
                return;
            }
        }
    }
}
void StudentWorld::addVortex(int x, int y, int walkDir)
{
    Vortex* vortex = new Vortex(IID_VORTEX, x, y, GraphObject::right, 0, 1, this, walkDir);
    m_actors.push_back(vortex);

}
bool StudentWorld::checkOverlap(int x, int y, int vx, int vy)
{
    //left side
    if (x <= vx && x + 15 >= vx)
    {
        //bottom left corner
        if (y <= vy && y + 15 >= vy)
            return true;
        //top left corner
        if (y <= vy + 15 && y + 15 >= vy + 15)
            return true;
    }
    //right side
    if (x <= vx + 15 && x + 15 >= vx + 15)
    {
        //bottom right corner
        if (y <= vy && y + 15 >= vy)
            return true;
        //top right corner
        if (y <= vy + 15 && y + 15 >= vy + 15)
            return true;
    }
    return false;
}
Actor* StudentWorld::checkVortex(int x, int y)
{
    for (int i = 0; i < m_actors.size(); i++)
    {
        
        if (checkOverlap(x, y, m_actors.at(i)->getX(), m_actors.at(i)->getY()))
        {
            if (m_actors.at(i)->isImpact())
            {
                return m_actors.at(i);
            }
                
        }
        
    }
    return nullptr;
}

int StudentWorld::init()
{
    string board_file = this->assetPath() + "board0" + to_string(this->getBoardNumber()) + ".txt";
    if (m_board->loadBoard(board_file) == Board::LoadResult::load_success)
    {
        for (int i = 0; i < SPRITE_WIDTH; i++)
        {
            for (int j = 0; j < SPRITE_HEIGHT; j++)
            {
                Board::GridEntry result = m_board->getContentsOf(i, j);
                switch (result)
                {
                case Board::empty:
                    break;
                case Board::player:
                {
                    Player_Avatar* peach = new Player_Avatar(IID_PEACH, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 0, 1, 1, this);
                    m_actors.push_back(peach);
                    m_peach = peach;
                    Player_Avatar* yoshi = new Player_Avatar(IID_YOSHI, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 0, 1, 2, this);
                    m_actors.push_back(yoshi);
                    m_yoshi = yoshi;
                    m_players.push_back(peach);
                    m_players.push_back(yoshi);
                    Coin_Square* blue_square = new Coin_Square(IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, Coin_Square::CoinStatus::give3, this);
                    m_actors.push_back(blue_square);
                    break;
                }
                case Board::blue_coin_square:
                {
                    Coin_Square* blue_square = new Coin_Square(IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, Coin_Square::CoinStatus::give3, this);
                    m_actors.push_back(blue_square);
                    break;
                }
                case Board::red_coin_square:
                {
                    Coin_Square* red_square = new Coin_Square(IID_RED_COIN_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, Coin_Square::CoinStatus::take3, this);
                    m_actors.push_back(red_square);
                    break;
                }
                case Board::star_square:
                {
                    Star_Square* star_square = new Star_Square(IID_STAR_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, this);
                    m_actors.push_back(star_square);
                    break;
                }
                case Board::left_dir_square:
                {
                    Directional_Square* directional_square = new Directional_Square(IID_DIR_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::left, 1, 1, this);
                    m_actors.push_back(directional_square);
                    break;
                }
                case Board::right_dir_square:
                {
                    Directional_Square* directional_square = new Directional_Square(IID_DIR_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, this);
                    m_actors.push_back(directional_square);
                    break;
                }
                case Board::up_dir_square:
                {
                    Directional_Square* directional_square = new Directional_Square(IID_DIR_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::up, 1, 1, this);
                    m_actors.push_back(directional_square);
                    break;
                }
                case Board::down_dir_square:
                {
                    Directional_Square* directional_square = new Directional_Square(IID_DIR_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::down, 1, 1, this);
                    m_actors.push_back(directional_square);
                    break;
                }
                case Board::bank_square:
                {
                    Bank_Square* bank_square = new Bank_Square(IID_BANK_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, this);
                    m_actors.push_back(bank_square);
                    break;
                }
                
                case Board::bowser:
                {
                    Baddie* bowser = new Bowser(IID_BOWSER, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 0, 1, this);
                    m_actors.push_back(bowser);
                    Coin_Square* blue_square = new Coin_Square(IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, Coin_Square::CoinStatus::give3, this);
                    m_actors.push_back(blue_square);
                    break;
                }
                case Board::boo:
                {
                    Baddie* boo = new Boo(IID_BOO, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 0, 1, this);
                    m_actors.push_back(boo);
                    Coin_Square* blue_square = new Coin_Square(IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, Coin_Square::CoinStatus::give3, this);
                    m_actors.push_back(blue_square);
                    break;
                }
                case Board::event_square:
                {
                    Event_Square* event_square = new Event_Square(IID_EVENT_SQUARE, SPRITE_WIDTH * i, SPRITE_HEIGHT * j, GraphObject::right, 1, 1, this);
                    m_actors.push_back(event_square);
                    break;
                }
                }
            }
        }
        startCountdownTimer(99);
        return GWSTATUS_CONTINUE_GAME;
    }
    else
        return GWSTATUS_BOARD_ERROR;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    
    for (int i = 0; i < m_actors.size(); i++)
    {
        if (m_actors.at(i)->getActivityState() == Actor::ActivityState::inactive)
        {
            delete m_actors.at(i);
            m_actors.erase(m_actors.begin() + i);
            continue;
        }
        m_actors.at(i)->doSomething();
    }

    // P1 Roll: 3 Stars: 2 $$: 15 | Time: 75 | Bank: 9 | P2 Roll: 0 Stars: 1 $$: 22 VOR
    string p1text = "P1 Roll: " + to_string(getPeach()->getSpacesToMove()) + " Stars: " + to_string(getPeach()->getStars())
    + " $$: " + to_string(getPeach()->getCoins()) + " " + getPeach()->getVortexString();
    string p2text = "P2 Roll: " + to_string(getYoshi()->getSpacesToMove()) + " Stars: " + to_string(getYoshi()->getStars())
    + " $$: " + to_string(getYoshi()->getCoins()) + " " + getYoshi()->getVortexString();
    string center = " | Time: " + to_string(timeRemaining()) + " | Bank: " + to_string(getBank()) + " | ";
    setGameStatText(p1text + center + p2text);

    if (timeRemaining() <= 0)
    {
        playSound(SOUND_GAME_FINISHED);
        if (getPeach()->getStars() > getYoshi()->getStars())
        {
            setFinalScore(getPeach()->getStars(), getPeach()->getCoins());
            return GWSTATUS_PEACH_WON;
        }
        else if (getPeach()->getStars() < getYoshi()->getStars())
        {
            setFinalScore(getYoshi()->getStars(), getYoshi()->getCoins());
            return GWSTATUS_YOSHI_WON;
        }
        else if (getPeach()->getCoins() > getYoshi()->getCoins())
        {
            setFinalScore(getPeach()->getStars(), getPeach()->getCoins());
            return GWSTATUS_PEACH_WON;
        }
        else if (getPeach()->getCoins() < getYoshi()->getCoins())
        {
            setFinalScore(getYoshi()->getStars(), getYoshi()->getCoins());
            return GWSTATUS_YOSHI_WON;
        }
        else
        {
            int winner = randInt(1, 2);
            if (winner == 1)
            {
                setFinalScore(getPeach()->getStars(), getPeach()->getCoins());
                return GWSTATUS_PEACH_WON;
            }
            setFinalScore(getYoshi()->getStars(), getYoshi()->getCoins());
            return GWSTATUS_YOSHI_WON;
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i < m_actors.size(); i++)
        delete m_actors.at(i);
    m_actors.clear();
    delete m_board;
}
