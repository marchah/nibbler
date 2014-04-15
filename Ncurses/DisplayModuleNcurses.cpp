//
// DisplayModuleNcurses.cpp for DisplayModuleNcurses in /home/marcha_j//test/c++/Nibbler/Ncurses
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Tue Mar  6 18:33:00 2012 hugo marchadier
// Last update Wed Mar 14 18:29:19 2012 fabien karquel
//


#include "DisplayModuleNcurses.hh"

#include "../Ressources/Defines.hh"

DisplayModuleNcurses::DisplayModuleNcurses()
{

}

DisplayModuleNcurses::~DisplayModuleNcurses()
{
  if (this->_win != NULL)
    delwin(this->_win);
  endwin();
}

void	DisplayModuleNcurses::create_box(const int score)
{
  int	y = 1;
  int	x;

  wattron(this->_win, COLOR_PAIR(1));
  mvwprintw(this->_win, 0, 0, "Score: %d", score);
  while (y != this->_height + 3)
    {
      x = 0;
      if (y == 1 || (y + 1) == (this->_height + 3))
	{
	  while (x != this->_width + 2)
	    {
	      mvwaddch(this->_win, y, x, '-');
	      x = x + 1;
	    }
	}
      else
	{
	  x = 1;
	  mvwaddch(this->_win, y, 0, '|');
	  while (x != this->_width + 1)
	    {
	      mvwaddch(this->_win, y, x, ' ');
	      x = x + 1;
	    }
	  mvwaddch(this->_win, y, this->_width + 1, '|');
	}
      y = y + 1;
      }
  wattroff(this->_win, COLOR_PAIR(1));
}

void	DisplayModuleNcurses::drawSnake(const std::list<Coord>& snake)
{
  wattron(this->_win, COLOR_PAIR(3));
  for (std::list<Coord>::const_iterator it = snake.begin();
       it != snake.end(); ++it)
    {
      if (it == snake.begin())
	{
	  wattroff(this->_win, COLOR_PAIR(3));
	  wattron(this->_win, COLOR_PAIR(5));
	}
      mvwaddch(this->_win, (*it)._y + 2, (*it)._x + 1, 'o');
      if (it == snake.begin())
	{
	  wattroff(this->_win, COLOR_PAIR(5));
	  wattron(this->_win, COLOR_PAIR(3));
	}
    }
  wattroff(this->_win, COLOR_PAIR(3));
}

void	DisplayModuleNcurses::drawEat(const Coord & eat)
{
  wattron(this->_win, COLOR_PAIR(2));
  mvwaddch(this->_win, eat._y + 2, eat._x + 1, '#');
  wattroff(this->_win, COLOR_PAIR(2));
}

void	DisplayModuleNcurses::draw(const std::list<Coord>& snake, const Coord& eat, const int score)
{
  this->create_box(score);
  this->drawSnake(snake);
  this->drawEat(eat);
  doupdate();
  wnoutrefresh(this->_win);
}

void	DisplayModuleNcurses::init(int const width, int const height)
{
  this->_width = width;
  this->_height = height;
  initscr();
  curs_set(false);
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  if ((this->_win = newwin(height + 3, width + 2, 0, 0)) == NULL)
    {
      this->stop();
      throw IDisplayModuleException("Error: newwin failed.");
    }
  wrefresh(this->_win);
  if(has_colors() != FALSE)
    start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  this->create_box(0);
}

void	DisplayModuleNcurses::stop()
{
  if (this->_win != NULL)
    delwin(this->_win);
  endwin();
}


Dir	DisplayModuleNcurses::getEvent()
{
  int key = -1;

  nodelay(stdscr, TRUE);
  key = getch();
  switch (key)
  {
    case KEY_LEFT:
      return LEFT;
    case KEY_RIGHT:
      return RIGHT;
    case KEY_UP:
      return UP;
    case KEY_DOWN:
      return DOWN;
    case 27:
      return QUIT;
    case 32:
      return SPACE;
    default:
      return NONE;
  }
  return (NONE);
}

extern "C" IDisplayModule*	make()
{
  return (new DisplayModuleNcurses());
}
