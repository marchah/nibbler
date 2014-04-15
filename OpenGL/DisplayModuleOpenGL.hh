//
// displaymode.hpp for  in /home/l-huil_o//test/nibbler/sdl
// 
// Made by olivier l-huillier
// Login   <l-huil_o@epitech.net>
// 
// Started on  Mon Mar  5 17:55:49 2012 olivier l-huillier
// Last update Wed Mar 14 18:02:31 2012 fabien karquel
//

#ifndef DISPLAYMODULEOPENGL_HH_
#define DISPLAYMODULEOPENGL_HH_

#include <list>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../Ressources/Coord.hh"
#include "../Ressources/IDisplayModule.hh"


class DisplayModuleOpenGL : public IDisplayModule
{
public:
  DisplayModuleOpenGL();
  virtual ~DisplayModuleOpenGL();
  
  virtual void		init(int const width, int const height);
  virtual void		stop();
  virtual void		draw(const std::list<Coord>& snake, const Coord& eat, int score);
  virtual Dir		getEvent();
  
private:
  DisplayModuleOpenGL(DisplayModuleOpenGL const&);
  DisplayModuleOpenGL&operator=(DisplayModuleOpenGL const&);
  
  void		drawSnake(std::list<Coord> const& snake);
  void		drawEat(const Coord& eat);
  void		draw_ground();
  void		draw_cube(int x, int y);

  SDL_Surface	*_screen;
  int		_width;
  int		_height;
};

#endif // DISPLAYMODULEOPENGL_HH_
