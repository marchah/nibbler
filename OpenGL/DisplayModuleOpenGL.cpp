//
// displaymode.cpp for  in /home/l-huil_o//test/nibbler/sdl
// 
// Made by olivier l-huillier
// Login   <l-huil_o@epitech.net>
// 
// Started on  Mon Mar  5 17:55:31 2012 olivier l-huillier
// Last update Wed Mar 14 18:30:17 2012 fabien karquel
//

#include <iostream>
#include <sstream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "DisplayModuleOpenGL.hh"

#include "../Ressources/Defines.hh"
#include "../Ressources/Coord.hh"

DisplayModuleOpenGL::DisplayModuleOpenGL()
{
}

DisplayModuleOpenGL::~DisplayModuleOpenGL()
{
  SDL_Quit();
}

void DisplayModuleOpenGL::init(int const width, int const height)
{
  _height = height;
  _width = width;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
      throw IDisplayModuleException("Error: SDL_Init failed.");
  SDL_WM_SetCaption("Nibbler", NULL);
  this->_screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70,(double)width/height,1,1000);
  glEnable(GL_DEPTH_TEST);
}

void DisplayModuleOpenGL::stop()
{
  SDL_Quit();
}

void DisplayModuleOpenGL::draw_cube(int x, int y)
{
  glVertex3d(x + 1, 1, y + 1);
  glVertex3d(x + 1, 0, y + 1);
  glVertex3d(x, 0, y + 1);
  glVertex3d(x, 1, y + 1);

  glVertex3d(x + 1, 1, y);
  glVertex3d(x + 1, 0, y);
  glVertex3d(x + 1, 0, y + 1);
  glVertex3d(x + 1, 1, y + 1);

  glVertex3d(x, 1, y);
  glVertex3d(x, 0, y);
  glVertex3d(x + 1, 0, y);
  glVertex3d(x + 1, 1, y);

  glVertex3d(x, 1, y + 1);
  glVertex3d(x, 0, y + 1);
  glVertex3d(x, 0, y);
  glVertex3d(x, 1, y);

  glVertex3d(x + 1, 0, y + 1);
  glVertex3d(x + 1, 0, y);
  glVertex3d(x, 0, y);
  glVertex3d(x, 0, y + 1);

  glVertex3d(x + 1, 1, y);
  glVertex3d(x + 1, 1, y + 1);
  glVertex3d(x, 1, y + 1);
  glVertex3d(x, 1,y);
}

void DisplayModuleOpenGL::drawSnake(const std::list<Coord>& snake)
{
  for (std::list<Coord>::const_iterator it = snake.begin();
       it != snake.end(); ++it)
    {
      glBegin(GL_QUADS);
      if (it == snake.begin())
	glColor3ub(255,128,0);
      else
	glColor3ub(128,255,0);
      draw_cube((*it)._x, (*it)._y);
      glEnd();
    }
}

void DisplayModuleOpenGL::drawEat(const Coord& eat)
{
  glBegin(GL_QUADS);
  glColor3ub(0,0,255);
  draw_cube(eat._x, eat._y);
  glEnd();
}

void DisplayModuleOpenGL::draw_ground()
{
  glBegin(GL_QUADS);
  glColor3ub(200,200,200);
  glVertex3d(0,0,0);
  glVertex3d(0,0,_height);
  glVertex3d(_width,0,_height);
  glVertex3d(_width,0, 0);
  glEnd();
}

void DisplayModuleOpenGL::draw(const std::list<Coord>& snake, const Coord& eat, int score)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(_width / 2 , 20 + (_width + _height) / 2, _height * 2,0,0,0,(_width + _height) / 2 + 20,360,0);

  this->draw_ground();
  this->drawSnake(snake);
  this->drawEat(eat);
  glFlush();
  SDL_GL_SwapBuffers();

  std::stringstream	ss;
  ss << "Score: " << score;

  SDL_WM_SetCaption(ss.str().c_str(), NULL);
  (void)score;
}

Dir DisplayModuleOpenGL::getEvent()
{
  SDL_Event	event;
  int		key;

  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT)
    return QUIT;
  if (event.type == SDL_KEYDOWN)
    {
      key = event.key.keysym.sym;
      switch (key)
	{
	case SDLK_LEFT:
	  return LEFT;
	case SDLK_RIGHT:
	  return RIGHT;
	case SDLK_UP:
	  return UP;
	case SDLK_DOWN:
	  return DOWN;
	case SDLK_ESCAPE:
	  return QUIT;
	case SDLK_SPACE:
	  return SPACE;
	default:
	  return NONE;
	}
    }
  return NONE;
}

extern "C"
{
  IDisplayModule	*make()
  {
    return (new DisplayModuleOpenGL);
  }
}
