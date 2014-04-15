//
// displaymode.hpp for  in /home/l-huil_o//test/nibbler/sdl
// 
// Made by olivier l-huillier
// Login   <l-huil_o@epitech.net>
// 
// Started on  Mon Mar  5 17:55:49 2012 olivier l-huillier
// Last update Thu Mar  8 15:57:10 2012 olivier l-huillier
//

#ifndef DISPLAYMODULE_HH_
#define DISPLAYMODULE_HH_

#include <list>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../Ressources/Coord.hh"
#include "../Ressources/IDisplayModule.hh"

class DisplayModuleSDL : public IDisplayModule
{
public:
  DisplayModuleSDL();
  virtual ~DisplayModuleSDL();
  
  virtual void		init(int const width, int const height);
  virtual void		stop();
  virtual void		draw(const std::list<Coord>& snake, const Coord& eat, int const score);
  virtual Dir		getEvent();
  
private:
  DisplayModuleSDL(DisplayModuleSDL const&);
  DisplayModuleSDL&operator=(DisplayModuleSDL const&);
  
  void		drawSnake(std::list<Coord> const& snake);
  void		drawEat(const Coord& eat);
  void		drawScore(const int score);
  void		initWindow(int const width, int const height);
  void		initGame();
  void		initScore();
  
  SDL_Surface	*_screen;
  SDL_Surface	*_snakeHead;
  SDL_Surface	*_snakeBody;
  SDL_Surface	*_eat;
  TTF_Font	*_font;
  SDL_Color	_textColor;
  int		_width;
  int		_height;
};

#endif
