//
// Game.cpp for Game in /home/marcha_j//test/c++/Nibbler/proj
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Mon Mar  5 16:39:15 2012 hugo marchadier
// Last update Wed Mar 14 18:43:23 2012 fabien karquel
//

#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <sys/time.h>

#include "Game.hh"
#include "Ressources/Defines.hh"
#include "Ressources/IDisplayModule.hh"

Game::Game(const int height, const int width, IDisplayModule * obj)
  : _height(height), _width(width), _obj(obj), _dir(RIGHT), _addLink(false)
{
  int	nb = 0;

  srand(time(NULL));
  while (nb != Sizes::INIT_SNAKE)
    {
      this->_snake.push_back(Coord((height / 2), (width / 2) - nb));
      nb = nb + 1;
    }
}

Game::~Game()
{

}

void	Game::move()
{
  Coord	tmp;

  tmp = this->_snake.front();
  if (this->_addLink == true)
    this->_addLink = false;
  else
    this->_snake.pop_back();
  switch (this->_dir)
    {
    case UP:
      tmp._y -= 1;
      break;
    case DOWN:
      tmp._y += 1;
      break;
    case LEFT:
      tmp._x -= 1;
      break;
    case RIGHT:
      tmp._x += 1;
      break;
    default: break;
    }
  this->_snake.push_front(tmp);
}

void	Game::createEat()
{
  Coord	eat;
  bool	status = false;

  while (status == false)
    {
      eat._x = rand() % this->_width;
      eat._y = rand() % this->_height;
      if (find(this->_snake.begin(), this->_snake.end(), eat)
	  == this->_snake.end())
	{
	  status = true;
	  this->_eat = eat;
	}
    }
}

void	Game::checkEat()
{
  if (this->_eat == this->_snake.front())
    {
      this->_addLink = true;
      this->createEat();
      this->_score += Rules::POINT;
    }
}

void	Game::GameOver()
{
  std::stringstream os;

  os << this->_score;
  std::list<Coord>::iterator it = this->_snake.begin();
  Coord	head = this->_snake.front();

  if (this->_snake.size() >= (this->_height * this->_width))
    {
      delete this->_obj;
      throw GameException("Congratulation, you win: Your score is " + os.str() + ".");
    }
  if (head._x < 0 || head._y < 0 || head._x >= this->_width || head._y >= this->_height)
    {
      delete this->_obj;
      throw GameException("Game Over: Your score is " + os.str() + ".");
    }
  if (find(++it, this->_snake.end(), head) != this->_snake.end())
    {
      delete this->_obj;
      throw GameException("Game Over: Your score is " + os.str() + ".");
    }
}

void	timeval_diff(struct timeval *diff,
			     struct timeval *end_time,
			     struct timeval *start_time)
{
  struct timeval	temp_diff;

  if (diff == NULL)
    diff = &temp_diff;
  diff->tv_sec = end_time->tv_sec - start_time->tv_sec;
  diff->tv_usec = end_time->tv_usec - start_time->tv_usec;
  while (diff->tv_usec < 0)
  {
    diff->tv_usec+=1000000;
    diff->tv_sec -=1;
  }
}

void	Game::run()
{
  bool			status = true;
  Dir			tmp;
  int			speed = Rules::SPEED_INIT;
  struct timeval	earlier;
  struct timeval	later;
  struct timeval	interval;

  gettimeofday(&earlier, NULL);
  this->_score = 0;
  this->createEat();
  this->_obj->init(this->_width, this->_height);
  while (status)
  {
    tmp = NONE;
    this->GameOver();
    this->checkEat();
    this->_obj->draw(this->_snake, this->_eat, this->_score);
    if ((tmp = this->_obj->getEvent()) == QUIT)
    {
      delete this->_obj;
      return ;
    }
    if (tmp == SPACE && speed == Rules::SPEED_INIT)
      speed = Rules::SPEED_MAX;
    else if (tmp == SPACE && speed == Rules::SPEED_MAX)
      speed = Rules::SPEED_INIT;
    else if (tmp != NONE)
      this->setDir(tmp);
    gettimeofday(&later, NULL);
    timeval_diff(&interval, &later, &earlier);
    if (interval.tv_sec > 0 || interval.tv_usec > (Rules::TIME / speed))
    {
      this->move();
      gettimeofday(&earlier,NULL);
    }
  }
}

void	Game::setDir(Dir dir)
{
  if ((dir == UP && this->_dir == DOWN)
      || (dir == DOWN && this->_dir == UP)
      || (dir == RIGHT && this->_dir == LEFT)
      || (dir == LEFT && this->_dir == RIGHT))
    return ;

  this->_dir = dir;
  return ;
  if (dir == RIGHT && this->_dir == RIGHT)
    dir = DOWN;
  else if (dir == LEFT && this->_dir == RIGHT)
    dir = UP;
  if (dir == RIGHT && this->_dir == LEFT)
    dir = UP;
  else if (dir == LEFT && this->_dir == LEFT)
    dir = DOWN;

  if (dir == RIGHT && this->_dir == UP)
    dir = RIGHT;
  else if (dir == LEFT && this->_dir == UP)
    dir = LEFT;
  if (dir == RIGHT && this->_dir == DOWN)
    dir = LEFT;
  else if (dir == LEFT && this->_dir == DOWN)
    dir = RIGHT;

  this->_dir = dir;
}
