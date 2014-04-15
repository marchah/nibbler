//
// DisplayModuleNcurses.hh for DisplayModuleNcurses in /home/marcha_j//test/c++/Nibbler/Ncurses
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Tue Mar  6 18:28:36 2012 hugo marchadier
// Last update Wed Mar  7 18:30:11 2012 hugo marchadier
//

#ifndef	DISPLAYMODULENCURSES_H_
#define DISPLAYMODULENCURSES_H_

#include <list>

#include <ncurses.h>
#include <panel.h>

#include "../Ressources/IDisplayModule.hh"
#include "../Ressources/Coord.hh"


class DisplayModuleNcurses : public IDisplayModule
{
  int		_width;
  int		_height;
  WINDOW*	_win;

  DisplayModuleNcurses(const DisplayModuleNcurses &);
  DisplayModuleNcurses& operator=(const DisplayModuleNcurses &);

  void	create_box(const int);
  void	drawSnake(const std::list<Coord>&);
  void	drawEat(const Coord &);
public:
  DisplayModuleNcurses();
  virtual ~DisplayModuleNcurses();

  virtual void	draw(const std::list<Coord>& snake, const Coord& eat, const int);
  virtual Dir	getEvent();
  virtual void	init(const int, const int);
  virtual void	stop();
};

#endif // DISPLAYMODULENCURSES_H_
