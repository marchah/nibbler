//
// Game.hh for Game in /home/marcha_j//test/c++/Nibbler/proj
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Mon Mar  5 16:36:36 2012 hugo marchadier
// Last update Wed Mar  7 18:24:24 2012 hugo marchadier
//

#ifndef	GAME_HH_
#define GAME_HH_

#include <list>
#include <string>

#include "Ressources/Defines.hh"
#include "Ressources/Coord.hh"

#include "Ressources/IDisplayModule.hh" /* a virer */

class	Game
{
  const int		_height;
  const int		_width;
  IDisplayModule * _obj;
  Dir			_dir;
  bool			_addLink;
  std::list<Coord>	_snake;
  Coord			_eat;
  int			_score;
  
  Game(const Game &);
  Game& operator=(const Game &);
  
  void	createEat();
  void	checkEat();
  void	move();
  void	GameOver();
  void	setDir(Dir);

public:
  Game(const int, const int, IDisplayModule *);
  ~Game();
  void	run();
};

class GameException : public std::exception
{
  std::string   _message;

public:
  GameException(std::string const &msg) : _message(msg) {}
  ~GameException() throw() {}
  std::string const &   getMessage() const throw()
  {
    return (this->_message);
  }
};


#endif // GAME_HH_
